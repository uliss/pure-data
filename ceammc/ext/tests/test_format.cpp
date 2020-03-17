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

#include "ceammc_format.h"

#include "test_common.h"

TEST_CASE("format", "[ceammc::format]")
{
    SECTION("atom format")
    {
        REQUIRE(to_string(Atom(1.1111f)) == "1.1111");
        REQUIRE(to_string(Atom(-3.1415f)) == "-3.1415");
        REQUIRE(to_string(Atom(123)) == "123");
        REQUIRE(to_string(Atom(gensym("1.1"))) == "1.1");

        // float
        REQUIRE(to_float_string(123) == "123");
        REQUIRE(to_float_string(123.12f) == "123.12");
        REQUIRE(to_float_string(gensym("1.1")) == "");

        // hex
        REQUIRE(to_hex_string(255) == "FF");
        REQUIRE(to_hex_string(0xF1) == "F1");
        REQUIRE(to_hex_string(-0xF1) == "-F1");
        REQUIRE(to_hex_string(0x09) == "9");
        REQUIRE(to_hex_string(gensym("255")) == "");
    }

    SECTION("atomlist format")
    {
        REQUIRE(to_string(LF(1.f, 2.f, 3.f)) == "1 2 3");
        REQUIRE(to_string(L()) == "");
    }

    SECTION("message format")
    {
        REQUIRE(to_string(Message(-0.45f)) == "-0.45");
        REQUIRE(to_string(Message(gensym("a b c"))) == "a b c");
        REQUIRE(to_string(Message(AtomList::ones(2))) == "1 1");
        REQUIRE(to_string(Message()) == "");
        REQUIRE(to_string(Message(gensym("a"), AtomList::zeroes(1))) == "a 0");
    }

    SECTION("string escape format")
    {
#define REQUIRE_ESCAPED(a, b)                              \
    {                                                      \
        REQUIRE(to_string_quoted(test_atom_wrap(a)) == b); \
    }

        REQUIRE_ESCAPED("", "\"\"");
        REQUIRE_ESCAPED(123, "123");
        REQUIRE_ESCAPED(123.123, "123.123");
        REQUIRE_ESCAPED("abc", "abc");
        REQUIRE_ESCAPED("a b c", "\"a b c\"");
        REQUIRE_ESCAPED("a b    c", "\"a b    c\"");
        REQUIRE_ESCAPED("there's a table", "\"there's a table\"");
        REQUIRE_ESCAPED(new IntData(123), "123");
        REQUIRE_ESCAPED(new StrData("test string with spaces and q`otes"), "test string with spaces and q`otes");
        REQUIRE_ESCAPED("many ````", "\"many ````\"");
        REQUIRE_ESCAPED("many '''''", "\"many '''''\"");
        REQUIRE_ESCAPED("many \"\"\"\"", "\"many `\"`\"`\"`\"\"");
        REQUIRE_ESCAPED("'double'", "'double'");
        REQUIRE_ESCAPED("\"\"", "\"\"");
        REQUIRE_ESCAPED("\"", "\"");
        REQUIRE_ESCAPED("'`", "'`");
        REQUIRE_ESCAPED("`\"", "`\"");
        REQUIRE_ESCAPED("`\" a", "\"``\" a\"");
        REQUIRE_ESCAPED("\" \"", "\"`\" `\"\"");
        REQUIRE_ESCAPED("\"a ", "\"`\"a \"");
        REQUIRE_ESCAPED("\"a b\"", "\"`\"a b`\"\"");
    }

    SECTION("quote")
    {
        REQUIRE(quote("") == std::string("\"\""));
        REQUIRE(quote("abc") == std::string("\"abc\""));
        // no escaping
        REQUIRE(quote("abc\"") == std::string("\"abc\"\""));
        REQUIRE(quote("abc", '\'') == std::string("'abc'"));
    }

    SECTION("to_json_string")
    {
        REQUIRE(to_json_string(Atom(123)) == "123");
        REQUIRE(to_json_string(Atom(0.5)) == "0.5");
        REQUIRE(to_json_string(Atom(SYM("a b c"))) == "\"a b c\"");
        REQUIRE(to_json_string(Atom(SYM(R"("TEST")"))) == R"("\"TEST\"")");
        REQUIRE(to_json_string(LF(1, 2, 3)) == R"([1, 2, 3])");
        REQUIRE(to_json_string(LA("A", 2, "a b c")) == R"(["A", 2, "a b c"])");
        REQUIRE(to_json_string(LA("\"A\"", 2, "a b c")) == R"(["\"A\"", 2, "a b c"])");
    }
}
