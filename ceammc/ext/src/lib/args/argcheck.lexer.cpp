// argcheck.lexer.cpp generated by reflex 3.0.1 from argcheck.l

#define REFLEX_VERSION "3.0.1"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  OPTIONS USED                                                              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define REFLEX_OPTION_YYLTYPE             ceammc::argcheck::location
#define REFLEX_OPTION_YYSTYPE             ceammc::argcheck::ArgCheckParser::semantic_type
#define REFLEX_OPTION_bison_cc            true
#define REFLEX_OPTION_bison_cc_namespace  ceammc::argcheck
#define REFLEX_OPTION_bison_cc_parser     ArgCheckParser
#define REFLEX_OPTION_bison_complete      true
#define REFLEX_OPTION_fast                true
#define REFLEX_OPTION_freespace           true
#define REFLEX_OPTION_header_file         "argcheck.lexer.h"
#define REFLEX_OPTION_lex                 lex
#define REFLEX_OPTION_lexer               ArgCheckLexer
#define REFLEX_OPTION_namespace           ceammc::argcheck
#define REFLEX_OPTION_noyywrap            true
#define REFLEX_OPTION_outfile             "argcheck.lexer.cpp"
#define REFLEX_OPTION_reentrant           true
#define REFLEX_OPTION_token_eof           ceammc::argcheck::ArgCheckParser::symbol_type(0)
#define REFLEX_OPTION_token_type          ceammc::argcheck::ArgCheckParser::symbol_type
#define REFLEX_OPTION_unicode             true

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %top user code                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 1 "argcheck.l"

    # include <string>
    # include <memory>

    # include "argcheck.parser.hpp"
    using token = ceammc::argcheck::ArgCheckParser::token;


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  REGEX MATCHER                                                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <reflex/matcher.h>

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  ABSTRACT LEXER CLASS                                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <reflex/abslexer.h>

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  LEXER CLASS                                                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

namespace ceammc {
namespace argcheck {

class ArgCheckLexer : public reflex::AbstractLexer<reflex::Matcher> {
 public:
  typedef reflex::AbstractLexer<reflex::Matcher> AbstractBaseLexer;
  ArgCheckLexer(
      const reflex::Input& input = reflex::Input(),
      std::ostream&        os    = std::cout)
    :
      AbstractBaseLexer(input, os)
  {
  }
  static const int INITIAL = 0;
  virtual ceammc::argcheck::ArgCheckParser::symbol_type lex(void);
};

} // namespace ceammc
} // namespace argcheck

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %{ user code %}                                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 14 "argcheck.l"
/*%option graphs-file*/
/*%option debug*/

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  BISON C++                                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 2: rules                                                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

namespace ceammc {
namespace argcheck {
extern void reflex_code_INITIAL(reflex::Matcher&);
} // namespace ceammc
} // namespace argcheck

