/*****************************************************************************
 * Copyright 2020 Serge Poltavsky. All rights reserved.
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
#include "ceammc_music_scale.h"
#include "test_base.h"

#include "catch.hpp"

using namespace ceammc;
using namespace ceammc::music;

TEST_CASE("scale", "[ceammc::music]")
{
    SECTION("degree to scale")
    {
        SECTION("chromatic 12")
        {
            auto ch12 = ScaleLibrary::instance().find(SYM("chromatic"));
            REQUIRE(ch12);
            REQUIRE(ch12->size() == 12);
            REQUIRE(ch12->pitchesPerOctave() == 12);
            REQUIRE(ch12->name() == SYM("chromatic"));
            REQUIRE(ch12->degrees() == LF(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11));

            for (int i = -100; i < 100; i++)
                REQUIRE(ch12->degreeToKey(i) == i);
        }

        SECTION("chromatic 24")
        {
            auto ch24 = ScaleLibrary::instance().find(SYM("chromatic24"));
            REQUIRE(ch24);
            REQUIRE(ch24->size() == 24);
            REQUIRE(ch24->pitchesPerOctave() == 24);
            REQUIRE(ch24->name() == SYM("chromatic24"));

            for (int i = -100; i < 100; i++)
                REQUIRE(ch24->degreeToKey(i) == i);
        }

        SECTION("major")
        {
            auto maj = ScaleLibrary::instance().find(SYM("major"));
            REQUIRE(maj);
            REQUIRE(maj->size() == 7);
            REQUIRE(maj->pitchesPerOctave() == 12);
            REQUIRE(maj->degrees() == LF(0, 2, 4, 5, 7, 9, 11));
            REQUIRE(maj->name() == SYM("major"));

            REQUIRE(maj->degreeToKey(0) == 0);
            REQUIRE(maj->degreeToKey(1) == 2);
            REQUIRE(maj->degreeToKey(2) == 4);
            REQUIRE(maj->degreeToKey(3) == 5);
            REQUIRE(maj->degreeToKey(4) == 7);
            REQUIRE(maj->degreeToKey(5) == 9);
            REQUIRE(maj->degreeToKey(6) == 11);
            REQUIRE(maj->degreeToKey(7) == 12);
            REQUIRE(maj->degreeToKey(8) == 14);
            REQUIRE(maj->degreeToKey(9) == 16);

            REQUIRE(maj->degreeToKey(-1) == -1);
            REQUIRE(maj->degreeToKey(-2) == -3);
            REQUIRE(maj->degreeToKey(-3) == -5);
            REQUIRE(maj->degreeToKey(-4) == -7);
            REQUIRE(maj->degreeToKey(-5) == -8);
            REQUIRE(maj->degreeToKey(-6) == -10);
            REQUIRE(maj->degreeToKey(-7) == -12);
            REQUIRE(maj->degreeToKey(-8) == -13);
            REQUIRE(maj->degreeToKey(-9) == -15);
        }

        SECTION("whole")
        {
            auto whole = ScaleLibrary::instance().find(SYM("whole"));
            REQUIRE(whole);
            REQUIRE(whole->size() == 6);
            REQUIRE(whole->pitchesPerOctave() == 12);
            REQUIRE(whole->degrees() == LF(0, 2, 4, 6, 8, 10));
            REQUIRE(whole->name() == SYM("whole"));

            for (int i = -16; i < 16; i++)
                REQUIRE(whole->degreeToKey(i) == i * 2);
        }
    }
}
