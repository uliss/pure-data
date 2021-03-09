// tl_lexer.cpp generated by reflex 3.0.1 from tl_lexer.l

#define REFLEX_VERSION "3.0.1"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  OPTIONS USED                                                              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define REFLEX_OPTION_YYLTYPE             ceammc::tl::location
#define REFLEX_OPTION_YYSTYPE             ceammc::tl::TlParser::semantic_type
#define REFLEX_OPTION_bison_cc            true
#define REFLEX_OPTION_bison_cc_namespace  ceammc::tl
#define REFLEX_OPTION_bison_cc_parser     TlParser
#define REFLEX_OPTION_bison_complete      true
#define REFLEX_OPTION_bison_locations     true
#define REFLEX_OPTION_fast                true
#define REFLEX_OPTION_freespace           true
#define REFLEX_OPTION_header_file         "tl_lexer.h"
#define REFLEX_OPTION_lex                 lex
#define REFLEX_OPTION_lexer               TlLexer
#define REFLEX_OPTION_namespace           ceammc::tl
#define REFLEX_OPTION_noyywrap            true
#define REFLEX_OPTION_outfile             "tl_lexer.cpp"
#define REFLEX_OPTION_reentrant           true
#define REFLEX_OPTION_stack               true
#define REFLEX_OPTION_token_eof           ceammc::tl::TlParser::symbol_type(0, location())
#define REFLEX_OPTION_token_type          ceammc::tl::TlParser::symbol_type
#define REFLEX_OPTION_yylineno            true

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %top user code                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 1 "tl_lexer.l"

    # include <cerrno>
    # include <climits>
    # include <cstdlib>
    # include <string>
    # include "tl_cmd_driver.h"
    # include "tl_parser.hpp"

    /* import the parser's token type into a local typedef */
    using token = ceammc::tl::TlParser::token;

    # define TL_NO_UNISTD_H


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
namespace tl {

class TlLexer : public reflex::AbstractLexer<reflex::Matcher> {
 public:
  typedef reflex::AbstractLexer<reflex::Matcher> AbstractBaseLexer;
  TlLexer(
      const reflex::Input& input = reflex::Input(),
      std::ostream&        os    = std::cout)
    :
      AbstractBaseLexer(input, os)
  {
  }
  static const int INITIAL = 0;
  std::string filename;
  virtual ceammc::tl::location location(void)
  {
    ceammc::tl::location yylloc;
    yylloc.begin.filename = &filename;
    yylloc.begin.line = static_cast<unsigned int>(matcher().lineno());
    yylloc.begin.column = static_cast<unsigned int>(matcher().columno());
    yylloc.end.filename = &filename;
    yylloc.end.line = static_cast<unsigned int>(matcher().lineno_end());
    yylloc.end.column = static_cast<unsigned int>(matcher().columno_end());
    return yylloc;
  }
  virtual ceammc::tl::TlParser::symbol_type lex(void);
};

} // namespace ceammc
} // namespace tl

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
namespace tl {
extern void reflex_code_INITIAL(reflex::Matcher&);
} // namespace ceammc
} // namespace tl

ceammc::tl::TlParser::symbol_type ceammc::tl::TlLexer::lex(void)
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
              return ceammc::tl::TlParser::symbol_type(0, location());
            }
            else
            {
              out().put(matcher().input());
            }
            break;
          case 1: // rule tl_lexer.l:43: {time} :
#line 43 "tl_lexer.l"
{ return TlParser::make_CLOCK_TIME(text(), location()); }

            break;
          case 2: // rule tl_lexer.l:45: {int} :
#line 45 "tl_lexer.l"
{
                      long v = strtol(text(), NULL, 10);
                      return TlParser::make_INT(v, location());
                }

            break;
          case 3: // rule tl_lexer.l:50: {float} :
#line 50 "tl_lexer.l"
{
                      float v = strtof(text(), NULL);
                      return TlParser::make_FLOAT(v, location());
                }

            break;
          case 4: // rule tl_lexer.l:55: {unit} :
#line 55 "tl_lexer.l"
{ return TlParser::make_UNIT(text(), location()); }
            break;
          case 5: // rule tl_lexer.l:56: before :
#line 56 "tl_lexer.l"
{ return TlParser::make_BEFORE(location()); }
            break;
          case 6: // rule tl_lexer.l:57: after :
#line 57 "tl_lexer.l"
{ return TlParser::make_AFTER(location()); }


            break;
          case 7: // rule tl_lexer.l:60: {act} :
#line 60 "tl_lexer.l"
{ std::string act(text());
                  if(act == "add")
                    return TlParser::make_ADD(location());
                  else if(act == "remove")
                    return TlParser::make_REMOVE(location());
                  else if(act == "remove_at")
                    return TlParser::make_REMOVE_AT(location());
                  else if(act == "clear")
                    return TlParser::make_CLEAR(location());
                  else if(act == "to_event")
                    return TlParser::make_TO_EVENT(location());
                  else if(act == "to_time")
                    return TlParser::make_TO_TIME(location());
                }

            break;
          case 8: // rule tl_lexer.l:75: {word} :
#line 75 "tl_lexer.l"
{ return TlParser::make_WORD(text(), location()); }
            break;
          case 9: // rule tl_lexer.l:76: {blank}+ :