ceammc::argcheck::ArgCheckParser::symbol_type ceammc::argcheck::ArgCheckLexer::lex(void)
{
  static const reflex::Pattern PATTERN_INITIAL(reflex_code_INITIAL);
  if (!has_matcher())
  {
    matcher(new Matcher(PATTERN_INITIAL, stdinit(), this));
  }
  while (true)
  {
        switch (matcher().scan())
        {
          case 0:
            if (matcher().at_end())
            {
              return ceammc::argcheck::ArgCheckParser::symbol_type(0);
            }
            else
            {
              out().put(matcher().input());
            }
            break;
          case 1: // rule argcheck.l:42: a :
#line 42 "argcheck.l"
{ return token::TATOM; }
            break;
          case 2: // rule argcheck.l:43: b :
#line 43 "argcheck.l"
{ return token::TBOOL; }
            break;
          case 3: // rule argcheck.l:44: d :
#line 44 "argcheck.l"
{ return token::TDATA; }
            break;
          case 4: // rule argcheck.l:45: f :
#line 45 "argcheck.l"
{ return token::TFLOAT; }
            break;
          case 5: // rule argcheck.l:46: f/{float_range} :
#line 46 "argcheck.l"
{ return token::TFLOAT; } // to prevent {symbol} longest match in f2..4 case
            break;
          case 6: // rule argcheck.l:47: s :
#line 47 "argcheck.l"
{ return token::TSYMBOL; }
            break;
          case 7: // rule argcheck.l:48: i :
#line 48 "argcheck.l"
{ return token::TINT; } // for simple i types
            break;
          case 8: // rule argcheck.l:49: i/{int_range} :
#line 49 "argcheck.l"
{ return token::TINT; } // to prevent {symbol} longest match in i2..4 case
            break;
          case 9: // rule argcheck.l:50: \+ :
#line 50 "argcheck.l"
{ return token::PLUS; }
            break;
          case 10: // rule argcheck.l:51: \* :
#line 51 "argcheck.l"
{ return token::ASTERISK; }
            break;
          case 11: // rule argcheck.l:52: \? :
#line 52 "argcheck.l"
{ return token::QUESTION; }
            break;
          case 12: // rule argcheck.l:53: \[ :
#line 53 "argcheck.l"
{ return token::REPEAT_START; }
            break;
          case 13: // rule argcheck.l:54: \] :
#line 54 "argcheck.l"
{ return token::REPEAT_END; }
            break;
          case 14: // rule argcheck.l:55: \( :
#line 55 "argcheck.l"
{ return token::GROUP_START; }
            break;
          case 15: // rule argcheck.l:56: \) :
#line 56 "argcheck.l"
{ return token::GROUP_END; }
            break;
          case 16: // rule argcheck.l:57: \| :
#line 57 "argcheck.l"
{ return token::OR; }
            break;
          case 17: // rule argcheck.l:58: % :
#line 58 "argcheck.l"
{ return token::MODULUS; }
            break;
          case 18: // rule argcheck.l:59: <= :
#line 59 "argcheck.l"
{ return token::LE; }
            break;
          case 19: // rule argcheck.l:60: < :
#line 60 "argcheck.l"
{ return token::LT; }
            break;
          case 20: // rule argcheck.l:61: >= :
#line 61 "argcheck.l"
{ return token::GE; }
            break;
          case 21: // rule argcheck.l:62: > :
#line 62 "argcheck.l"
{ return token::GT; }
            break;
          case 22: // rule argcheck.l:63: != :
#line 63 "argcheck.l"
{ return token::NE; }
            break;
          case 23: // rule argcheck.l:64: = :
#line 64 "argcheck.l"
{ return token::EQ; }
            break;
          case 24: // rule argcheck.l:65: ~ :
#line 65 "argcheck.l"
{ return token::TILDE; }
            break;
          case 25: // rule argcheck.l:66: \^ :
#line 66 "argcheck.l"
{ return token::CAPS; }
            break;
          case 26: // rule argcheck.l:67: \^2 :
#line 67 "argcheck.l"
{ return token::POWER_OF_TWO; }
            break;
          case 27: // rule argcheck.l:68: \$ :
#line 68 "argcheck.l"
{ return token::DOLLAR; }
            break;
          case 28: // rule argcheck.l:69: {space} :
#line 69 "argcheck.l"
{ ; }
            break;
          case 29: // rule argcheck.l:70: {range} :
#line 70 "argcheck.l"
{ return token::REPEAT_RANGE; }
            break;
          case 30: // rule argcheck.l:71: {int} :
#line 71 "argcheck.l"
{ return ArgCheckParser::make_INTEGER(std::strtol(text(), 0, 10)); }
            break;
          case 31: // rule argcheck.l:72: {float} :
#line 72 "argcheck.l"
{ return ArgCheckParser::make_FLOAT(std::strtod(text(), 0)); }

            break;
          case 32: // rule argcheck.l:74: {sqstring} :
#line 74 "argcheck.l"
{
                    const auto N = strlen(text()) - 2;
                    return ArgCheckParser::make_STRING(std::string(text() + 1, N));
                }

            break;
          case 33: // rule argcheck.l:79: {dqstring} :
#line 79 "argcheck.l"
{
                    const auto N = strlen(text()) - 2;
                    return ArgCheckParser::make_STRING(std::string(text() + 1, N));
                }


            break;
          case 34: // rule argcheck.l:85: {symbol} :
#line 85 "argcheck.l"
{ return ArgCheckParser::make_SYMBOL(text()); }
            break;
          case 35: // rule argcheck.l:86: . :
#line 86 "argcheck.l"
{ return ArgCheckParser::make_SYMBOL(text()); }

            break;
        }
  }
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 3: user code                                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 89 "argcheck.l"


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  TABLES                                                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <reflex/matcher.h>

#if defined(OS_WIN)
#pragma warning(disable:4101 4102)
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-label"
#elif defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-label"
#endif

namespace ceammc {
namespace argcheck {

void reflex_code_INITIAL(reflex::Matcher& m)
{
  int c0 = 0, c1 = 0;
  m.FSM_INIT(c1);

S0:
  m.FSM_FIND();
  c1 = m.FSM_CHAR();
  if (c1 == '~') goto S115;
  if (c1 == '|') goto S100;
  if (c1 == 's') goto S66;
  if (c1 == 'i') goto S73;
  if (c1 == 'f') goto S55;
  if (c1 == 'd') goto S48;
  if ('c' <= c1 && c1 <= 'z') goto S174;
  if (c1 == 'b') goto S41;
  if (c1 == 'a') goto S34;
  if (c1 == '_') goto S174;
  if (c1 == '^') goto S117;
  if (c1 == ']') goto S94;
  if (c1 == '[') goto S92;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if (c1 == '?') goto S90;
  if (c1 == '>') goto S107;
  if (c1 == '=') goto S113;
  if (c1 == '<') goto S104;
  if ('1' <= c1 && c1 <= '9') goto S132;
  if (c1 == '0') goto S129;
  if (c1 == '.') goto S122;
  if (c1 == '-') goto S187;
  if (c1 == '+') goto S84;
  if (c1 == '*') goto S88;
  if (c1 == ')') goto S98;
  if (c1 == '(') goto S96;
  if (c1 == '\'') goto S136;
  if (c1 == '%') goto S102;
  if (c1 == '$') goto S120;
  if (c1 == '"') goto S155;
  if (c1 == '!') goto S110;
  if (c1 == ' ') goto S183;
  if ('\t' <= c1 && c1 <= '\n') goto S183;
  if (0 <= c1) goto S181;
  return m.FSM_HALT(c1);

S34:
  m.FSM_TAKE(1);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S174;
  if (c1 == '.') goto S174;
  return m.FSM_HALT(c1);

S41:
  m.FSM_TAKE(2);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S174;
  if (c1 == '.') goto S174;
  return m.FSM_HALT(c1);

S48:
  m.FSM_TAKE(3);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S174;
  if (c1 == '.') goto S174;
  return m.FSM_HALT(c1);

S55:
  m.FSM_TAKE(4);
  m.FSM_HEAD(0);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('1' <= c1 && c1 <= '9') goto S198;
  if (c1 == '0') goto S191;
  if (c1 == '.') goto S174;
  if (c1 == '-') goto S205;
  if (c1 == '+') goto S205;
  return m.FSM_HALT(c1);

S66:
  m.FSM_TAKE(6);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S174;
  if (c1 == '.') goto S174;
  return m.FSM_HALT(c1);

S73:
  m.FSM_TAKE(7);
  m.FSM_HEAD(1);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('1' <= c1 && c1 <= '9') goto S215;
  if (c1 == '0') goto S208;
  if (c1 == '.') goto S174;
  if (c1 == '-') goto S222;
  if (c1 == '+') goto S222;
  return m.FSM_HALT(c1);

S84:
  m.FSM_TAKE(9);
  c1 = m.FSM_CHAR();
  if ('1' <= c1 && c1 <= '9') goto S132;
  if (c1 == '0') goto S129;
  return m.FSM_HALT(c1);

S88:
  m.FSM_TAKE(10);
  return m.FSM_HALT();

S90:
  m.FSM_TAKE(11);
  return m.FSM_HALT();

S92:
  m.FSM_TAKE(12);
  return m.FSM_HALT();

S94:
  m.FSM_TAKE(13);
  return m.FSM_HALT();

S96:
  m.FSM_TAKE(14);
  return m.FSM_HALT();

S98:
  m.FSM_TAKE(15);
  return m.FSM_HALT();

S100:
  m.FSM_TAKE(16);
  return m.FSM_HALT();

S102:
  m.FSM_TAKE(17);
  return m.FSM_HALT();

S104:
  m.FSM_TAKE(19);
  c1 = m.FSM_CHAR();
  if (c1 == '=') goto S225;
  return m.FSM_HALT(c1);

S107:
  m.FSM_TAKE(21);
  c1 = m.FSM_CHAR();
  if (c1 == '=') goto S227;
  return m.FSM_HALT(c1);

S110:
  m.FSM_TAKE(35);
  c1 = m.FSM_CHAR();
  if (c1 == '=') goto S229;
  return m.FSM_HALT(c1);

S113:
  m.FSM_TAKE(23);
  return m.FSM_HALT();

S115:
  m.FSM_TAKE(24);
  return m.FSM_HALT();

S117:
  m.FSM_TAKE(25);
  c1 = m.FSM_CHAR();
  if (c1 == '2') goto S231;
  return m.FSM_HALT(c1);

S120:
  m.FSM_TAKE(27);
  return m.FSM_HALT();

S122:
  m.FSM_TAKE(34);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S174;
  if (c1 == '.') goto S233;
  return m.FSM_HALT(c1);

S129:
  m.FSM_TAKE(30);
  c1 = m.FSM_CHAR();
  if (c1 == '.') goto S245;
  return m.FSM_HALT(c1);

S132:
  m.FSM_TAKE(30);
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S132;
  if (c1 == '.') goto S245;
  return m.FSM_HALT(c1);

S136:
  m.FSM_TAKE(35);
  c1 = m.FSM_CHAR();
  if (c1 == 244) goto S298;
  if (241 <= c1 && c1 <= 243) goto S296;
  if (c1 == 240) goto S294;
  if (238 <= c1 && c1 <= 239) goto S292;
  if (c1 == 237) goto S290;
  if (225 <= c1 && c1 <= 236) goto S288;
  if (c1 == 224) goto S286;
  if (194 <= c1 && c1 <= 223) goto S284;
  if ('~' <= c1 && c1 <= 127) goto S266;
  if (c1 == '|') goto S266;
  if ('v' <= c1 && c1 <= 'z') goto S266;
  if (c1 == 'r') goto S266;
  if (c1 == 'p') goto S266;
  if ('f' <= c1 && c1 <= 'n') goto S266;
  if ('e' <= c1) return m.FSM_HALT(c1);
  if (c1 == '`') goto S300;
  if (c1 == '\'') goto S247;
  if (0 <= c1 && c1 <= 'd') goto S266;
  return m.FSM_HALT(c1);

S155:
  m.FSM_TAKE(35);
  c1 = m.FSM_CHAR();
  if (c1 == 244) goto S369;
  if (241 <= c1 && c1 <= 243) goto S367;
  if (c1 == 240) goto S365;
  if (238 <= c1 && c1 <= 239) goto S363;
  if (c1 == 237) goto S361;
  if (225 <= c1 && c1 <= 236) goto S359;
  if (c1 == 224) goto S357;
  if (194 <= c1 && c1 <= 223) goto S355;
  if ('~' <= c1 && c1 <= 127) goto S337;
  if (c1 == '|') goto S337;
  if ('v' <= c1 && c1 <= 'z') goto S337;
  if ('r' <= c1 && c1 <= 's') goto S337;
  if (c1 == 'p') goto S337;
  if ('f' <= c1 && c1 <= 'n') goto S337;
  if ('d' <= c1) return m.FSM_HALT(c1);
  if (c1 == '`') goto S371;
  if (c1 == '"') goto S318;
  if (0 <= c1 && c1 <= 'c') goto S337;
  return m.FSM_HALT(c1);

S174:
  m.FSM_TAKE(34);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S174;
  if (c1 == '.') goto S174;
  return m.FSM_HALT(c1);

S181:
  m.FSM_TAKE(35);
  return m.FSM_HALT();

S183:
  m.FSM_TAKE(28);
  c1 = m.FSM_CHAR();
  if (c1 == ' ') goto S183;
  if ('\t' <= c1 && c1 <= '\n') goto S183;
  return m.FSM_HALT(c1);

S187:
  m.FSM_TAKE(35);
  c1 = m.FSM_CHAR();
  if ('1' <= c1 && c1 <= '9') goto S132;
  if (c1 == '0') goto S129;
  return m.FSM_HALT(c1);

S191:
  m.FSM_TAKE(34);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S174;
  if (c1 == '.') goto S389;
  return m.FSM_HALT(c1);

S198:
  m.FSM_TAKE(34);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S198;
  if (c1 == '.') goto S389;
  return m.FSM_HALT(c1);

S205:
  c1 = m.FSM_CHAR();
  if ('1' <= c1 && c1 <= '9') goto S398;
  if (c1 == '0') goto S396;
  return m.FSM_HALT(c1);

S208:
  m.FSM_TAKE(34);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S174;
  if (c1 == '.') goto S401;
  return m.FSM_HALT(c1);

S215:
  m.FSM_TAKE(34);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S215;
  if (c1 == '.') goto S401;
  return m.FSM_HALT(c1);

S222:
  c1 = m.FSM_CHAR();
  if ('1' <= c1 && c1 <= '9') goto S410;
  if (c1 == '0') goto S408;
  return m.FSM_HALT(c1);

S225:
  m.FSM_TAKE(18);
  return m.FSM_HALT();

S227:
  m.FSM_TAKE(20);
  return m.FSM_HALT();

S229:
  m.FSM_TAKE(22);
  return m.FSM_HALT();

S231:
  m.FSM_TAKE(26);
  return m.FSM_HALT();

S233:
  m.FSM_TAKE(34);
  m.FSM_HEAD(2);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if (c1 == ']') goto S429;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('1' <= c1 && c1 <= '9') goto S421;
  if (c1 == '0') goto S413;
  if (c1 == '.') goto S174;
  if (c1 == '-') goto S432;
  if (c1 == '+') goto S432;
  return m.FSM_HALT(c1);

S245:
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S435;
  return m.FSM_HALT(c1);

S247:
  m.FSM_TAKE(32);
  c1 = m.FSM_CHAR();
  if (c1 == 244) goto S298;
  if (241 <= c1 && c1 <= 243) goto S296;
  if (c1 == 240) goto S294;
  if (238 <= c1 && c1 <= 239) goto S292;
  if (c1 == 237) goto S290;
  if (225 <= c1 && c1 <= 236) goto S288;
  if (c1 == 224) goto S286;
  if (194 <= c1 && c1 <= 223) goto S284;
  if ('~' <= c1 && c1 <= 127) goto S266;
  if (c1 == '|') goto S266;
  if ('v' <= c1 && c1 <= 'z') goto S266;
  if (c1 == 'r') goto S266;
  if (c1 == 'p') goto S266;
  if ('f' <= c1 && c1 <= 'n') goto S266;
  if ('e' <= c1) return m.FSM_HALT(c1);
  if (c1 == '`') goto S300;
  if (c1 == '\'') goto S247;
  if (0 <= c1 && c1 <= 'd') goto S266;
  return m.FSM_HALT(c1);

S266:
  c1 = m.FSM_CHAR();
  if (c1 == 244) goto S298;
  if (241 <= c1 && c1 <= 243) goto S296;
  if (c1 == 240) goto S294;
  if (238 <= c1 && c1 <= 239) goto S292;
  if (c1 == 237) goto S290;
  if (225 <= c1 && c1 <= 236) goto S288;
  if (c1 == 224) goto S286;
  if (194 <= c1 && c1 <= 223) goto S284;
  if ('~' <= c1 && c1 <= 127) goto S266;
  if (c1 == '|') goto S266;
  if ('v' <= c1 && c1 <= 'z') goto S266;
  if (c1 == 'r') goto S266;
  if (c1 == 'p') goto S266;
  if ('f' <= c1 && c1 <= 'n') goto S266;
  if ('e' <= c1) return m.FSM_HALT(c1);
  if (c1 == '`') goto S300;
  if (c1 == '\'') goto S247;
  if (0 <= c1 && c1 <= 'd') goto S266;
  return m.FSM_HALT(c1);

S284:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S266;
  return m.FSM_HALT(c1);

S286:
  c1 = m.FSM_CHAR();
  if (160 <= c1 && c1 <= 191) goto S438;
  return m.FSM_HALT(c1);

S288:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S440;
  return m.FSM_HALT(c1);

S290:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 159) goto S442;
  return m.FSM_HALT(c1);

S292:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S444;
  return m.FSM_HALT(c1);

S294:
  c1 = m.FSM_CHAR();
  if (144 <= c1 && c1 <= 191) goto S446;
  return m.FSM_HALT(c1);

S296:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S448;
  return m.FSM_HALT(c1);

S298:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 143) goto S450;
  return m.FSM_HALT(c1);

S300:
  c1 = m.FSM_CHAR();
  if (c1 == 244) goto S298;
  if (241 <= c1 && c1 <= 243) goto S296;
  if (c1 == 240) goto S294;
  if (238 <= c1 && c1 <= 239) goto S292;
  if (c1 == 237) goto S290;
  if (225 <= c1 && c1 <= 236) goto S288;
  if (c1 == 224) goto S286;
  if (194 <= c1 && c1 <= 223) goto S284;
  if ('~' <= c1 && c1 <= 127) goto S266;
  if (c1 == '|') goto S266;
  if ('v' <= c1 && c1 <= 'z') goto S266;
  if (c1 == 'r') goto S266;
  if (c1 == 'p') goto S266;
  if ('f' <= c1 && c1 <= 'n') goto S266;
  if ('e' <= c1) return m.FSM_HALT(c1);
  if (c1 == '`') goto S300;
  if (c1 == '\'') goto S247;
  if (0 <= c1 && c1 <= 'd') goto S266;
  return m.FSM_HALT(c1);

S318:
  m.FSM_TAKE(33);
  c1 = m.FSM_CHAR();
  if (c1 == 244) goto S369;
  if (241 <= c1 && c1 <= 243) goto S367;
  if (c1 == 240) goto S365;
  if (238 <= c1 && c1 <= 239) goto S363;
  if (c1 == 237) goto S361;
  if (225 <= c1 && c1 <= 236) goto S359;
  if (c1 == 224) goto S357;
  if (194 <= c1 && c1 <= 223) goto S355;
  if ('~' <= c1 && c1 <= 127) goto S337;
  if (c1 == '|') goto S337;
  if ('v' <= c1 && c1 <= 'z') goto S337;
  if ('r' <= c1 && c1 <= 's') goto S337;
  if (c1 == 'p') goto S337;
  if ('f' <= c1 && c1 <= 'n') goto S337;
  if ('d' <= c1) return m.FSM_HALT(c1);
  if (c1 == '`') goto S371;
  if (c1 == '"') goto S318;
  if (0 <= c1 && c1 <= 'c') goto S337;
  return m.FSM_HALT(c1);

S337:
  c1 = m.FSM_CHAR();
  if (c1 == 244) goto S369;
  if (241 <= c1 && c1 <= 243) goto S367;
  if (c1 == 240) goto S365;
  if (238 <= c1 && c1 <= 239) goto S363;
  if (c1 == 237) goto S361;
  if (225 <= c1 && c1 <= 236) goto S359;
  if (c1 == 224) goto S357;
  if (194 <= c1 && c1 <= 223) goto S355;
  if ('~' <= c1 && c1 <= 127) goto S337;
  if (c1 == '|') goto S337;
  if ('v' <= c1 && c1 <= 'z') goto S337;
  if ('r' <= c1 && c1 <= 's') goto S337;
  if (c1 == 'p') goto S337;
  if ('f' <= c1 && c1 <= 'n') goto S337;
  if ('d' <= c1) return m.FSM_HALT(c1);
  if (c1 == '`') goto S371;
  if (c1 == '"') goto S318;
  if (0 <= c1 && c1 <= 'c') goto S337;
  return m.FSM_HALT(c1);

S355:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S337;
  return m.FSM_HALT(c1);

S357:
  c1 = m.FSM_CHAR();
  if (160 <= c1 && c1 <= 191) goto S452;
  return m.FSM_HALT(c1);

S359:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S454;
  return m.FSM_HALT(c1);

S361:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 159) goto S456;
  return m.FSM_HALT(c1);

S363:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S458;
  return m.FSM_HALT(c1);

S365:
  c1 = m.FSM_CHAR();
  if (144 <= c1 && c1 <= 191) goto S460;
  return m.FSM_HALT(c1);

S367:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S462;
  return m.FSM_HALT(c1);

S369:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 143) goto S464;
  return m.FSM_HALT(c1);

