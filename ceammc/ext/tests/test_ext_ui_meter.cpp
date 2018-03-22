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
#include "../ui/ui_meter.h"
#include "ui_external_test.h"

UI_COMPLETE_DSP_TEST_SETUP(Meter)

TEST_CASE("ui.meter~", "[ui.meter~]")
{
    ui_test_init();

    SECTION("construct")
    {
        TestMeter t("ui.meter~");
        REQUIRE(t->numInlets() == 1);
        REQUIRE(t->numOutlets() == 1);
        REQUIRE_UI_FLOAT_PROPERTY(t, "interval", 50);
    }

    SECTION("external")
    {
        // just create test
        TestExtMeter t("ui.meter~");
    }
}
