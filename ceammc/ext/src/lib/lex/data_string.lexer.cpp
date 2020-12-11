// data_string.lexer.cpp generated by reflex 1.6.3 from data_string.l

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  OPTIONS USED                                                              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define REFLEX_OPTION_YYLTYPE             ceammc::location
#define REFLEX_OPTION_YYSTYPE             ceammc::DataStringParser::semantic_type
#define REFLEX_OPTION_bison_cc            true
#define REFLEX_OPTION_bison_cc_namespace  ceammc
#define REFLEX_OPTION_bison_cc_parser     DataStringParser
#define REFLEX_OPTION_bison_complete      true
#define REFLEX_OPTION_bison_locations     true
#define REFLEX_OPTION_freespace           true
#define REFLEX_OPTION_header_file         "data_string.lexer.h"
#define REFLEX_OPTION_lex                 lex
#define REFLEX_OPTION_lexer               DataStringLexer
#define REFLEX_OPTION_namespace           ceammc
#define REFLEX_OPTION_noyywrap            true
#define REFLEX_OPTION_outfile             "data_string.lexer.cpp"
#define REFLEX_OPTION_reentrant           true
#define REFLEX_OPTION_token_eof           ceammc::DataStringParser::symbol_type(0, location())
#define REFLEX_OPTION_token_type          ceammc::DataStringParser::symbol_type
#define REFLEX_OPTION_unicode             true

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %top{ user code %}                                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 1 "data_string.l"

    # include <string>
    # include <memory>

    # include "lex/data_string.parser.hpp"
    # include "lex/data_string.location.hpp"
    # include "ceammc_log.h"

    using token = ceammc::DataStringParser::token;


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

class DataStringLexer : public reflex::AbstractLexer<reflex::Matcher> {
#line 12 "data_string.l"

    public:
        size_t output_indent = {0};

        std::string indent(size_t n = 0) const {
            return std::string(output_indent + n, ' ');
        }

 public:
  typedef reflex::AbstractLexer<reflex::Matcher> AbstractBaseLexer;
  DataStringLexer(
      const reflex::Input& input = reflex::Input(),
      std::ostream&        os    = std::cout)
    :
      AbstractBaseLexer(input, os)
  {
  }
  static const int INITIAL = 0;
  virtual ceammc::location location(void) const
  {
    ceammc::location yylloc;
    yylloc.begin.line = static_cast<unsigned int>(matcher().lineno());
    yylloc.begin.column = static_cast<unsigned int>(matcher().columno());
    yylloc.end.line = static_cast<unsigned int>(matcher().lineno_end());
    yylloc.end.column = static_cast<unsigned int>(matcher().columno_end());
    return yylloc;
  }
  virtual ceammc::DataStringParser::symbol_type lex(void);
};

} // namespace ceammc

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %{ user code %}                                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 21 "data_string.l"

    # include "fmt/format.h"

#line 30 "data_string.l"
/*%option graphs-file*/
/*%option debug*/
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

