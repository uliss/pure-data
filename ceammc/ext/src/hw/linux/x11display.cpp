/*
 * Copyright © 2007 Keith Packard
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */
/*****************************************************************************
 * Copyright 2019 Serge Poltavsky. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/

#include "x11display.h"

#include "ceammc_convert.h"
#include "ceammc_log.h"
#include "m_pd.h"

using namespace ceammc;

namespace x11_display {

static long backlight_get(xcb_connection_t* conn, xcb_atom_t& backlight, xcb_atom_t backlight_new, xcb_atom_t backlight_legacy, xcb_randr_output_t output)
{
    xcb_generic_error_t* error;
    xcb_randr_get_output_property_reply_t* prop_reply = NULL;
    xcb_randr_get_output_property_cookie_t prop_cookie;
    long value;

    backlight = backlight_new;
    if (backlight != XCB_ATOM_NONE) {
        prop_cookie = xcb_randr_get_output_property(conn, output,
            backlight, XCB_ATOM_NONE,
            0, 4, 0, 0);
        prop_reply = xcb_randr_get_output_property_reply(conn, prop_cookie, &error);
        if (error != NULL || prop_reply == NULL) {
            backlight = backlight_legacy;
            if (backlight != XCB_ATOM_NONE) {
                prop_cookie = xcb_randr_get_output_property(conn, output,
                    backlight, XCB_ATOM_NONE,
                    0, 4, 0, 0);
                prop_reply = xcb_randr_get_output_property_reply(conn, prop_cookie, &error);
                if (error != NULL || prop_reply == NULL) {
                    return -1;
                }
            }
        }
    }

    if (prop_reply == NULL || prop_reply->type != XCB_ATOM_INTEGER || prop_reply->num_items != 1 || prop_reply->format != 32) {
        value = -1;
    } else {
        value = *((int32_t*)xcb_randr_get_output_property_data(prop_reply));
    }

    free(prop_reply);
    return value;
}

X11Display::X11Display()
    : conn_(xcb_connect(NULL, NULL))
{
    if (xcb_connection_has_error(conn_) != 0) {
        xcb_disconnect(conn_);
        conn_ = nullptr;
        LIB_ERR << "connection error";
        return;
    }

    xcb_generic_error_t* error;
    xcb_randr_query_version_cookie_t ver_cookie;
    xcb_randr_query_version_reply_t* ver_reply;
    ver_cookie = xcb_randr_query_version(conn_, 1, 2);
    ver_reply = xcb_randr_query_version_reply(conn_, ver_cookie, &error);
    if (error != NULL || ver_reply == NULL) {
        int ec = error ? error->error_code : -1;
        LIB_ERR << "RANDR Query Version returned error " << ec;
        xcb_disconnect(conn_);
        conn_ = nullptr;
        return;
    }

    if (ver_reply->major_version != 1 || ver_reply->minor_version < 2) {
        pd_error(nullptr, "RandR version %d.%d too old",
            ver_reply->major_version, ver_reply->minor_version);
        free(ver_reply);
        xcb_disconnect(conn_);
        conn_ = nullptr;
        return;
    }

    free(ver_reply);

    xcb_intern_atom_cookie_t backlight_cookie[2];
    backlight_cookie[0] = xcb_intern_atom(conn_, 1, strlen("Backlight"), "Backlight");
    backlight_cookie[1] = xcb_intern_atom(conn_, 1, strlen("BACKLIGHT"), "BACKLIGHT");

    xcb_intern_atom_reply_t* backlight_reply;
    backlight_reply = xcb_intern_atom_reply(conn_, backlight_cookie[0], &error);
    if (error != NULL || backlight_reply == NULL) {
        int ec = error ? error->error_code : -1;
        pd_error(nullptr, "Intern Atom returned error %d", ec);
        xcb_disconnect(conn_);
        conn_ = nullptr;
        return;
    }

    backlight_new = backlight_reply->atom;
    free(backlight_reply);

    backlight_reply = xcb_intern_atom_reply(conn_, backlight_cookie[1], &error);
    if (error != NULL || backlight_reply == NULL) {
        int ec = error ? error->error_code : -1;
        pd_error(nullptr, "Intern Atom returned error %d", ec);
        xcb_disconnect(conn_);
        conn_ = nullptr;
        return;
    }

    backlight_legacy = backlight_reply->atom;
    free(backlight_reply);

    if (backlight_new == XCB_NONE && backlight_legacy == XCB_NONE) {
        pd_error(nullptr, "No outputs have backlight property");
        xcb_disconnect(conn_);
        conn_ = nullptr;
        return;
    }
}

X11Display::~X11Display()
{
    xcb_disconnect(conn_);
}

bool X11Display::setBrightness(float v)
{
    if (!conn_)
        return false;

    xcb_generic_error_t* error;

    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(xcb_get_setup(conn_));
    while (iter.rem) {
        xcb_screen_t* screen = iter.data;
        xcb_window_t root = screen->root;

        xcb_randr_get_screen_resources_current_cookie_t resources_cookie;
        xcb_randr_get_screen_resources_current_reply_t* resources_reply;

        resources_cookie = xcb_randr_get_screen_resources_current(conn_, root);
        resources_reply = xcb_randr_get_screen_resources_current_reply(conn_, resources_cookie, &error);
        if (error != NULL || resources_reply == NULL) {
            int ec = error ? error->error_code : -1;
            pd_error(nullptr, "RANDR Get Screen Resources returned error %d", ec);
            continue;
        }

        xcb_randr_output_t* outputs = xcb_randr_get_screen_resources_current_outputs(resources_reply);
        for (int o = 0; o < resources_reply->num_outputs; o++) {
            xcb_randr_output_t output = outputs[o];
            xcb_atom_t backlight;
            double cur = backlight_get(conn_, backlight, backlight_new, backlight_legacy, output);
            if (cur != -1) {
                xcb_randr_query_output_property_cookie_t prop_cookie;
                xcb_randr_query_output_property_reply_t* prop_reply;

                prop_cookie = xcb_randr_query_output_property(conn_, output, backlight);
                prop_reply = xcb_randr_query_output_property_reply(conn_, prop_cookie, &error);

                if (error != NULL || prop_reply == NULL)
                    continue;

                if (prop_reply->range && xcb_randr_query_output_property_valid_values_length(prop_reply) == 2) {
                    int32_t* values = xcb_randr_query_output_property_valid_values(prop_reply);
                    double vmin = values[0];
                    double vmax = values[1];

                    long vset = clip<float>(v, vmin, vmax) * (vmax - vmin) + vmin;
                    xcb_randr_change_output_property (conn_, output, backlight, XCB_ATOM_INTEGER,
                                       32, XCB_PROP_MODE_REPLACE,
                                       1, &vset);
                    xcb_flush(conn_);

                    free(resources_reply);
                    free(prop_reply);
                    return true;
                }

                free(prop_reply);
            }

            free(resources_reply);
            xcb_screen_next(&iter);
        }
    }

    return false;
}

bool X11Display::getBrightness(float* v) const
{
    if (!conn_)
        return false;

    xcb_generic_error_t* error;

    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(xcb_get_setup(conn_));
    while (iter.rem) {
        xcb_screen_t* screen = iter.data;
        xcb_window_t root = screen->root;

        xcb_randr_get_screen_resources_current_cookie_t resources_cookie;
        xcb_randr_get_screen_resources_current_reply_t* resources_reply;

        resources_cookie = xcb_randr_get_screen_resources_current(conn_, root);
        resources_reply = xcb_randr_get_screen_resources_current_reply(conn_, resources_cookie, &error);
        if (error != NULL || resources_reply == NULL) {
            int ec = error ? error->error_code : -1;
            pd_error(nullptr, "RANDR Get Screen Resources returned error %d", ec);
            continue;
        }

        xcb_randr_output_t* outputs = xcb_randr_get_screen_resources_current_outputs(resources_reply);
        for (int o = 0; o < resources_reply->num_outputs; o++) {
            xcb_randr_output_t output = outputs[o];
            xcb_atom_t backlight;
            double cur = backlight_get(conn_, backlight, backlight_new, backlight_legacy, output);
            if (cur != -1) {
                xcb_randr_query_output_property_cookie_t prop_cookie;
                xcb_randr_query_output_property_reply_t* prop_reply;

                prop_cookie = xcb_randr_query_output_property(conn_, output, backlight);
                prop_reply = xcb_randr_query_output_property_reply(conn_, prop_cookie, &error);

                if (error != NULL || prop_reply == NULL)
                    continue;

                if (prop_reply->range && xcb_randr_query_output_property_valid_values_length(prop_reply) == 2) {
                    int32_t* values = xcb_randr_query_output_property_valid_values(prop_reply);
                    double min = values[0];
                    double max = values[1];

                    float res = float(cur - min) / (max - min);
                    free(resources_reply);
                    free(prop_reply);
                    *v = res;
                    return true;
                }

                free(prop_reply);
            }

            free(resources_reply);
            xcb_screen_next(&iter);
        }
    }

    return false;
}
}
