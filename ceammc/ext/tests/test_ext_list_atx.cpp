/*****************************************************************************
 * Copyright 2017 Serge Poltavsky. All rights reserved.
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
#include "../data/data_mlist.h"
#include "../list/list_atx.h"
#include "test_external.h"

PD_COMPLETE_TEST_SETUP(ListAtX, list, atx);

typedef TestExternal<ListAtX> ListAtXTest;

TEST_CASE("list.^at", "[externals]")
{
    pd_test_mod_init_list_atx();

    SECTION("test create with:")
    {
        SECTION("empty arguments")
        {
            ListAtXTest t("list.^at");
            REQUIRE(t.numInlets() == 2);
            REQUIRE(t.numOutlets() == 1);
            REQUIRE(t.property("@default") != 0);
            REQUIRE(t.property("@default")->get()[0].isNone());
            REQUIRE_PROPERTY_LIST(t, @method, LA("rel"));
        }

        SECTION("properties")
        {
            ListAtXTest t("list.^at", LA("@default", 2, "@fold"));
            REQUIRE(t.property("@default") != 0);
            REQUIRE(t.property("@default")->get() == Atom(2));
            REQUIRE_PROPERTY_LIST(t, @method, LA("fold"));
        }

        SECTION("method")
        {
            SECTION("rel")
            {
                ListAtXTest t("list.^at", LA("@method", "rel"));
                REQUIRE_PROPERTY_LIST(t, @method, LA("rel"));
            }

            SECTION("@rel")
            {
                ListAtXTest t("list.^at", LA("@rel"));
                REQUIRE_PROPERTY_LIST(t, @method, LA("rel"));
            }

            SECTION("clip")
            {
                ListAtXTest t("list.^at", LA("@method", "clip"));
                REQUIRE_PROPERTY_LIST(t, @method, LA("clip"));
            }

            SECTION("@clip")
            {
                ListAtXTest t("list.^at", LA("@clip"));
                REQUIRE_PROPERTY_LIST(t, @method, LA("clip"));
            }

            SECTION("fold")
            {
                ListAtXTest t("list.^at", LA("@method", "fold"));
                REQUIRE_PROPERTY_LIST(t, @method, LA("fold"));
            }

            SECTION("@fold")
            {
                ListAtXTest t("list.^at", LA("@fold"));
                REQUIRE_PROPERTY_LIST(t, @method, LA("fold"));
            }

            SECTION("wrap")
            {
                ListAtXTest t("list.^at", LA("@method", "wrap"));
                REQUIRE_PROPERTY_LIST(t, @method, LA("wrap"));
            }

            SECTION("@wrap")
            {
                ListAtXTest t("list.^at", LA("@wrap"));
                REQUIRE_PROPERTY_LIST(t, @method, LA("wrap"));
            }
        }
    }

    SECTION("do")
    {
        SECTION("empty")
        {
            ListAtXTest t("list.^at");

            WHEN_SEND_FLOAT_TO(0, t, 0);
            REQUIRE_NO_MSG(t);
            WHEN_SEND_FLOAT_TO(1, t, 0);
            REQUIRE_NO_MSG(t);
            WHEN_SEND_FLOAT_TO(-1, t, 0);
            REQUIRE_NO_MSG(t);
        }

        SECTION("rel")
        {
            ListAtXTest t("list.^at", LA(1, 2, 3));

            WHEN_SEND_FLOAT_TO(0, t, 0);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 1);
            WHEN_SEND_FLOAT_TO(0, t, 1);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 2);
            WHEN_SEND_FLOAT_TO(0, t, 2);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 3);
            WHEN_SEND_FLOAT_TO(0, t, 3);
            REQUIRE_NO_MSG(t);
            WHEN_SEND_FLOAT_TO(0, t, -1);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 3);
            WHEN_SEND_FLOAT_TO(0, t, -2);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 2);
            WHEN_SEND_FLOAT_TO(0, t, -3);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 1);
            WHEN_SEND_FLOAT_TO(0, t, -4);
            REQUIRE_NO_MSG(t);
        }

        SECTION("rel @default")
        {
            ListAtXTest t("list.^at", LA(1, 2, 3, "@default", "null"));

            WHEN_SEND_FLOAT_TO(0, t, 0);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 1);
            WHEN_SEND_FLOAT_TO(0, t, 1);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 2);
            WHEN_SEND_FLOAT_TO(0, t, 2);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 3);
            WHEN_SEND_FLOAT_TO(0, t, 3);
            REQUIRE_SYMBOL_AT_OUTLET(0, t, "null");
            WHEN_SEND_FLOAT_TO(0, t, -1);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 3);
            WHEN_SEND_FLOAT_TO(0, t, -2);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 2);
            WHEN_SEND_FLOAT_TO(0, t, -3);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 1);
            WHEN_SEND_FLOAT_TO(0, t, -4);
            REQUIRE_SYMBOL_AT_OUTLET(0, t, "null");
        }

        SECTION("clip")
        {
            ListAtXTest t("list.^at", LA(1, 2, 3, "@clip"));

            WHEN_SEND_FLOAT_TO(0, t, 0);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 1);
            WHEN_SEND_FLOAT_TO(0, t, 1);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 2);
            WHEN_SEND_FLOAT_TO(0, t, 2);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 3);
            WHEN_SEND_FLOAT_TO(0, t, 3);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 3);
            WHEN_SEND_FLOAT_TO(0, t, 4);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 3);
            WHEN_SEND_FLOAT_TO(0, t, 4000);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 3);
            WHEN_SEND_FLOAT_TO(0, t, -1);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 1);
            WHEN_SEND_FLOAT_TO(0, t, -2);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 1);
            WHEN_SEND_FLOAT_TO(0, t, -3);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 1);
            WHEN_SEND_FLOAT_TO(0, t, -4);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 1);
            WHEN_SEND_FLOAT_TO(0, t, -5);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 1);
            WHEN_SEND_FLOAT_TO(0, t, -6000);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 1);
        }

        SECTION("wrap")
        {
            ListAtXTest t("list.^at", LA(1, 2, 3, "@wrap"));

            WHEN_SEND_FLOAT_TO(0, t, 0);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 1);
            WHEN_SEND_FLOAT_TO(0, t, 1);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 2);
            WHEN_SEND_FLOAT_TO(0, t, 2);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 3);
            WHEN_SEND_FLOAT_TO(0, t, 3);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 1);
            WHEN_SEND_FLOAT_TO(0, t, 4);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 2);
            WHEN_SEND_FLOAT_TO(0, t, 5);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 3);
            WHEN_SEND_FLOAT_TO(0, t, 6);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 1);
            WHEN_SEND_FLOAT_TO(0, t, 7);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 2);
            WHEN_SEND_FLOAT_TO(0, t, -1);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 3);
            WHEN_SEND_FLOAT_TO(0, t, -2);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 2);
            WHEN_SEND_FLOAT_TO(0, t, -3);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 1);
            WHEN_SEND_FLOAT_TO(0, t, -4);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 3);
        }

        SECTION("fold")
        {
            ListAtXTest t("list.^at", LA(1, 2, 3, "@fold"));

            WHEN_SEND_FLOAT_TO(0, t, 0);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 1);
            WHEN_SEND_FLOAT_TO(0, t, 1);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 2);
            WHEN_SEND_FLOAT_TO(0, t, 2);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 3);
            WHEN_SEND_FLOAT_TO(0, t, 3);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 2);
            WHEN_SEND_FLOAT_TO(0, t, 4);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 1);
            WHEN_SEND_FLOAT_TO(0, t, 5);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 2);
            WHEN_SEND_FLOAT_TO(0, t, 6);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 3);
            WHEN_SEND_FLOAT_TO(0, t, 7);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 2);
            WHEN_SEND_FLOAT_TO(0, t, -1);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 2);
            WHEN_SEND_FLOAT_TO(0, t, -2);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 3);
            WHEN_SEND_FLOAT_TO(0, t, -3);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 2);
            WHEN_SEND_FLOAT_TO(0, t, -4);
            REQUIRE_FLOAT_AT_OUTLET(0, t, 1);
        }
    }

    SECTION("list")
    {
        SECTION("rel")
        {
            ListAtXTest t("list.^at", LA(1, 2, 3, "@rel"));

            WHEN_SEND_LIST_TO(0, t, L());
            REQUIRE_LIST_AT_OUTLET(0, t, L());

            WHEN_SEND_LIST_TO(0, t, LF(0, -1, 2));
            REQUIRE_LIST_AT_OUTLET(0, t, LF(1, 3, 3));

            WHEN_SEND_LIST_TO(0, t, LF(0, 100, -100));
            REQUIRE_LIST_AT_OUTLET(0, t, LF(1));
        }

        SECTION("rel + default")
        {
            ListAtXTest t("list.^at", LA(1, 2, 3, "@default", "NONE"));

            WHEN_SEND_LIST_TO(0, t, LF(0, 100, -100));
            REQUIRE_LIST_AT_OUTLET(0, t, LA(1, "NONE", "NONE"));
        }
    }

    SECTION("external")
    {
        TestExtListAtX t("list.^at", LF(-1));
    }
}