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
#include "proto_xtouch_ext.h"
#include "test_proto_base.h"

PD_COMPLETE_TEST_SETUP(XTouchExtender, proto, xtouch_ext)

TEST_CASE("proto.xtouch_ext", "[externals]")
{
    pd_test_init();
    test::pdPrintToStdError();

    SECTION("create")
    {
        SECTION("default")
        {
            TExt t("proto.xtouch_ext");
            REQUIRE(t.numInlets() == 1);
            REQUIRE(t.numOutlets() == 2);
        }
    }

    SECTION("display")
    {
        Display d;

        d.setUpperAlign(d.ALIGN_CENTER);
        d.setUpperText("ABC");
        REQUIRE(d.upperCharAt(0) == 'A');
        REQUIRE(d.upperCharAt(1) == 'B');
        REQUIRE(d.upperCharAt(2) == 'C');
        REQUIRE(d.upperCharAt(3) == '\0');
        REQUIRE(d.upperCharAt(4) == '\0');
        REQUIRE(d.upperCharAt(5) == '\0');
        REQUIRE(d.upperCharAt(6) == '\0');
        REQUIRE(d.upperCharAt(7) == '\0');

        d.setUpperText("ABCDEFGHIJ");
        REQUIRE(d.upperCharAt(0) == 'A');
        REQUIRE(d.upperCharAt(1) == 'B');
        REQUIRE(d.upperCharAt(2) == 'C');
        REQUIRE(d.upperCharAt(3) == 'D');
        REQUIRE(d.upperCharAt(4) == 'E');
        REQUIRE(d.upperCharAt(5) == 'F');
        REQUIRE(d.upperCharAt(6) == 'G');
        REQUIRE(d.upperCharAt(7) == '\0');

        d.setUpperAlign(d.ALIGN_LEFT);
        d.setUpperText("ABC");
        REQUIRE(d.upperCharAt(0) == 'A');
        REQUIRE(d.upperCharAt(1) == 'B');
        REQUIRE(d.upperCharAt(2) == 'C');
        REQUIRE(d.upperCharAt(3) == ' ');
        REQUIRE(d.upperCharAt(4) == ' ');
        REQUIRE(d.upperCharAt(5) == ' ');
        REQUIRE(d.upperCharAt(6) == ' ');
        REQUIRE(d.upperCharAt(7) == '\0');

        d.setUpperText("ABCDEFGHIJ");
        REQUIRE(d.upperCharAt(0) == 'A');
        REQUIRE(d.upperCharAt(1) == 'B');
        REQUIRE(d.upperCharAt(2) == 'C');
        REQUIRE(d.upperCharAt(3) == 'D');
        REQUIRE(d.upperCharAt(4) == 'E');
        REQUIRE(d.upperCharAt(5) == 'F');
        REQUIRE(d.upperCharAt(6) == 'G');
        REQUIRE(d.upperCharAt(7) == '\0');

        d.setUpperAlign(d.ALIGN_RIGHT);
        d.setUpperText("ABC");
        REQUIRE(d.upperCharAt(0) == ' ');
        REQUIRE(d.upperCharAt(1) == ' ');
        REQUIRE(d.upperCharAt(2) == ' ');
        REQUIRE(d.upperCharAt(3) == ' ');
        REQUIRE(d.upperCharAt(4) == 'A');
        REQUIRE(d.upperCharAt(5) == 'B');
        REQUIRE(d.upperCharAt(6) == 'C');
        REQUIRE(d.upperCharAt(7) == '\0');

        d.setUpperText("ABCDEFGHIJ");
        REQUIRE(d.upperCharAt(0) == 'A');
        REQUIRE(d.upperCharAt(1) == 'B');
        REQUIRE(d.upperCharAt(2) == 'C');
        REQUIRE(d.upperCharAt(3) == 'D');
        REQUIRE(d.upperCharAt(4) == 'E');
        REQUIRE(d.upperCharAt(5) == 'F');
        REQUIRE(d.upperCharAt(6) == 'G');
        REQUIRE(d.upperCharAt(7) == '\0');

        d.setUpperAlign(d.ALIGN_JUSTIFY);
        d.setUpperText("n: 1%");
        REQUIRE(d.upperCharAt(0) == 'n');
        REQUIRE(d.upperCharAt(1) == ':');
        REQUIRE(d.upperCharAt(2) == ' ');
        REQUIRE(d.upperCharAt(3) == ' ');
        REQUIRE(d.upperCharAt(4) == ' ');
        REQUIRE(d.upperCharAt(5) == '1');
        REQUIRE(d.upperCharAt(6) == '%');
        REQUIRE(d.upperCharAt(7) == '\0');

        d.setUpperText("n: 12%");
        REQUIRE(d.upperCharAt(0) == 'n');
        REQUIRE(d.upperCharAt(1) == ':');
        REQUIRE(d.upperCharAt(2) == ' ');
        REQUIRE(d.upperCharAt(3) == ' ');
        REQUIRE(d.upperCharAt(4) == '1');
        REQUIRE(d.upperCharAt(5) == '2');
        REQUIRE(d.upperCharAt(6) == '%');
        REQUIRE(d.upperCharAt(7) == '\0');

        d.setUpperText("n: 123%");
        REQUIRE(d.upperCharAt(0) == 'n');
        REQUIRE(d.upperCharAt(1) == ':');
        REQUIRE(d.upperCharAt(2) == ' ');
        REQUIRE(d.upperCharAt(3) == '1');
        REQUIRE(d.upperCharAt(4) == '2');
        REQUIRE(d.upperCharAt(5) == '3');
        REQUIRE(d.upperCharAt(6) == '%');
        REQUIRE(d.upperCharAt(7) == '\0');

        d.setUpperText("n: 123%");
        REQUIRE(d.upperCharAt(0) == 'n');
        REQUIRE(d.upperCharAt(1) == ':');
        REQUIRE(d.upperCharAt(2) == ' ');
        REQUIRE(d.upperCharAt(3) == '1');
        REQUIRE(d.upperCharAt(4) == '2');
        REQUIRE(d.upperCharAt(5) == '3');
        REQUIRE(d.upperCharAt(6) == '%');
        REQUIRE(d.upperCharAt(7) == '\0');

        d.setUpperText("n: 1234%");
        REQUIRE(d.upperCharAt(0) == 'n');
        REQUIRE(d.upperCharAt(1) == ':');
        REQUIRE(d.upperCharAt(2) == '1');
        REQUIRE(d.upperCharAt(3) == '2');
        REQUIRE(d.upperCharAt(4) == '3');
        REQUIRE(d.upperCharAt(5) == '4');
        REQUIRE(d.upperCharAt(6) == '%');
        REQUIRE(d.upperCharAt(7) == '\0');

        d.setUpperText("n: 12345%");
        REQUIRE(d.upperCharAt(0) == 'n');
        REQUIRE(d.upperCharAt(1) == ':');
        REQUIRE(d.upperCharAt(2) == '1');
        REQUIRE(d.upperCharAt(3) == '2');
        REQUIRE(d.upperCharAt(4) == '3');
        REQUIRE(d.upperCharAt(5) == '4');
        REQUIRE(d.upperCharAt(6) == '5');
        REQUIRE(d.upperCharAt(7) == '\0');
    }

    SECTION("setUpperText")
    {
        Display d;

        d.setUpperText(LA("A", "B"));
        REQUIRE(d.upperCharAt(0) == 'A');
        REQUIRE(d.upperCharAt(1) == ' ');
        REQUIRE(d.upperCharAt(2) == ' ');
        REQUIRE(d.upperCharAt(3) == ' ');
        REQUIRE(d.upperCharAt(4) == ' ');
        REQUIRE(d.upperCharAt(5) == ' ');
        REQUIRE(d.upperCharAt(6) == 'B');
        REQUIRE(d.upperCharAt(7) == '\0');

        d.setUpperText(LA("A B"));
        REQUIRE(d.upperCharAt(0) == 'A');
        REQUIRE(d.upperCharAt(1) == ' ');
        REQUIRE(d.upperCharAt(2) == 'B');
        REQUIRE(d.upperCharAt(3) == '\0');
        REQUIRE(d.upperCharAt(4) == '\0');
        REQUIRE(d.upperCharAt(5) == '\0');
        REQUIRE(d.upperCharAt(6) == '\0');
        REQUIRE(d.upperCharAt(7) == '\0');
    }

    SECTION("align")
    {
        TExt t("proto.xtouch_ext");

        REQUIRE(t->display(0).upperAlign() == Display::ALIGN_AUTO);
        REQUIRE(t->display(0).lowerAlign() == Display::ALIGN_AUTO);

        REQUIRE(t->display(0).upperAlign() == Display::ALIGN_AUTO);
        REQUIRE(t->display(0).lowerAlign() == Display::ALIGN_AUTO);

        t.call("lcd_align");
        REQUIRE(t->display(0).upperAlign() == Display::ALIGN_AUTO);
        REQUIRE(t->display(0).lowerAlign() == Display::ALIGN_AUTO);

        t.call("lcd_align", LA("all"));
        REQUIRE(t->display(0).upperAlign() == Display::ALIGN_AUTO);
        REQUIRE(t->display(0).lowerAlign() == Display::ALIGN_AUTO);

        t.call("lcd_align", LA("all", "left"));
        REQUIRE(t->display(0).upperAlign() == Display::ALIGN_LEFT);
        REQUIRE(t->display(0).lowerAlign() == Display::ALIGN_LEFT);

        t.call("lcd_align", LA("scene", "right"));
        REQUIRE(t->display(0).upperAlign() == Display::ALIGN_RIGHT);
        REQUIRE(t->display(0).lowerAlign() == Display::ALIGN_RIGHT);
        REQUIRE(t->display(8).upperAlign() == Display::ALIGN_LEFT);
        REQUIRE(t->display(8).lowerAlign() == Display::ALIGN_LEFT);

        t.call("lcd_align", LA(2, "auto"));
        REQUIRE(t->display(1).upperAlign() == Display::ALIGN_RIGHT);
        REQUIRE(t->display(1).lowerAlign() == Display::ALIGN_RIGHT);
        REQUIRE(t->display(2).upperAlign() == Display::ALIGN_AUTO);
        REQUIRE(t->display(2).lowerAlign() == Display::ALIGN_AUTO);
        REQUIRE(t->display(3).upperAlign() == Display::ALIGN_RIGHT);
        REQUIRE(t->display(3).lowerAlign() == Display::ALIGN_RIGHT);

        t.call("lcd_align", LA(0., "left", "right", "center", "left", "right", "center", "left", "right", "auto"));
        REQUIRE(t->display(0).upperAlign() == Display::ALIGN_LEFT);
        REQUIRE(t->display(1).upperAlign() == Display::ALIGN_RIGHT);
        REQUIRE(t->display(2).upperAlign() == Display::ALIGN_CENTER);
        REQUIRE(t->display(3).upperAlign() == Display::ALIGN_LEFT);
        REQUIRE(t->display(4).upperAlign() == Display::ALIGN_RIGHT);
        REQUIRE(t->display(5).upperAlign() == Display::ALIGN_CENTER);
        REQUIRE(t->display(6).upperAlign() == Display::ALIGN_LEFT);

        t.call("lcd_align", LA(4, "auto", "auto", "auto", "auto"));
        REQUIRE(t->display(0).upperAlign() == Display::ALIGN_LEFT);
        REQUIRE(t->display(1).upperAlign() == Display::ALIGN_RIGHT);
        REQUIRE(t->display(2).upperAlign() == Display::ALIGN_CENTER);
        REQUIRE(t->display(3).upperAlign() == Display::ALIGN_LEFT);
        REQUIRE(t->display(4).upperAlign() == Display::ALIGN_AUTO);
        REQUIRE(t->display(5).upperAlign() == Display::ALIGN_AUTO);
        REQUIRE(t->display(6).upperAlign() == Display::ALIGN_AUTO);

        t.call("lcd_align", LA("all", "left"));
        REQUIRE(t->display(0).upperAlign() == Display::ALIGN_LEFT);
        REQUIRE(t->display(0).lowerAlign() == Display::ALIGN_LEFT);

        t.call("lcd_align0", LA("all", "right"));
        REQUIRE(t->display(0).upperAlign() == Display::ALIGN_RIGHT);
        REQUIRE(t->display(0).lowerAlign() == Display::ALIGN_LEFT);

        t.call("lcd_align1", LA("all", "auto"));
        REQUIRE(t->display(0).upperAlign() == Display::ALIGN_RIGHT);
        REQUIRE(t->display(0).lowerAlign() == Display::ALIGN_AUTO);
    }
}
