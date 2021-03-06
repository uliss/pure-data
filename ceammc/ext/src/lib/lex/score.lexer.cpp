// score.lexer.cpp generated by reflex 3.0.1 from score.l

#define REFLEX_VERSION "3.0.1"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  OPTIONS USED                                                              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define REFLEX_OPTION_YYLTYPE             ceammc::score::location
#define REFLEX_OPTION_YYSTYPE             ceammc::score::ScoreParser::semantic_type
#define REFLEX_OPTION_bison_cc            true
#define REFLEX_OPTION_bison_cc_namespace  ceammc::score
#define REFLEX_OPTION_bison_cc_parser     ScoreParser
#define REFLEX_OPTION_bison_complete      true
#define REFLEX_OPTION_debug               true
#define REFLEX_OPTION_fast                true
#define REFLEX_OPTION_freespace           true
#define REFLEX_OPTION_header_file         "score.lexer.h"
#define REFLEX_OPTION_lex                 lex
#define REFLEX_OPTION_lexer               ScoreLexer
#define REFLEX_OPTION_namespace           ceammc::score
#define REFLEX_OPTION_noindent            true
#define REFLEX_OPTION_noyywrap            true
#define REFLEX_OPTION_outfile             "score.lexer.cpp"
#define REFLEX_OPTION_reentrant           true
#define REFLEX_OPTION_token_eof           ceammc::score::ScoreParser::symbol_type(0)
#define REFLEX_OPTION_token_type          ceammc::score::ScoreParser::symbol_type

// --debug option enables ASSERT:
#define ASSERT(c) assert(c)

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %top user code                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 1 "score.l"

    # include <memory>
    # include <cctype>
    # include "lex/score.parser.hpp"

    using token = ceammc::score::ScoreParser::token;


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  REGEX MATCHER                                                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define WITH_NO_INDENT
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
namespace score {

class ScoreLexer : public reflex::AbstractLexer<reflex::Matcher> {
#line 9 "score.l"

    public:
        BarList bars;



 public:
  typedef reflex::AbstractLexer<reflex::Matcher> AbstractBaseLexer;
  ScoreLexer(
      const reflex::Input& input = reflex::Input(),
      std::ostream&        os    = std::cout)
    :
      AbstractBaseLexer(input, os)
  {
    set_debug(true);
  }
  static const int INITIAL = 0;
  virtual ceammc::score::ScoreParser::symbol_type lex(void);
};

} // namespace ceammc
} // namespace score

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %{ user code %}                                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 21 "score.l"
/*%option graphs-file*/
#line 23 "score.l"
/*%option perf-report*/

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
namespace score {
extern void reflex_code_INITIAL(reflex::Matcher&);
} // namespace ceammc
} // namespace score

ceammc::score::ScoreParser::symbol_type ceammc::score::ScoreLexer::lex(void)
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
              if (debug()) std::cerr << "--\033[1;35mEOF\033[0m (start condition " << start() << ")\n";
              return ceammc::score::ScoreParser::symbol_type(0);
            }
            else
            {
              if (debug()) std::cerr << "--\033[1;31maccepting default rule\033[0m\n";
              out().put(matcher().input());
            }
            break;
          case 1: // rule score.l:55: {space} :
            if (debug()) std::cerr << "--\033[1;35maccepting rule at line 55\033[0m (\"\033[1m" << matcher().text() << "\033[0m\")\n";
#line 55 "score.l"
{ return ScoreParser::make_SPACE(); }
            break;
          case 2: // rule score.l:56: \| :
            if (debug()) std::cerr << "--\033[1;35maccepting rule at line 56\033[0m (\"\033[1m" << matcher().text() << "\033[0m\")\n";
#line 56 "score.l"
{ return ScoreParser::make_PIPE(); }
            break;
          case 3: // rule score.l:57: {change} :
            if (debug()) std::cerr << "--\033[1;35maccepting rule at line 57\033[0m (\"\033[1m" << matcher().text() << "\033[0m\")\n";
