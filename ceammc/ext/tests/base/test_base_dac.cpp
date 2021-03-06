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
#include "base_dac.h"
#include "test_base.h"
#include "test_catch2.hpp"

PD_COMPLETE_TEST_SETUP(BaseDac, base, dac)

TEST_CASE("xdac~", "[extension]")
{
    pd_test_init();

    SECTION("init")
    {
        SECTION("default")
        {
            TExt t("xdac~");
            REQUIRE(t->numInputChannels() == 2);
            REQUIRE(t->numOutputChannels() == 0);
        }

        SECTION("single")
        {
            TExt t("xdac~", LA(1));
            REQUIRE(t->numInputChannels() == 1);
            REQUIRE(t->numOutputChannels() == 0);
        }

        SECTION("3")
        {
            TExt t("xdac~", LA(1, 4, 27));
            REQUIRE(t->numInputChannels() == 3);
            REQUIRE(t->numOutputChannels() == 0);
        }

        SECTION("range")
        {
            TExt t("xdac~", LA("2:6"));
            REQUIRE(t->numInputChannels() == 5);
            REQUIRE(t->numOutputChannels() == 0);
        }
    }
}