ceammc::DataStringParser::symbol_type ceammc::DataStringLexer::lex()
{
  static const char *REGEX_INITIAL = "(?mx)((?:[\\x09\\x0a\\x20]+))|(,)|(null)|(true)|(false)|(S(?=(?:\"(?:(?:[\\x00-!]|[\\x23-_]|[a-\\x7f]|[\\xc2-\\xdf][\\x80-\\xbf]|\\xe0[\\xa0-\\xbf][\\x80-\\xbf]|[\\xe1-\\xec][\\x80-\\xbf][\\x80-\\xbf]|\\xed[\\x80-\\x9f][\\x80-\\xbf]|[\\xee\\xef][\\x80-\\xbf][\\x80-\\xbf]|\\xf0[\\x90-\\xbf][\\x80-\\xbf][\\x80-\\xbf]|[\\xf1-\\xf3][\\x80-\\xbf][\\x80-\\xbf][\\x80-\\xbf]|\\xf4[\\x80-\\x8f][\\x80-\\xbf][\\x80-\\xbf])|`\"|``|`\\.|`:|`\\(|`\\))*\")))|((?:[A-Z][A-Za-z]*)(?=(?:\\()))|((?:[A-Z][A-Za-z]*)(?=(?:\\[)))|((?:[a-z][0-9a-z]*)(?=(?:\\()))|((?:\\[))|((?:\\]))|((?:\\())|((?:\\)))|((?:(?:[\\x2b\\x2d]?(?:0|[1-9][0-9]*))(?:\\.[0-9]+)?))|((?:[\\x2b\\x2d]?0[Xx][0-9A-Fa-f]+))|((?:0b[01]+))|((?:[\\x23\\x2e0-9@-Z_a-z]+:))|((?:(?:[\\x23%.-9@-Z_a-z])(?:(?:[\\x00-\\x1f]|!|[\\x23-']|[*-9]|[;-Z]|[\\x5e_]|[a-\\x7f]|[\\xc2-\\xdf][\\x80-\\xbf]|\\xe0[\\xa0-\\xbf][\\x80-\\xbf]|[\\xe1-\\xec][\\x80-\\xbf][\\x80-\\xbf]|\\xed[\\x80-\\x9f][\\x80-\\xbf]|[\\xee\\xef][\\x80-\\xbf][\\x80-\\xbf]|\\xf0[\\x90-\\xbf][\\x80-\\xbf][\\x80-\\xbf]|[\\xf1-\\xf3][\\x80-\\xbf][\\x80-\\xbf][\\x80-\\xbf]|\\xf4[\\x80-\\x8f][\\x80-\\xbf][\\x80-\\xbf]))*))|((?:\"(?:(?:[\\x00-!]|[\\x23-_]|[a-\\x7f]|[\\xc2-\\xdf][\\x80-\\xbf]|\\xe0[\\xa0-\\xbf][\\x80-\\xbf]|[\\xe1-\\xec][\\x80-\\xbf][\\x80-\\xbf]|\\xed[\\x80-\\x9f][\\x80-\\xbf]|[\\xee\\xef][\\x80-\\xbf][\\x80-\\xbf]|\\xf0[\\x90-\\xbf][\\x80-\\xbf][\\x80-\\xbf]|[\\xf1-\\xf3][\\x80-\\xbf][\\x80-\\xbf][\\x80-\\xbf]|\\xf4[\\x80-\\x8f][\\x80-\\xbf][\\x80-\\xbf])|`\"|``|`\\.|`:|`\\(|`\\))*\"))|(.)";
  static const reflex::Pattern PATTERN_INITIAL(REGEX_INITIAL);
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
              return ceammc::DataStringParser::symbol_type(0, location());
            }
            else
            {
              out().put(matcher().input());
            }
            break;
          case 1: // rule at line 66: (?:[\x09\x0a\x20]+)
#line 66 "data_string.l"
            break;
          case 2: // rule at line 67: ,
#line 67 "data_string.l"
{ return DataStringParser::make_COMMA(location()); }
            break;
          case 3: // rule at line 68: null
#line 68 "data_string.l"
{ return DataStringParser::make_NULL(location()); }
            break;
          case 4: // rule at line 69: true
#line 69 "data_string.l"
{ return DataStringParser::make_FLOAT(1, location()); }
            break;
          case 5: // rule at line 70: false
#line 70 "data_string.l"
{ return DataStringParser::make_FLOAT(0, location()); }
            break;
          case 6: // rule at line 71: S(?=(?:"(?:(?:[\x00-!]|[\x23-_]|[a-\x7f]|[\xc2-\xdf][\x80-\xbf]|\xe0[\xa0-\xbf][\x80-\xbf]|[\xe1-\xec][\x80-\xbf][\x80-\xbf]|\xed[\x80-\x9f][\x80-\xbf]|[\xee\xef][\x80-\xbf][\x80-\xbf]|\xf0[\x90-\xbf][\x80-\xbf][\x80-\xbf]|[\xf1-\xf3][\x80-\xbf][\x80-\xbf][\x80-\xbf]|\xf4[\x80-\x8f][\x80-\xbf][\x80-\xbf])|`"|``|`\.|`:|`\(|`\))*"))
#line 71 "data_string.l"
{ return DataStringParser::make_DATA_TYPE_STRING(location()); }
            break;
          case 7: // rule at line 72: (?:[A-Z][A-Za-z]*)(?=(?:\())
#line 72 "data_string.l"
{ return DataStringParser::make_DATA_TYPE(text(), location()); }
            break;
          case 8: // rule at line 73: (?:[A-Z][A-Za-z]*)(?=(?:\[))
#line 73 "data_string.l"
{ return DataStringParser::make_DATA_TYPE(text(), location()); }
            break;
          case 9: // rule at line 74: (?:[a-z][0-9a-z]*)(?=(?:\())
#line 74 "data_string.l"
{ return DataStringParser::make_FUNC_CALL(text(), location()); }
            break;
          case 10: // rule at line 75: (?:\[)
#line 75 "data_string.l"
{ return DataStringParser::make_OPEN_DICT_BRACKET(location()); }
            break;
          case 11: // rule at line 76: (?:\])
#line 76 "data_string.l"
{ return DataStringParser::make_CLOSE_DICT_BRACKET(location()); }
            break;
          case 12: // rule at line 77: (?:\()