S371:
  c1 = m.FSM_CHAR();
  if (c1 == 244) goto S369;
  if (241 <= c1 && c1 <= 243) goto S367;
  if (c1 == 240) goto S365;
  if (238 <= c1 && c1 <= 239) goto S363;
  if (c1 == 237) goto S361;
  if (225 <= c1 && c1 <= 236) goto S359;
  if (c1 == 224) goto S357;
  if (194 <= c1 && c1 <= 223) goto S355;
  if ('~' <= c1 && c1 <= 127) goto S337;
  if (c1 == '|') goto S337;
  if ('v' <= c1 && c1 <= 'z') goto S337;
  if ('r' <= c1 && c1 <= 's') goto S337;
  if (c1 == 'p') goto S337;
  if ('f' <= c1 && c1 <= 'n') goto S337;
  if ('d' <= c1) return m.FSM_HALT(c1);
  if (c1 == '`') goto S371;
  if (c1 == '"') goto S318;
  if (0 <= c1 && c1 <= 'c') goto S337;
  return m.FSM_HALT(c1);

S389:
  m.FSM_TAKE(34);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S476;
  if (c1 == '.') goto S466;
  return m.FSM_HALT(c1);

S396:
  c1 = m.FSM_CHAR();
  if (c1 == '.') goto S483;
  return m.FSM_HALT(c1);