#line 57 "score.l"
{ return ScoreParser::make_CHANGE(); }
            break;
          case 4: // rule score.l:58: {fermata} :
            if (debug()) std::cerr << "--\033[1;35maccepting rule at line 58\033[0m (\"\033[1m" << matcher().text() << "\033[0m\")\n";
#line 58 "score.l"
{ return ScoreParser::make_FERMATA(); }

            break;
          case 5: // rule score.l:60: {bar_check} :
            if (debug()) std::cerr << "--\033[1;35maccepting rule at line 60\033[0m (\"\033[1m" << matcher().text() << "\033[0m\")\n";
#line 60 "score.l"
{
                            const auto n = std::strtol(text()+4, nullptr, 10);
                            return ScoreParser::make_BAR_CHECK(n);
                        }

            break;
          case 6: // rule score.l:65: {bar_pos} :
            if (debug()) std::cerr << "--\033[1;35maccepting rule at line 65\033[0m (\"\033[1m" << matcher().text() << "\033[0m\")\n";
#line 65 "score.l"
{
                            const auto pos = std::strtol(text()+1, nullptr, 10);
                            return ScoreParser::make_AT(pos);
                        }

            break;
          case 7: // rule score.l:70: {bar_repeat} :
            if (debug()) std::cerr << "--\033[1;35maccepting rule at line 70\033[0m (\"\033[1m" << matcher().text() << "\033[0m\")\n";
#line 70 "score.l"
{
                            const auto n = std::strtol(text(), nullptr, 10);
                            return ScoreParser::make_REPEAT(n);
                        }

            break;
          case 8: // rule score.l:75: {beat_div} :
            if (debug()) std::cerr << "--\033[1;35maccepting rule at line 75\033[0m (\"\033[1m" << matcher().text() << "\033[0m\")\n";
#line 75 "score.l"
{
                            const auto n = std::strtol(text()+4, nullptr, 10);
                            return ScoreParser::make_BEAT_DIVISION(n);
                        }

            break;
          case 9: // rule score.l:80: {ratio} :
            if (debug()) std::cerr << "--\033[1;35maccepting rule at line 80\033[0m (\"\033[1m" << matcher().text() << "\033[0m\")\n";
#line 80 "score.l"
{
                            char* end;
                            const auto num = std::strtol(text(), &end, 10);
                            const auto den = std::strtol(end+1, nullptr, 10);
                            return ScoreParser::make_RATIO(std::pair<int, int>(num, den));
                        }

            break;
          case 10: // rule score.l:87: {udec} :
            if (debug()) std::cerr << "--\033[1;35maccepting rule at line 87\033[0m (\"\033[1m" << matcher().text() << "\033[0m\")\n";
#line 87 "score.l"
{
                            const auto num = std::strtol(text(), nullptr, 10);
                            return ScoreParser::make_INT(num);
                        }

            break;
          case 11: // rule score.l:92: {keys} :
            if (debug()) std::cerr << "--\033[1;35maccepting rule at line 92\033[0m (\"\033[1m" << matcher().text() << "\033[0m\")\n";
#line 92 "score.l"
{
                            const int len = strlen(text());
                            const char id = text()[0];
                            const char c = text()[len-2];
                            const char n = isdigit(c) ? (c-'0') : 0;
                            return ScoreParser::make_KEY(KeyId(id, n));
                        }
            break;
          case 12: // rule score.l:99: . :
            if (debug()) std::cerr << "--\033[1;35maccepting rule at line 99\033[0m (\"\033[1m" << matcher().text() << "\033[0m\")\n";