#line 76 "tl_lexer.l"
{  }
            break;
        }
  }
}

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
namespace tl {

void reflex_code_INITIAL(reflex::Matcher& m)
{
  int c0 = 0, c1 = 0;
  m.FSM_INIT(c1);

S0:
  m.FSM_FIND();
  c1 = m.FSM_CHAR();
  if (c1 == 't') goto S72;
  if (c1 == 's') goto S25;
  if (c1 == 'r') goto S54;
  if (c1 == 'm') goto S16;
  if ('d' <= c1 && c1 <= 'z') goto S81;
  if (c1 == 'c') goto S63;
  if (c1 == 'b') goto S35;
  if (c1 == 'a') goto S44;
  if (c1 == '_') goto S81;
  if ('@' <= c1 && c1 <= 'Z') goto S81;
  if ('0' <= c1 && c1 <= '9') goto S89;
  if (c1 == '-') goto S94;
  if (c1 == '+') goto S94;
  if (c1 == ' ') goto S96;
  if (c1 == '\t') goto S96;
  return m.FSM_HALT(c1);

S16:
  c1 = m.FSM_CHAR();
  if (c1 == 's') goto S100;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S25:
  m.FSM_TAKE(4);
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S119;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S35:
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S129;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S44:
  c1 = m.FSM_CHAR();
  if (c1 == 'f') goto S139;
  if (c1 == 'd') goto S149;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S54:
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S159;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S63:
  c1 = m.FSM_CHAR();
  if (c1 == 'l') goto S169;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S72:
  c1 = m.FSM_CHAR();
  if (c1 == 'o') goto S179;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S81:
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S89:
  m.FSM_TAKE(2);
  c1 = m.FSM_CHAR();
  if (c1 == ':') goto S189;
  if ('0' <= c1 && c1 <= '9') goto S191;
  if (c1 == '.') goto S196;
  return m.FSM_HALT(c1);

S94:
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S198;
  return m.FSM_HALT(c1);

S96:
  m.FSM_TAKE(9);
  c1 = m.FSM_CHAR();
  if (c1 == ' ') goto S96;
  if (c1 == '\t') goto S96;
  return m.FSM_HALT(c1);

S100:
  m.FSM_TAKE(4);
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S202;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S110:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S119:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'c') goto S212;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S129:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'f') goto S221;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S139:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 't') goto S231;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S149:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'd') goto S241;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S159:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'm') goto S250;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S169:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S260;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S179:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if (c1 == '_') goto S270;
  if (c1 == '^') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S189:
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S281;
  return m.FSM_HALT(c1);

S191:
  m.FSM_TAKE(2);
  c1 = m.FSM_CHAR();
  if (c1 == ':') goto S189;
  if ('0' <= c1 && c1 <= '9') goto S198;
  if (c1 == '.') goto S196;
  return m.FSM_HALT(c1);

S196:
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S283;
  return m.FSM_HALT(c1);

S198:
  m.FSM_TAKE(2);
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S198;
  if (c1 == '.') goto S196;
  return m.FSM_HALT(c1);

S202:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'c') goto S212;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S212:
  m.FSM_TAKE(4);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S221:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'o') goto S286;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S231:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S296;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S241:
  m.FSM_TAKE(7);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S250:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'o') goto S306;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S260:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if ('b' <= c1 && c1 <= 'z') goto S110;
  if (c1 == 'a') goto S316;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S270:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 't') goto S336;
  if (c1 == 'e') goto S326;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S281:
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S346;
  return m.FSM_HALT(c1);

S283:
  m.FSM_TAKE(3);
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S283;
  return m.FSM_HALT(c1);

S286:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'r') goto S350;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S296:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'r') goto S360;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S306:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'v') goto S369;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S316:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'r') goto S241;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S326:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'v') goto S379;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S336:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'i') goto S389;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S346:
  m.FSM_TAKE(1);
  c1 = m.FSM_CHAR();
  if (c1 == ':') goto S399;
  if (c1 == '.') goto S401;
  return m.FSM_HALT(c1);

S350:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S403;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S360:
  m.FSM_TAKE(6);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S369:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S412;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S379:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S422;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S389:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'm') goto S432;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S399:
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S442;
  return m.FSM_HALT(c1);

S401:
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S444;
  return m.FSM_HALT(c1);

S403:
  m.FSM_TAKE(5);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S412:
  m.FSM_TAKE(7);
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if (c1 == '_') goto S447;
  if (c1 == '^') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S422:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'n') goto S457;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S432:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S241;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S442:
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S467;
  return m.FSM_HALT(c1);

S444:
  m.FSM_TAKE(1);
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S470;
  return m.FSM_HALT(c1);

S447:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if ('b' <= c1 && c1 <= 'z') goto S110;
  if (c1 == 'a') goto S473;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S457:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 't') goto S241;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S467:
  m.FSM_TAKE(1);
  c1 = m.FSM_CHAR();
  if (c1 == '.') goto S401;
  return m.FSM_HALT(c1);

S470:
  m.FSM_TAKE(1);
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S483;
  return m.FSM_HALT(c1);

S473:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if (c1 == 't') goto S241;
  if ('a' <= c1 && c1 <= 'z') goto S110;
  if ('^' <= c1 && c1 <= '_') goto S110;
  if ('@' <= c1 && c1 <= 'Z') goto S110;
  if ('0' <= c1 && c1 <= '9') goto S110;
  if (c1 == '*') goto S110;
  if ('#' <= c1 && c1 <= '&') goto S110;
  if (c1 == '!') goto S110;
  return m.FSM_HALT(c1);

S483:
  m.FSM_TAKE(1);
  return m.FSM_HALT();
}

} // namespace ceammc

} // namespace tl