#line 77 "data_string.l"
{ return DataStringParser::make_OPEN_LIST_BRACKET(location()); }
            break;
          case 13: // rule at line 78: (?:\))
#line 78 "data_string.l"
{ return DataStringParser::make_CLOSE_LIST_BRACKET(location()); }
            break;
          case 14: // rule at line 79: (?:(?:[\x2b\x2d]?(?:0|[1-9][0-9]*))(?:\.[0-9]+)?)
#line 79 "data_string.l"
{ return DataStringParser::make_FLOAT(std::strtod(text(), 0), location()); }
            break;
          case 15: // rule at line 80: (?:[\x2b\x2d]?0[Xx][0-9A-Fa-f]+)
#line 80 "data_string.l"
{
                          try {
                           long hex = std::stoi(text(), 0, 16);
                           return DataStringParser::make_FLOAT(hex, location());
                          }
                          catch(std::exception& e) {
                             out() << "invalid hex: " << e.what() << " - " << text();
                             return DataStringParser::make_LEXER_ERROR(location());
                          }
                        }
            break;
          case 16: // rule at line 90: (?:0b[01]+)
#line 90 "data_string.l"
{
                          std::string str(text() + 2);
                          try {
                           long bin = std::stoi(str.c_str(), 0, 2);
                           return DataStringParser::make_FLOAT(bin, location());
                          }
                          catch(std::exception& e) {
                             out() << "invalid bin: " << e.what() << " - " << text();
                             return DataStringParser::make_LEXER_ERROR(location());
                          }
                        }
            break;
          case 17: // rule at line 101: (?:[\x23\x2e0-9@-Z_a-z]+:)
#line 101 "data_string.l"
{
                          std::string key(str());
                          key.pop_back(); // remove trailing ':'
                          return DataStringParser::make_KEY(key, location());
                        }
            break;
          case 18: // rule at line 106: (?:(?:[\x23%.-9@-Z_a-z])(?:(?:[\x00-\x1f]|!|[\x23-']|[*-9]|[;-Z]|[\x5e_]|[a-\x7f]|[\xc2-\xdf][\x80-\xbf]|\xe0[\xa0-\xbf][\x80-\xbf]|[\xe1-\xec][\x80-\xbf][\x80-\xbf]|\xed[\x80-\x9f][\x80-\xbf]|[\xee\xef][\x80-\xbf][\x80-\xbf]|\xf0[\x90-\xbf][\x80-\xbf][\x80-\xbf]|[\xf1-\xf3][\x80-\xbf][\x80-\xbf][\x80-\xbf]|\xf4[\x80-\x8f][\x80-\xbf][\x80-\xbf]))*)
#line 106 "data_string.l"
{ return DataStringParser::make_SYMBOL(text(), location()); }
            break;
          case 19: // rule at line 107: (?:"(?:(?:[\x00-!]|[\x23-_]|[a-\x7f]|[\xc2-\xdf][\x80-\xbf]|\xe0[\xa0-\xbf][\x80-\xbf]|[\xe1-\xec][\x80-\xbf][\x80-\xbf]|\xed[\x80-\x9f][\x80-\xbf]|[\xee\xef][\x80-\xbf][\x80-\xbf]|\xf0[\x90-\xbf][\x80-\xbf][\x80-\xbf]|[\xf1-\xf3][\x80-\xbf][\x80-\xbf][\x80-\xbf]|\xf4[\x80-\x8f][\x80-\xbf][\x80-\xbf])|`"|``|`\.|`:|`\(|`\))*")
#line 107 "data_string.l"
{
                          std::string str(text() + 1);
                          str.pop_back();
                          return DataStringParser::make_STRING(str, location());
                        }

            break;
          case 20: // rule at line 113: .
#line 113 "data_string.l"
{
                          std::string line = matcher().line();
                          std::string err;

                          if(strcmp("`", text()) == 0)
                            err = " - stray ` found, use quotes: \"``\"";
                          else if(strcmp("\"", text()) == 0)
                            err = " - unmatched \" found, use quotes: \"`\"\"";
                          else if(strcmp("[", text()) == 0)
                            err = " - unmatched [ found, use quotes: \"[\"";
                          else if(strcmp("]", text()) == 0)
                            err = " - unmatched ] found, use quotes: \"]\"";
                          else if(strcmp("(", text()) == 0)
                            err = " - unmatched '(' found, use quotes: \"(\"";
                          else
                            err = fmt::format("unmatched lexer input: '{}'", text());

                          out() << fmt::format("error while parsing '{}': {}", line, err);

                          return DataStringParser::make_LEXER_ERROR(location()); /* error */
                        }

            break;
        }
  }
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 3: user code                                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 136 "data_string.l"

# include "fmt/format.h"
