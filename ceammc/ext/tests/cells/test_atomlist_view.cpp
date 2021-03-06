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
#include "catch.hpp"
#include "test_base.h"
#include "test_macro.h"

#include "ceammc_atomlist_view.h"
using namespace ceammc;

#include <algorithm>

TEST_CASE("AtomListView", "core")
{
    SECTION("init")
    {
        SECTION("empty")
        {
            AtomListView av;
            REQUIRE(av.empty());
            REQUIRE(av.size() == 0);
            REQUIRE(av.isNull());
            REQUIRE_FALSE(av.isBool());
            REQUIRE_FALSE(av.isFloat());
            REQUIRE_FALSE(av.isSymbol());
            REQUIRE_FALSE(av.isData());
            REQUIRE_FALSE(av.isA<bool>());
            REQUIRE_FALSE(av.isA<int>());
            REQUIRE_FALSE(av.isA<t_float>());
            REQUIRE_FALSE(av.isA<t_symbol*>());
        }

        SECTION("bool")
        {
            AtomList l0(LA("true"));
            AtomListView lv(l0);

            REQUIRE(lv.isBool());
            REQUIRE(lv.isAtom());
            REQUIRE(lv.isSymbol());
            REQUIRE_FALSE(lv.isInteger());
            REQUIRE_FALSE(lv.isNull());

            REQUIRE(lv == true);
        }

        SECTION("float")
        {
            AtomList l(1.5);
            AtomListView lv(l);
            REQUIRE(lv.asInt() == 1);

            REQUIRE(lv.isFloat());
            REQUIRE(lv.isAtom());
            REQUIRE_FALSE(lv.isInteger());
            REQUIRE_FALSE(lv.isBool());
            REQUIRE_FALSE(lv.isNull());
            REQUIRE_FALSE(lv.isSymbol());
            REQUIRE(lv == t_float(1.5));
            REQUIRE_FALSE(lv == t_float(1.51));
        }

        SECTION("int")
        {
            AtomList l(100);
            AtomListView lv(l);

            REQUIRE(lv.isFloat());
            REQUIRE(lv.isAtom());
            REQUIRE(lv.isInteger());
            REQUIRE_FALSE(lv.isBool());
            REQUIRE_FALSE(lv.isNull());
            REQUIRE_FALSE(lv.isSymbol());
            REQUIRE(lv == 100);
            REQUIRE_FALSE(lv == 101);
        }

        SECTION("symbol")
        {
            AtomList l(LA("ABC"));
            AtomListView lv(l);

            REQUIRE_FALSE(lv.isFloat());
            REQUIRE(lv.isAtom());
            REQUIRE_FALSE(lv.isInteger());
            REQUIRE_FALSE(lv.isBool());
            REQUIRE_FALSE(lv.isNull());
            REQUIRE(lv.isSymbol());
            REQUIRE(lv == SYM("ABC"));
            REQUIRE_FALSE(lv == SYM("AB"));
        }

        SECTION("AtomList")
        {
            AtomList l({ 0, 1, 2, 3, 4 });
            AtomListView lv(l);
            REQUIRE(lv.size() == 5);
            REQUIRE_FALSE(lv.isNull());
            REQUIRE_FALSE(lv.empty());
            REQUIRE_FALSE(lv.isBool());
            REQUIRE_FALSE(lv.isFloat());
            REQUIRE_FALSE(lv.isSymbol());
            REQUIRE(lv[0] == A(0.));
            REQUIRE(lv[1] == A(1));
            REQUIRE(lv[2] == A(2));
            REQUIRE(lv[3] == A(3));
            REQUIRE(lv[4] == A(4));
            REQUIRE(lv.boolAt(0, true) == false);
            REQUIRE(lv.boolAt(0, true) == false);
            REQUIRE(lv.boolAt(1, true) == true);
            REQUIRE(lv.boolAt(1, false) == true);
            REQUIRE(lv.intAt(2, 0) == 2);
            REQUIRE(lv.floatAt(3, 0) == 3);
            REQUIRE(lv.symbolAt(0, nullptr) == nullptr);

            REQUIRE(lv.boolAt(5, true) == true);
            REQUIRE(lv.boolAt(5, false) == false);
            REQUIRE(lv.intAt(5, -1) == -1);
            REQUIRE(lv.floatAt(5, -1) == -1);
            REQUIRE(lv.symbolAt(5, SYM("?")) == SYM("?"));

            REQUIRE(std::all_of(lv.begin(), lv.end(), [](const Atom& a) { return a.isFloat(); }));
            REQUIRE(std::none_of(lv.begin(), lv.end(), [](const Atom& a) { return a.isData(); }));

            // check iteration
            for (auto a : lv) {
            }

            REQUIRE(lv == lv);
            REQUIRE_FALSE(lv != lv);
            // subView
            REQUIRE(lv.subView(0) == l);
            REQUIRE(lv.subView(0) == lv.subView(0, 5));
            REQUIRE(lv.subView(0) == LF(0, 1, 2, 3, 4));
            REQUIRE(lv.subView(1) == LF(1, 2, 3, 4));
            REQUIRE(lv.subView(2) == LF(2, 3, 4));
            REQUIRE(lv.subView(3) == LF(3, 4));
            REQUIRE(lv.subView(4) == LF(4));
            REQUIRE(lv.subView(5) == L());

            REQUIRE(lv.subView(0, 6) == LF(0, 1, 2, 3, 4));
            REQUIRE(lv.subView(0, 5) == LF(0, 1, 2, 3, 4));
            REQUIRE(lv.subView(0, 4) == LF(0, 1, 2, 3));
            REQUIRE(lv.subView(0, 3) == LF(0, 1, 2));
            REQUIRE(lv.subView(0, 2) == LF(0, 1));
            REQUIRE(lv.subView(0, 1) == LF(0));
            REQUIRE(lv.subView(0, 0) == L());

            REQUIRE(lv.subView(1, 5) == LF(1, 2, 3, 4));
            REQUIRE(lv.subView(1, 4) == LF(1, 2, 3, 4));
            REQUIRE(lv.subView(1, 3) == LF(1, 2, 3));
            REQUIRE(lv.subView(1, 2) == LF(1, 2));
            REQUIRE(lv.subView(1, 1) == LF(1));
            REQUIRE(lv.subView(1, 0) == L());

            REQUIRE(lv.subView(2, 4) == LF(2, 3, 4));
            REQUIRE(lv.subView(2, 3) == LF(2, 3, 4));
            REQUIRE(lv.subView(2, 2) == LF(2, 3));
            REQUIRE(lv.subView(2, 1) == LF(2));
            REQUIRE(lv.subView(2, 0) == L());

            REQUIRE(lv.subView(3, 3) == LF(3, 4));
            REQUIRE(lv.subView(3, 2) == LF(3, 4));
            REQUIRE(lv.subView(3, 1) == LF(3));
            REQUIRE(lv.subView(3, 0) == L());

            REQUIRE(lv.subView(4, 2) == LF(4));
            REQUIRE(lv.subView(4, 1) == LF(4));
            REQUIRE(lv.subView(4, 0) == L());

            REQUIRE(lv.subView(5, 1) == L());
            REQUIRE(lv.subView(5, 0) == L());
        }
    }

    SECTION("contains")
    {
        AtomList l({ 1, 2, 3, 4 });
        REQUIRE(l.view().contains(A(1)));
        REQUIRE_FALSE(AtomListView().contains(A(100)));
    }

    SECTION("parse quoted")
    {

#define REQUIRE_ALV_EQ(l0, l1, p)               \
    {                                           \
        AtomList l = l0;                        \
        REQUIRE(l.view().parseQuoted(p) == l1); \
    }

        // empty
        REQUIRE_ALV_EQ(L(), L(), false);
        REQUIRE_ALV_EQ(L(), L(), true);

        // normal atoms
        REQUIRE_ALV_EQ(LA(1, 2, 3, "A"), LA(1, 2, 3, "A"), false);
        REQUIRE_ALV_EQ(LA(1, 2, 3, "A"), LA(1, 2, 3, "A"), true);

        // normal atoms
        REQUIRE_ALV_EQ(LA(1, "'A"), LA(1, "'A"), false);
        REQUIRE_ALV_EQ(LA(1, "'A"), LA(1, "'A"), true);

        // normal atoms
        REQUIRE_ALV_EQ(LA(1, "'A'"), LA(1, "'A'"), false);
        REQUIRE_ALV_EQ(LA(1, "'A'"), LA(1, "'A'"), true);

        // normal atoms
        REQUIRE_ALV_EQ(LA(1, "A'"), LA(1, "A'"), false);
        REQUIRE_ALV_EQ(LA(1, "A'"), LA(1, "A'"), true);

        // unbalanced quotes
        REQUIRE_ALV_EQ(LA(1, "A\""), LA(1, "A\""), false);
        REQUIRE_ALV_EQ(LA(1, "A\""), LA(1, "A\""), true);

        // unbalanced quotes
        REQUIRE_ALV_EQ(LA(1, "\"A"), LA(1, "\"A"), false);
        REQUIRE_ALV_EQ(LA(1, "\"A"), LA(1, "\"A"), true);

        // simple quotes
        REQUIRE_ALV_EQ(LA(1, "\"A\"", 2), LA(1, "A", 2), false);
        REQUIRE_ALV_EQ(LA(1, "\"A\"", 2), LA(1, "A", 2), true);

        // simple quotes
        REQUIRE_ALV_EQ(LA(1, "\"A", "B\"", 2), LA(1, "A B", 2), false);
        REQUIRE_ALV_EQ(LA(1, "\"A", "B\"", 2), LA(1, "A B", 2), true);

        // inner quotes
        REQUIRE_ALV_EQ(LA(1, "\"A`\"", "B\"", 2), LA(1, "A\" B", 2), false);
        REQUIRE_ALV_EQ(LA(1, "\"A`\"", "B\"", 2), LA(1, "A\" B", 2), true);

        // props
        REQUIRE_ALV_EQ(LA(1, "@abc", 2), LA(1, "@abc", 2), false);
        REQUIRE_ALV_EQ(LA(1, "@abc", 2).view(), LA(1, "@abc", 2), true);

        // props
        REQUIRE_ALV_EQ(LA(1, "@abc", "\"@def\""), LA(1, "@abc", "@def"), false);
        REQUIRE_ALV_EQ(LA(1, "@abc", "\"@def\"").view(), LA(1, "@abc", "\"@def\""), true);

        // props
        REQUIRE_ALV_EQ(LA(1, "@abc", "\"@d", "e\""), LA(1, "@abc", "@d e"), false);
        REQUIRE_ALV_EQ(LA(1, "@abc", "\"@d", "e\"").view(), LA(1, "@abc", "@d e"), true);
    }

    SECTION("allOf")
    {

#define REQUIRE_ALL_OF(l0, p)       \
    {                               \
        AtomList l = l0;            \
        REQUIRE(l.view().allOf(p)); \
    }

#define REQUIRE_NOT_ALL_OF(l0, p)         \
    {                                     \
        AtomList l = l0;                  \
        REQUIRE_FALSE(l.view().allOf(p)); \
    }

        REQUIRE_ALL_OF(L(), isFloat);
        REQUIRE_ALL_OF(LF(1, 2, 3), isFloat);
        REQUIRE_ALL_OF(LF(1), isFloat);
        REQUIRE_NOT_ALL_OF(LA("a"), isFloat);
        REQUIRE_NOT_ALL_OF(LA(1, 2, 3, "a"), isFloat);
    }

    SECTION("allOf")
    {

#define REQUIRE_ANY_OF(l0, p)       \
    {                               \
        AtomList l = l0;            \
        REQUIRE(l.view().anyOf(p)); \
    }

#define REQUIRE_NOT_ANY_OF(l0, p)         \
    {                                     \
        AtomList l = l0;                  \
        REQUIRE_FALSE(l.view().anyOf(p)); \
    }

        REQUIRE_NOT_ANY_OF(L(), isFloat);
        REQUIRE_NOT_ANY_OF(LA("a"), isFloat);
        REQUIRE_ANY_OF(LA(1, "a"), isFloat);
        REQUIRE_ANY_OF(LF(1, 2), isFloat);
    }

    SECTION("noneOf")
    {

#define REQUIRE_NONE_OF(l0, p)       \
    {                                \
        AtomList l = l0;             \
        REQUIRE(l.view().noneOf(p)); \
    }

        REQUIRE_NONE_OF(L(), isFloat);
        REQUIRE_NONE_OF(LA("a"), isFloat);
        REQUIRE_NONE_OF(LA(1, 2), isSymbol);
    }

    SECTION("ranges")
    {
        AtomList l = LA("a", -100, 0., 100);
        AtomListView v(l);

        REQUIRE(v.floatLessThenAt(0, 0, -1024) == -1024);
        REQUIRE(v.floatLessThenAt(1, 0, -1024) == -100);
        REQUIRE(v.floatLessThenAt(2, 0, -1024) == -1024);
        REQUIRE(v.floatLessThenAt(3, 0, -1024) == -1024);
        REQUIRE(v.floatLessThenAt(4, 0, -1024) == -1024);
        REQUIRE(v.floatLessThenAt(5, 0, -1024) == -1024);

        REQUIRE(v.floatLessEqualAt(0, 0, -1024) == -1024);
        REQUIRE(v.floatLessEqualAt(1, 0, -1024) == -100);
        REQUIRE(v.floatLessEqualAt(2, 0, -1024) == 0);
        REQUIRE(v.floatLessEqualAt(3, 0, -1024) == -1024);
        REQUIRE(v.floatLessEqualAt(4, 0, -1024) == -1024);
        REQUIRE(v.floatLessEqualAt(5, 0, -1024) == -1024);

        REQUIRE(v.floatGreaterThenAt(0, 0, 1024) == 1024);
        REQUIRE(v.floatGreaterThenAt(1, 0, 1024) == 1024);
        REQUIRE(v.floatGreaterThenAt(2, 0, 1024) == 1024);
        REQUIRE(v.floatGreaterThenAt(3, 0, 1024) == 100);
        REQUIRE(v.floatGreaterThenAt(4, 0, 1024) == 1024);
        REQUIRE(v.floatGreaterThenAt(5, 0, 1024) == 1024);

        REQUIRE(v.floatGreaterEqualAt(0, 0, 1024) == 1024);
        REQUIRE(v.floatGreaterEqualAt(1, 0, 1024) == 1024);
        REQUIRE(v.floatGreaterEqualAt(2, 0, 1024) == 0);
        REQUIRE(v.floatGreaterEqualAt(3, 0, 1024) == 100);
        REQUIRE(v.floatGreaterEqualAt(4, 0, 1024) == 1024);
        REQUIRE(v.floatGreaterEqualAt(5, 0, 1024) == 1024);

        REQUIRE(v.intLessThenAt(0, 0, -1024) == -1024);
        REQUIRE(v.intLessThenAt(1, 0, -1024) == -100);
        REQUIRE(v.intLessThenAt(2, 0, -1024) == -1024);
        REQUIRE(v.intLessThenAt(3, 0, -1024) == -1024);
        REQUIRE(v.intLessThenAt(4, 0, -1024) == -1024);
        REQUIRE(v.intLessThenAt(5, 0, -1024) == -1024);

        REQUIRE(v.intLessEqualAt(0, 0, -1024) == -1024);
        REQUIRE(v.intLessEqualAt(1, 0, -1024) == -100);
        REQUIRE(v.intLessEqualAt(2, 0, -1024) == 0);
        REQUIRE(v.intLessEqualAt(3, 0, -1024) == -1024);
        REQUIRE(v.intLessEqualAt(4, 0, -1024) == -1024);
        REQUIRE(v.intLessEqualAt(5, 0, -1024) == -1024);

        REQUIRE(v.intGreaterThenAt(0, 0, 1024) == 1024);
        REQUIRE(v.intGreaterThenAt(1, 0, 1024) == 1024);
        REQUIRE(v.intGreaterThenAt(2, 0, 1024) == 1024);
        REQUIRE(v.intGreaterThenAt(3, 0, 1024) == 100);
        REQUIRE(v.intGreaterThenAt(4, 0, 1024) == 1024);
        REQUIRE(v.intGreaterThenAt(5, 0, 1024) == 1024);

        REQUIRE(v.intGreaterEqualAt(0, 0, 1024) == 1024);
        REQUIRE(v.intGreaterEqualAt(1, 0, 1024) == 1024);
        REQUIRE(v.intGreaterEqualAt(2, 0, 1024) == 0);
        REQUIRE(v.intGreaterEqualAt(3, 0, 1024) == 100);
        REQUIRE(v.intGreaterEqualAt(4, 0, 1024) == 1024);
        REQUIRE(v.intGreaterEqualAt(5, 0, 1024) == 1024);
    }

    SECTION("back")
    {
        REQUIRE(LF(1, 2, 3, 4, 5).view().back() == 5);
        REQUIRE(LF(1, 2, 3, 4, 5).view().front() == 1);
        REQUIRE(LF(1, 2, 3, 4, 5).view().at(0) == 1);
        REQUIRE(LF(1, 2, 3, 4, 5).view().at(1) == 2);
        REQUIRE(LF(1, 2, 3, 4, 5).view().at(2) == 3);
        REQUIRE(LF(1, 2, 3, 4, 5).view().at(3) == 4);
        REQUIRE(LF(1, 2, 3, 4, 5).view().at(4) == 5);
        REQUIRE(LF(1, 2, 3, 4, 5).view()[0] == 1);
    }
}
