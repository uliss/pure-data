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
#include "base_extension_test.h"
#include "ceammc_dataatomlist.h"

#include "catch.hpp"

using namespace ceammc;

TEST_CASE("DataAtomList", "[ceammc::DataAtomList]")
{
    SECTION("create")
    {
        SECTION("empty")
        {
            DataAtomList lst;
            REQUIRE(lst.size() == 0);
        }

        SECTION("atom")
        {
            DataAtomList lst(Atom(123));
            REQUIRE(lst.size() == 1);
            REQUIRE(lst[0].toAtom() == Atom(123));
        }

        SECTION("list")
        {
            DataAtomList lst(L3(1, 2, 3));
            REQUIRE(lst.size() == 3);
            REQUIRE(lst.toList() == L3(1, 2, 3));
        }
    }

    SECTION("set")
    {
        DataAtomList lst;
        REQUIRE(lst.size() == 0);

        lst.set(L2(10, 12));
        REQUIRE(lst.size() == 2);
        REQUIRE(lst[0].toAtom() == Atom(10));
        REQUIRE(lst[1].toAtom() == Atom(12));
        REQUIRE(lst.toList() == L2(10, 12));
    }

    SECTION("append")
    {
        DataAtomList lst;
        REQUIRE(lst.size() == 0);
        lst.append(Atom(23));
        REQUIRE(lst.size() == 1);

        lst.append(Atom(24));
        REQUIRE(lst.size() == 2);
        REQUIRE(lst[1].toAtom() == Atom(24));
    }

    SECTION("search")
    {
        DataAtomList lst;
        lst.append(1);
        lst.append(2);
        lst.append(3);
        lst.append(gensym("a"));
        lst.append(new IntData(100));
        lst.append(new StrData("A"));

        REQUIRE(lst.search(Atom()) == -1);
        REQUIRE(lst.search(Atom(gensym("???"))) == -1);
        REQUIRE(lst.search(Atom(0.f)) == -1);
        REQUIRE(lst.search(Atom(1)) == 0);
        REQUIRE(lst.search(Atom(2)) == 1);
        REQUIRE(lst.search(Atom(3)) == 2);
        REQUIRE(lst.search(Atom(100)) == -1);
        REQUIRE(lst.search(Atom(gensym("a"))) == 3);
        REQUIRE(lst.search(new IntData(100)) == 4);
        REQUIRE(lst.search(new IntData(99)) == -1);
        REQUIRE(lst.search(new StrData("A")) == 5);
        REQUIRE(lst.search(new StrData("B")) == -1);

        REQUIRE(lst.search(L2(2, 3)) == 1);
        REQUIRE(lst.search(L2(3, "a")) == 2);
        REQUIRE(lst.search(AtomList()) == -1);

        lst.clear();
        REQUIRE(lst.search(AtomList()) == -1);
        lst.append(10);
        lst.append(20);

        REQUIRE(lst.search(L2(10, 20)) == 0);

        // from
        REQUIRE(lst.search(Atom(1), 2) == -1);
        REQUIRE(lst.search(Atom(2), 2) == -1);
        REQUIRE(lst.search(Atom(3), 2) == 2);
    }

    SECTION("contains")
    {
        DataAtomList lst;
        REQUIRE_FALSE(lst.contains(Atom(10)));
        REQUIRE_FALSE(lst.contains(DataAtom(gensym("sdf"))));
        REQUIRE_FALSE(lst.contains(Atom()));
        REQUIRE_FALSE(lst.contains(AtomList()));

        REQUIRE_FALSE(lst.contains(new IntData(123)));

        lst.append(100);
        REQUIRE_FALSE(lst.contains(Atom(10)));
        REQUIRE_FALSE(lst.contains(DataAtom(gensym("sdf"))));
        REQUIRE_FALSE(lst.contains(new IntData(123)));

        REQUIRE(lst.contains(Atom(100)));
        REQUIRE_FALSE(lst.contains(DataAtom(gensym("100"))));
        REQUIRE_FALSE(lst.contains(new IntData(100)));

        lst.append(new IntData(444));
        REQUIRE(lst.contains(new IntData(444)));
        REQUIRE_FALSE(lst.contains(Atom(444)));

        DataAtom int444(new IntData(444));
        REQUIRE(lst.contains(int444));

        REQUIRE(lst.contains(L2(100, int444.toAtom())));

        // 100, INT(444)
        lst.append(Atom(gensym("a")));
        lst.append(Atom(gensym("b")));
        lst.append(Atom(gensym("c")));

        REQUIRE(lst.contains(Atom(gensym("b"))));
        REQUIRE(lst.contains(L2("a", "b")));
        REQUIRE(lst.contains(L2("b", "c")));
        REQUIRE_FALSE(lst.contains(L2("a", "c")));
        REQUIRE_FALSE(lst.contains(AtomList()));
    }
}