S398:
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S398;
  if (c1 == '.') goto S483;
  return m.FSM_HALT(c1);

S401:
  m.FSM_TAKE(34);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S174;
  if (c1 == '.') goto S486;
  return m.FSM_HALT(c1);

S408:
  c1 = m.FSM_CHAR();
  if (c1 == '.') goto S496;
  return m.FSM_HALT(c1);

S410:
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S410;
  if (c1 == '.') goto S496;
  return m.FSM_HALT(c1);

S413:
  m.FSM_TAKE(29);
  m.FSM_TAIL(2);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S174;
  if (c1 == '.') goto S498;
  return m.FSM_HALT(c1);

S421:
  m.FSM_TAKE(29);
  m.FSM_TAIL(2);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S421;
  if (c1 == '.') goto S498;
  return m.FSM_HALT(c1);

S429:
  m.FSM_TAKE(29);
  m.FSM_TAIL(2);
  return m.FSM_HALT();

S432:
  c1 = m.FSM_CHAR();
  if ('1' <= c1 && c1 <= '9') goto S509;
  if (c1 == '0') goto S505;
  return m.FSM_HALT(c1);

S435:
  m.FSM_TAKE(31);
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S435;
  return m.FSM_HALT(c1);

S438:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S266;
  return m.FSM_HALT(c1);

