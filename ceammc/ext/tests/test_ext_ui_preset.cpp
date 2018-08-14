/*****************************************************************************
 * Copyright 2018 Serge Poltavsky. All rights reserved.
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
#include "../ui/ui_preset.h"
#include "../ui/ui_slider.h"
#include "ceammc_platform.h"
#include "test_ui.h"

typedef TestUIExternal<UISlider> TestExtSlider;

UI_COMPLETE_TEST_SETUP(Preset)

TEST_CASE("ui.preset", "[ui.preset]")
{
    ui_test_init();
    setup_ui_slider();

    SECTION("construct")
    {
        TestPreset t("ui.preset");
        REQUIRE(t->numInlets() == 1);
        REQUIRE(t->numOutlets() == 0);
    }

    SECTION("external")
    {
        TestExtPreset t("ui.preset");

        TestExtSlider s0("ui.slider");
        TestExtSlider s1("ui.slider");

        s0->setValue(0.2);
        s1->setValue(0.8);
        t.call("store");

        s0->setValue(0.3);
        s1->setValue(0.7);
        t.call("store", 1);

        s0->setValue(0.4);
        s1->setValue(0.6);
        t.call("store", 2);

        t.call("load");
        REQUIRE(s0->value() == 0.2f);
        REQUIRE(s1->value() == 0.8f);
        REQUIRE(t->propCurrent() == LF(0));

        t.call("load", LF(1));
        REQUIRE(s0->value() == 0.3f);
        REQUIRE(s1->value() == 0.7f);
        REQUIRE(t->propCurrent() == LF(1));

        t.call("load", LF(0.f));
        REQUIRE(s0->value() == 0.2f);
        REQUIRE(s1->value() == 0.8f);
        REQUIRE(t->propCurrent() == LF(0));

        t.call("load", LF(2));
        REQUIRE(s0->value() == 0.4f);
        REQUIRE(s1->value() == 0.6f);
        REQUIRE(t->propCurrent() == LF(2));

        t.call("write", LA(TEST_DATA_DIR "abc.txt"));
        REQUIRE(platform::path_exists(TEST_DATA_DIR "abc.txt"));

        t.call("clear", LF(0.f));
        t.call("clear", LF(1));
        t.call("clear", LF(2));

        REQUIRE(s0->value() == 0.4f);
        REQUIRE(s1->value() == 0.6f);
        t.call("load", LF(1));
        REQUIRE(s0->value() == 0.4f);
        REQUIRE(s1->value() == 0.6f);

        t.call("read", LA(TEST_DATA_DIR "abc.txt"));
        t.call("load");
        REQUIRE(s0->value() == 0.2f);
        REQUIRE(s1->value() == 0.8f);
        REQUIRE(t->propCurrent() == LF(0));

        t.call("load", LF(1));
        REQUIRE(s0->value() == 0.3f);
        REQUIRE(s1->value() == 0.7f);
        REQUIRE(t->propCurrent() == LF(1));

        platform::remove(TEST_DATA_DIR "abc.txt");
    }

    SECTION("invalid")
    {
        TestExtPreset t("ui.preset");

        t <<= LA("load", -1);
        t <<= LA("store", -1);
        t <<= LA("clear", -1);
        t <<= LA("load", 100000);
        t <<= LA("store", 100000);
        t <<= LA("clear", 100000);
    }
}
