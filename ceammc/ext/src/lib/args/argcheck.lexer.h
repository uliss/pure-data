// argcheck.lexer.h generated by reflex 3.0.1 from argcheck.l

#ifndef REFLEX_ARGCHECK_LEXER_H
#define REFLEX_ARGCHECK_LEXER_H
#define IN_HEADER 1
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
//  BISON C++                                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


#endif