S440:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S266;
  return m.FSM_HALT(c1);

S442:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S266;
  return m.FSM_HALT(c1);

S444:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S266;
  return m.FSM_HALT(c1);

S446:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S514;
  return m.FSM_HALT(c1);

S448:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S516;
  return m.FSM_HALT(c1);

S450:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S518;
  return m.FSM_HALT(c1);

S452:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S337;
  return m.FSM_HALT(c1);

S454:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S337;
  return m.FSM_HALT(c1);

S456:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S337;
  return m.FSM_HALT(c1);

S458:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S337;
  return m.FSM_HALT(c1);

S460:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S520;
  return m.FSM_HALT(c1);

S462:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S522;
  return m.FSM_HALT(c1);

S464:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S524;
  return m.FSM_HALT(c1);

S466:
  m.FSM_TAKE(34);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('1' <= c1 && c1 <= '9') goto S534;
  if (c1 == '0') goto S526;
  if (c1 == '.') goto S174;
  if (c1 == '-') goto S542;
  if (c1 == '+') goto S542;
  return m.FSM_HALT(c1);

S476:
  m.FSM_TAKE(34);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S476;
  if (c1 == '.') goto S545;
  return m.FSM_HALT(c1);

S483:
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S557;
  if (c1 == '.') goto S552;
  return m.FSM_HALT(c1);

