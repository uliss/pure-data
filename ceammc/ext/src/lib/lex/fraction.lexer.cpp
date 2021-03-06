// fraction.lexer.cpp generated by reflex 1.6.3 from fraction.l

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  OPTIONS USED                                                              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define REFLEX_OPTION_fast                true
#define REFLEX_OPTION_freespace           true
#define REFLEX_OPTION_header_file         "fraction.lexer.h"
#define REFLEX_OPTION_lex                 lex
#define REFLEX_OPTION_lexer               FractionLexer
#define REFLEX_OPTION_namespace           ceammc::fraction
#define REFLEX_OPTION_noyywrap            true
#define REFLEX_OPTION_outfile             "fraction.lexer.cpp"
#define REFLEX_OPTION_reentrant           true

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %top{ user code %}                                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 1 "fraction.l"

    # include "ceammc_units.h"
    # include <cstdlib>


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
namespace fraction {

class FractionLexer : public reflex::AbstractLexer<reflex::Matcher> {
#line 6 "fraction.l"



    public:
        units::FractionValue value;

 public:
  typedef reflex::AbstractLexer<reflex::Matcher> AbstractBaseLexer;
  FractionLexer(
      const reflex::Input& input = reflex::Input(),
      std::ostream&        os    = std::cout)
    :
      AbstractBaseLexer(input, os)
  {
  }
  static const int INITIAL = 0;
  virtual int lex();
  int lex(
      const reflex::Input& input,
      std::ostream        *os = NULL)
  {
    in(input);
    if (os)
      out(*os);
    return lex();
  }
};

} // namespace ceammc
} // namespace fraction

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  REENTRANT                                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

typedef ceammc::fraction::FractionLexer yyscanner_t;

typedef void *yyscan_t;

#ifndef YY_EXTERN_C
#define YY_EXTERN_C
#endif

YY_EXTERN_C int yylex(yyscan_t scanner)
{
  return static_cast<yyscanner_t*>(scanner)->lex();
}

YY_EXTERN_C void yylex_init(yyscan_t *scanner)
{
  *scanner = static_cast<yyscan_t>(new yyscanner_t);
}

YY_EXTERN_C void yylex_destroy(yyscan_t scanner)
{
  delete static_cast<yyscanner_t*>(scanner);
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 2: rules                                                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

namespace ceammc {
namespace fraction {
extern void reflex_code_INITIAL(reflex::Matcher&);
} // namespace ceammc
} // namespace fraction

int ceammc::fraction::FractionLexer::lex()
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
              return int();
            }
            else
            {
              out().put(matcher().input());
            }
            break;
          case 1: // rule at line 37: (?:[\x09\x0a\x20]+)
#line 37 "fraction.l"
{ }
            break;
          case 2: // rule at line 38: (?:(?:(?:[\x2b\x2d]?(?:0|[1-9][0-9]*))(?:\.\d+)?)%)
#line 38 "fraction.l"
{ auto v = strtod(text(), nullptr); value = units::FractionValue(v, units::FractionValue::PERCENT); return 1; }
            break;
          case 3: // rule at line 39: (?:(?:(?:[\x2b\x2d]?(?:0|[1-9][0-9]*))(?:\.\d+)?)[\x2a])
#line 39 "fraction.l"
{ auto v = strtod(text(), nullptr); value = units::FractionValue(v, units::FractionValue::PHASE); return 1; }
            break;
          case 4: // rule at line 40: (?:(?:(?:0|[1-9][0-9]*))[/](?:(?:0|[1-9][0-9]*)))
#line 40 "fraction.l"
{
                    char* end;
                    auto num = strtol(text(), &end, 10);
                    auto den = strtol(end+1, nullptr, 10);
                    value = units::FractionValue::ratio(num, den);
                    return 1;
                }
            break;
          case 5: // rule at line 47: .
#line 47 "fraction.l"
{ return -1; }

            break;
        }
  }
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 3: user code                                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 50 "fraction.l"


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
namespace fraction {

void reflex_code_INITIAL(reflex::Matcher& m)
{
  int c0 = 0, c1 = 0;
  m.FSM_INIT(c1);

S0:
  m.FSM_FIND();
  c1 = m.FSM_CHAR();
  if ('1' <= c1 && c1 <= '9') goto S13;
  if (c1 == '0') goto S7;
  if (c1 == '-') goto S26;
  if (c1 == '+') goto S26;
  if (c1 == ' ') goto S22;
  if ('\t' <= c1 && c1 <= '\n') goto S22;
  if (0 <= c1) goto S20;
  return m.FSM_HALT(c1);

S7:
  m.FSM_TAKE(5);
  c1 = m.FSM_CHAR();
  if (c1 == '/') goto S34;
  if (c1 == '.') goto S37;
  if (c1 == '*') goto S32;
  if (c1 == '%') goto S30;
  return m.FSM_HALT(c1);

S13:
  m.FSM_TAKE(5);
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S39;
  if (c1 == '/') goto S34;
  if (c1 == '.') goto S37;
  if (c1 == '*') goto S32;
  if (c1 == '%') goto S30;
  return m.FSM_HALT(c1);

S20:
  m.FSM_TAKE(5);
  return m.FSM_HALT();

S22:
  m.FSM_TAKE(1);
  c1 = m.FSM_CHAR();
  if (c1 == ' ') goto S22;
  if ('\t' <= c1 && c1 <= '\n') goto S22;
  return m.FSM_HALT(c1);

S26:
  m.FSM_TAKE(5);
  c1 = m.FSM_CHAR();
  if ('1' <= c1 && c1 <= '9') goto S49;
  if (c1 == '0') goto S45;
  return m.FSM_HALT(c1);

S30:
  m.FSM_TAKE(2);
  return m.FSM_HALT();

S32:
  m.FSM_TAKE(3);
  return m.FSM_HALT();

S34:
  c1 = m.FSM_CHAR();
  if ('1' <= c1 && c1 <= '9') goto S56;
  if (c1 == '0') goto S54;
  return m.FSM_HALT(c1);

S37:
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S59;
  return m.FSM_HALT(c1);

S39:
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S39;
  if (c1 == '/') goto S34;
  if (c1 == '.') goto S37;
  if (c1 == '*') goto S32;
  if (c1 == '%') goto S30;
  return m.FSM_HALT(c1);

S45:
  c1 = m.FSM_CHAR();
  if (c1 == '.') goto S37;
  if (c1 == '*') goto S32;
  if (c1 == '%') goto S30;
  return m.FSM_HALT(c1);

S49:
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S49;
  if (c1 == '.') goto S37;
  if (c1 == '*') goto S32;
  if (c1 == '%') goto S30;
  return m.FSM_HALT(c1);

S54:
  m.FSM_TAKE(4);
  return m.FSM_HALT();

S56:
  m.FSM_TAKE(4);
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S56;
  return m.FSM_HALT(c1);

S59:
  c1 = m.FSM_CHAR();
  if ('0' <= c1 && c1 <= '9') goto S59;
  if (c1 == '*') goto S32;
  if (c1 == '%') goto S30;
  return m.FSM_HALT(c1);
}

} // namespace ceammc

} // namespace fraction

