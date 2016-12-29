/*****************************************************************************
 * Copyright 2016 Serge Poltavsky. All rights reserved.
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
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ceammc_atom.h"
#include <sstream>

using namespace ceammc;

TEST_CASE("Atom", "[ceammc::Atom]")
{
    SECTION("Atom contruct")
    {
        t_atom a;
        SETFLOAT(&a, 1.1f);
        Atom fatom(a);
        REQUIRE(fatom.isFloat());
        REQUIRE_FALSE(fatom.isSymbol());
        REQUIRE(fatom.type() == Atom::FLOAT);
        std::string s;
        REQUIRE_FALSE(fatom.getString(s));
        t_float v;
        REQUIRE(fatom.getFloat(&v));
        CHECK(v == 1.1f);

        Atom b;
        REQUIRE(b.isNone());
    }

    SECTION("Atom attr")
    {
        t_atom a;
        SETSYMBOL(&a, gensym("@attr"));
        Atom atom(a);
        REQUIRE(atom.isProperty());
        REQUIRE_FALSE(notProperty(atom));
        REQUIRE(atom.isSymbol());
        REQUIRE(atom.asString() == "@attr");
        REQUIRE(atom.asSymbol() == gensym("@attr"));

        atom.setFloat(1.f, true);
        REQUIRE(!atom.isProperty());

        atom.setSymbol(gensym(""), true);
        REQUIRE(!atom.isProperty());

        Atom p(gensym("a"));
        REQUIRE(!p.isProperty());
        REQUIRE(p.isSymbol());
    }

    SECTION("Float atom tests")
    {
        Atom fatom(1.99f);
        REQUIRE(fatom.isFloat());
        REQUIRE(fatom.asFloat() == 1.99f);
        t_float v;
        REQUIRE(fatom.getFloat(&v));
        REQUIRE_FALSE(fatom.getFloat(NULL));
        t_symbol* s;
        REQUIRE_FALSE(fatom.getSymbol(&s));
        REQUIRE_FALSE(fatom.getSymbol(NULL));
    }

    SECTION("Type replace")
    {
        t_atom a;
        a.a_type = A_DEFFLOAT;
        Atom fatom(a);
        REQUIRE(fatom.isFloat());
        SETSYMBOL(&a, gensym("a"));
        REQUIRE(a.a_type == A_SYMBOL);
        a.a_type = A_DEFSYMBOL;
        fatom = Atom(a);
        REQUIRE(fatom.isSymbol());

        a.a_type = A_NULL;
        REQUIRE(Atom(a).type() == Atom::NONE);
    }

    SECTION("Symbol atom tests")
    {
        Atom satom(gensym("test"));
        REQUIRE_FALSE(satom.isFloat());
        REQUIRE(satom.type() == Atom::SYMBOL);
        REQUIRE(satom.asSymbol() == gensym("test"));
        REQUIRE(satom.asString() == "test");
        t_symbol* s;
        REQUIRE(satom.getSymbol(&s));
        REQUIRE_FALSE(satom.getSymbol(NULL));
        t_float v;
        REQUIRE_FALSE(satom.getFloat(NULL));
        REQUIRE_FALSE(satom.getFloat(&v));
        std::string str;
        REQUIRE(satom.getString(str));
        REQUIRE(str == "test");
    }

    SECTION("set tests")
    {
        Atom a1(1.2f);
        REQUIRE(a1.setFloat(2.0f));
        REQUIRE(a1.isFloat());
        REQUIRE(a1.setFloat(3.0f, true));
        REQUIRE(a1.isFloat());
        REQUIRE_FALSE(a1.setSymbol(0));
        REQUIRE(a1.isFloat());
        // setting null pointer
        REQUIRE(a1.setSymbol(0, true));
        REQUIRE_FALSE(a1.isSymbol());
        REQUIRE(a1.setSymbol(gensym("a"), true));
        REQUIRE(a1.isSymbol());

        Atom a2(gensym("test"));
        REQUIRE(a2.setSymbol(gensym("test2")));
        REQUIRE(a2.isSymbol());
        REQUIRE(a2.setSymbol(gensym("test2"), true));
        REQUIRE(a2.isSymbol());

        REQUIRE_FALSE(a2.setFloat(1));
        REQUIRE(a2.isSymbol());
        REQUIRE(a2.setFloat(1, true));
        REQUIRE(a2.isFloat());
    }

    SECTION("equal tests")
    {
        Atom a1(1.2f);
        Atom a2(1.2f);

        REQUIRE(a1 == a1);
        REQUIRE_FALSE(a1 != a1);
        REQUIRE(a1 == a2);

        a2.setFloat(1.3f);
        REQUIRE(a1 != a2);

        Atom a3(a2);
        REQUIRE(a3 == a2);

        Atom a4(1.0f);
        a4 = a2;
        REQUIRE(a4 == a2);

        Atom s1(gensym("test"));
        Atom s2(gensym("test"));
        REQUIRE(s1 == s2);

        Atom s3(gensym("test2"));
        REQUIRE(s1 != s3);

        REQUIRE(s1 != a1);

        t_atom p;
        p.a_type = A_NULL;
        Atom u1(p);
        Atom u2(p);
        REQUIRE(u1 != u2);
    }

    SECTION("compare tests")
    {
        Atom a1(1.0);

        REQUIRE_FALSE(a1 < a1);
        Atom a2(1.0);
        REQUIRE_FALSE(a1 < a2);
        a2.setFloat(1.0001);
        REQUIRE(a1 < a2);

        Atom s1(gensym("test"));
        REQUIRE(a1 < s1);

        Atom s2(gensym("test"));
        REQUIRE_FALSE(s1 < s2);

        Atom s3(gensym("a"));
        Atom s4(gensym("b"));
        REQUIRE(s3 < s4);

        t_atom r1;
        r1.a_type = A_NULL;
        t_atom r2;
        r2.a_type = A_NULL;
        REQUIRE_FALSE(Atom(r1) < Atom(r2));
    }

    SECTION("test output")
    {
        {
            Atom a1;
            std::ostringstream ss;
            ss << a1;
            REQUIRE(ss.str() == "NONE");
        }

        {
            Atom a1(1.23f);
            std::ostringstream ss;
            ss << a1;
            REQUIRE(ss.str() == "1.23");
        }

        {
            Atom a1(gensym("test"));
            std::ostringstream ss;
            ss << a1;
            REQUIRE(ss.str() == "test");
        }
    }

    SECTION("test as int") {
        Atom a1(1.34f);
        REQUIRE(a1.asInt(0) == 1);

        Atom a2(gensym("a"));
        REQUIRE(a2.asInt(-30) == -30);
    }

    SECTION("test as size_t") {
        Atom a1(21.34f);
        REQUIRE(a1.asSizeT(0) == 21);

        Atom a2(gensym("a"));
        REQUIRE(a2.asSizeT(30) == 30);

        Atom a3(-132.f);
        REQUIRE(a3.asSizeT(10) == 10);
    }
}