S486:
  m.FSM_TAKE(34);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('1' <= c1 && c1 <= '9') goto S568;
  if (c1 == '0') goto S560;
  if (c1 == '.') goto S174;
  if (c1 == '-') goto S576;
  if (c1 == '+') goto S576;
  return m.FSM_HALT(c1);

S496:
  c1 = m.FSM_CHAR();
  if (c1 == '.') goto S579;
  return m.FSM_HALT(c1);

S498:
  m.FSM_TAKE(34);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S584;
  if (c1 == '.') goto S174;
  return m.FSM_HALT(c1);

S505:
  m.FSM_TAKE(29);
  m.FSM_TAIL(2);
  c1 = m.FSM_CHAR();
  if (c1 == '.') goto S592;
  return m.FSM_HALT(c1);

S509:
  m.FSM_TAKE(29);
  m.FSM_TAIL(2);
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S509;
  if (c1 == '.') goto S592;
  return m.FSM_HALT(c1);

S514:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S266;
  return m.FSM_HALT(c1);

S516:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S266;
  return m.FSM_HALT(c1);

S518:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S266;
  return m.FSM_HALT(c1);

S520:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S337;
  return m.FSM_HALT(c1);

S522:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S337;
  return m.FSM_HALT(c1);

S524:
  c1 = m.FSM_CHAR();
  if (128 <= c1 && c1 <= 191) goto S337;
  return m.FSM_HALT(c1);