#line 99 "score.l"
{   }

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
namespace score {

void reflex_code_INITIAL(reflex::Matcher& m)
{
  int c0 = 0, c1 = 0;
  m.FSM_INIT(c1);

S0:
  m.FSM_FIND();
  c1 = m.FSM_CHAR();
  if (c1 == '|') goto S17;
  if (c1 == 'v') goto S67;
  if (c1 == 't') goto S43;
  if (c1 == 'p') goto S62;
  if (c1 == 'm') goto S57;
  if (c1 == 'f') goto S22;
  if (c1 == 'd') goto S37;
  if (c1 == 'c') goto S52;
  if (c1 == 'b') goto S25;
  if (c1 == 'a') goto S47;
  if (c1 == '@') goto S28;
  if ('1' <= c1 && c1 <= '9') goto S32;
  if (c1 == '0') goto S40;
  if (c1 == '.') goto S19;
  if (c1 == ' ') goto S74;
  if ('\t' <= c1 && c1 <= '\n') goto S74;
  if (0 <= c1) goto S72;
  return m.FSM_HALT(c1);

S17:
  m.FSM_TAKE(2);
  return m.FSM_HALT();

S19:
  m.FSM_TAKE(12);
  c1 = m.FSM_CHAR();
  if (c1 == '.') goto S78;
  return m.FSM_HALT(c1);

S22:
  m.FSM_TAKE(12);
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S80;
  return m.FSM_HALT(c1);

S25:
  m.FSM_TAKE(12);
  c1 = m.FSM_CHAR();
  if (c1 == 'a') goto S82;
  return m.FSM_HALT(c1);

S28:
  m.FSM_TAKE(12);
  c1 = m.FSM_CHAR();
  if ('1' <= c1 && c1 <= '9') goto S86;
  if (c1 == '0') goto S84;
  return m.FSM_HALT(c1);

S32:
  m.FSM_TAKE(10);
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S32;
  if (c1 == '/') goto S91;
  if (c1 == '*') goto S89;
  return m.FSM_HALT(c1);

S37:
  m.FSM_TAKE(12);
  c1 = m.FSM_CHAR();
  if (c1 == 'i') goto S94;
  return m.FSM_HALT(c1);

S40:
  m.FSM_TAKE(10);
  c1 = m.FSM_CHAR();
  if (c1 == '/') goto S91;
  return m.FSM_HALT(c1);

S43:
  m.FSM_TAKE(12);
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S98;
  if (c1 == '=') goto S96;
  return m.FSM_HALT(c1);

S47:
  m.FSM_TAKE(12);
  c1 = m.FSM_CHAR();
  if (c1 == 'm') goto S100;
  if (c1 == '=') goto S96;
  if ('0' <= c1 && c1 <= '9') goto S102;
  return m.FSM_HALT(c1);

S52:
  m.FSM_TAKE(12);
  c1 = m.FSM_CHAR();
  if (c1 == 'u') goto S104;
  if (c1 == '=') goto S96;
  if ('0' <= c1 && c1 <= '9') goto S102;
  return m.FSM_HALT(c1);

S57:
  m.FSM_TAKE(12);
  c1 = m.FSM_CHAR();
  if (c1 == 'a') goto S106;
  if (c1 == '=') goto S96;
  if ('0' <= c1 && c1 <= '9') goto S102;
  return m.FSM_HALT(c1);

S62:
  m.FSM_TAKE(12);
  c1 = m.FSM_CHAR();
  if (c1 == 'a') goto S108;
  if (c1 == '=') goto S96;
  if ('0' <= c1 && c1 <= '9') goto S102;
  return m.FSM_HALT(c1);

S67:
  m.FSM_TAKE(12);
  c1 = m.FSM_CHAR();
  if (c1 == 'o') goto S110;
  if (c1 == '=') goto S96;
  if ('0' <= c1 && c1 <= '9') goto S102;
  return m.FSM_HALT(c1);

S72:
  m.FSM_TAKE(12);
  return m.FSM_HALT();

S74:
  m.FSM_TAKE(1);
  c1 = m.FSM_CHAR();
  if (c1 == ' ') goto S74;
  if ('\t' <= c1 && c1 <= '\n') goto S74;
  return m.FSM_HALT(c1);

S78:
  m.FSM_TAKE(3);
  return m.FSM_HALT();

S80:
  c1 = m.FSM_CHAR();
  if (c1 == 'r') goto S112;
  return m.FSM_HALT(c1);

S82:
  c1 = m.FSM_CHAR();
  if (c1 == 'r') goto S114;
  return m.FSM_HALT(c1);

S84:
  m.FSM_TAKE(6);
  return m.FSM_HALT();

S86:
  m.FSM_TAKE(6);
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S86;
  return m.FSM_HALT(c1);

S89:
  m.FSM_TAKE(7);
  return m.FSM_HALT();

S91:
  c1 = m.FSM_CHAR();
  if ('1' <= c1 && c1 <= '9') goto S118;
  if (c1 == '0') goto S116;
  return m.FSM_HALT(c1);

S94:
  c1 = m.FSM_CHAR();
  if (c1 == 'v') goto S121;
  return m.FSM_HALT(c1);

S96:
  m.FSM_TAKE(11);
  return m.FSM_HALT();

S98:
  c1 = m.FSM_CHAR();
  if (c1 == 'm') goto S123;
  return m.FSM_HALT(c1);

S100:
  c1 = m.FSM_CHAR();
  if (c1 == 'p') goto S125;
  return m.FSM_HALT(c1);

S102:
  c1 = m.FSM_CHAR();
  if (c1 == '=') goto S96;
  return m.FSM_HALT(c1);

S104:
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S125;
  return m.FSM_HALT(c1);

S106:
  c1 = m.FSM_CHAR();
  if (c1 == 'r') goto S128;
  return m.FSM_HALT(c1);

S108:
  c1 = m.FSM_CHAR();
  if (c1 == 'n') goto S125;
  return m.FSM_HALT(c1);

S110:
  c1 = m.FSM_CHAR();
  if (c1 == 'l') goto S125;
  return m.FSM_HALT(c1);

S112:
  c1 = m.FSM_CHAR();
  if (c1 == 'm') goto S130;
  return m.FSM_HALT(c1);

S114:
  c1 = m.FSM_CHAR();
  if (c1 == '=') goto S132;
  return m.FSM_HALT(c1);

S116:
  m.FSM_TAKE(9);
  return m.FSM_HALT();

S118:
  m.FSM_TAKE(9);
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S118;
  return m.FSM_HALT(c1);

S121:
  c1 = m.FSM_CHAR();
  if (c1 == '=') goto S135;
  return m.FSM_HALT(c1);

S123:
  c1 = m.FSM_CHAR();
  if (c1 == 'p') goto S138;
  return m.FSM_HALT(c1);

S125:
  c1 = m.FSM_CHAR();
  if (c1 == '=') goto S96;
  if ('0' <= c1 && c1 <= '9') goto S102;
  return m.FSM_HALT(c1);

S128:
  c1 = m.FSM_CHAR();
  if (c1 == 'k') goto S125;
  return m.FSM_HALT(c1);

S130:
  c1 = m.FSM_CHAR();
  if (c1 == 'a') goto S140;
  return m.FSM_HALT(c1);

S132:
  c1 = m.FSM_CHAR();
  if ('1' <= c1 && c1 <= '9') goto S144;
  if (c1 == '0') goto S142;
  return m.FSM_HALT(c1);

S135:
  c1 = m.FSM_CHAR();
  if ('1' <= c1 && c1 <= '9') goto S149;
  if (c1 == '0') goto S147;
  return m.FSM_HALT(c1);

S138:
  c1 = m.FSM_CHAR();
  if (c1 == 'o') goto S102;
  return m.FSM_HALT(c1);

S140:
  c1 = m.FSM_CHAR();
  if (c1 == 't') goto S152;
  return m.FSM_HALT(c1);

S142:
  m.FSM_TAKE(5);
  return m.FSM_HALT();

S144:
  m.FSM_TAKE(5);
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S144;
  return m.FSM_HALT(c1);

S147:
  m.FSM_TAKE(8);
  return m.FSM_HALT();

S149:
  m.FSM_TAKE(8);
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S149;
  return m.FSM_HALT(c1);

S152:
  c1 = m.FSM_CHAR();
  if (c1 == 'a') goto S154;
  return m.FSM_HALT(c1);

S154:
  m.FSM_TAKE(4);
  return m.FSM_HALT();
}

} // namespace ceammc

} // namespace score