S526:
  m.FSM_TAKE(5);
  m.FSM_TAIL(0);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S174;
  if (c1 == '.') goto S594;
  return m.FSM_HALT(c1);

S534:
  m.FSM_TAKE(5);
  m.FSM_TAIL(0);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S534;
  if (c1 == '.') goto S594;
  return m.FSM_HALT(c1);

S542:
  c1 = m.FSM_CHAR();
  if ('1' <= c1 && c1 <= '9') goto S605;
  if (c1 == '0') goto S601;
  return m.FSM_HALT(c1);

S545:
  m.FSM_TAKE(34);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S174;
  if (c1 == '.') goto S466;
  return m.FSM_HALT(c1);

S552:
  c1 = m.FSM_CHAR();
  if ('1' <= c1 && c1 <= '9') goto S605;
  if (c1 == '0') goto S601;
  if (c1 == '-') goto S542;
  if (c1 == '+') goto S542;
  return m.FSM_HALT(c1);

S557:
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S557;
  if (c1 == '.') goto S610;
  return m.FSM_HALT(c1);

S560:
  m.FSM_TAKE(8);
  m.FSM_TAIL(1);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S174;
  if (c1 == '.') goto S174;
  return m.FSM_HALT(c1);

S568:
  m.FSM_TAKE(8);
  m.FSM_TAIL(1);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S568;
  if (c1 == '.') goto S174;
  return m.FSM_HALT(c1);

S576:
  c1 = m.FSM_CHAR();
  if ('1' <= c1 && c1 <= '9') goto S615;
  if (c1 == '0') goto S612;
  return m.FSM_HALT(c1);

S579:
  c1 = m.FSM_CHAR();
  if ('1' <= c1 && c1 <= '9') goto S615;
  if (c1 == '0') goto S612;
  if (c1 == '-') goto S576;
  if (c1 == '+') goto S576;
  return m.FSM_HALT(c1);

S584:
  m.FSM_TAKE(29);
  m.FSM_TAIL(2);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S584;
  if (c1 == '.') goto S174;
  return m.FSM_HALT(c1);

S592:
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S619;
  return m.FSM_HALT(c1);

S594:
  m.FSM_TAKE(34);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S623;
  if (c1 == '.') goto S174;
  return m.FSM_HALT(c1);

S601:
  m.FSM_TAKE(5);
  m.FSM_TAIL(0);
  c1 = m.FSM_CHAR();
  if (c1 == '.') goto S631;
  return m.FSM_HALT(c1);

S605:
  m.FSM_TAKE(5);
  m.FSM_TAIL(0);
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S605;
  if (c1 == '.') goto S631;
  return m.FSM_HALT(c1);

S610:
  c1 = m.FSM_CHAR();
  if (c1 == '.') goto S552;
  return m.FSM_HALT(c1);

S612:
  m.FSM_TAKE(8);
  m.FSM_TAIL(1);
  return m.FSM_HALT();

S615:
  m.FSM_TAKE(8);
  m.FSM_TAIL(1);
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S615;
  return m.FSM_HALT(c1);

S619:
  m.FSM_TAKE(29);
  m.FSM_TAIL(2);
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S619;
  return m.FSM_HALT(c1);

S623:
  m.FSM_TAKE(5);
  m.FSM_TAIL(0);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S174;
  if (c1 == '_') goto S174;
  if ('A' <= c1 && c1 <= 'Z') goto S174;
  if ('0' <= c1 && c1 <= '9') goto S623;
  if (c1 == '.') goto S174;
  return m.FSM_HALT(c1);

S631:
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S633;
  return m.FSM_HALT(c1);

S633:
  m.FSM_TAKE(5);
  m.FSM_TAIL(0);
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S633;
  return m.FSM_HALT(c1);
}

} // namespace ceammc

} // namespace argcheck

