// select.lexer.cpp generated by reflex 1.6.3 from select.l

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  OPTIONS USED                                                              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define REFLEX_OPTION_YYLTYPE             ceammc::location
#define REFLEX_OPTION_YYSTYPE             ceammc::SelectParser::semantic_type
#define REFLEX_OPTION_bison_cc            true
#define REFLEX_OPTION_bison_cc_namespace  ceammc
#define REFLEX_OPTION_bison_cc_parser     SelectParser
#define REFLEX_OPTION_bison_complete      true
#define REFLEX_OPTION_freespace           true
#define REFLEX_OPTION_header_file         "select.lexer.h"
#define REFLEX_OPTION_lex                 lex
#define REFLEX_OPTION_lexer               SelectLexer
#define REFLEX_OPTION_namespace           ceammc
#define REFLEX_OPTION_noindent            true
#define REFLEX_OPTION_noyywrap            true
#define REFLEX_OPTION_outfile             "select.lexer.cpp"
#define REFLEX_OPTION_reentrant           true
#define REFLEX_OPTION_token_eof           ceammc::SelectParser::symbol_type(0)
#define REFLEX_OPTION_token_type          ceammc::SelectParser::symbol_type
#define REFLEX_OPTION_unicode             true

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %top{ user code %}                                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 1 "select.l"

    # include <string>
    # include <array>
    # include <stdexcept>
    # include <algorithm>
    # include <cstdint>

    # include "lex/select.parser.hpp"

    using token = ceammc::SelectParser::token;


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

class SelectLexer : public reflex::AbstractLexer<reflex::Matcher> {
#line 13 "select.l"

    public:
        enum MatchType : uint8_t {
            MATCH_EQUAL,
            MATCH_EPSILON,
            MATCH_RANGE_OO,
            MATCH_RANGE_CC,
            MATCH_RANGE_OC,
            MATCH_RANGE_CO,
            MATCH_SET,
            MATCH_LESS,
            MATCH_LESS_EQ,
            MATCH_GREATER,
            MATCH_GREATER_EQ
        };

        struct LexerAtom {
            std::string txt;
            bool is_float;
        };

        class MatchData {
            using AList = std::array<ceammc::Atom, 16>;
            AList data_;
            uint8_t n_ = { 0 };
            MatchType type_ = { MATCH_EQUAL };

        public:
            MatchData() {}
            MatchData(uint8_t n, MatchType t) : n_(std::min<uint8_t>(n, data_.size())), type_(t) {}
            MatchData(double v) : MatchData(1, MATCH_EQUAL) { data_[0].setFloat(v, true); }
            MatchData(const std::string& s) : MatchData(1, MATCH_EQUAL) { data_[0].setSymbol(gensym(s.c_str()), true); }

            MatchData& operator+=(const MatchData& m) {
                for (uint8_t i = 0; i < m.n_ && n_ < data_.size(); i++) {
                    data_[n_] = m.data_[i];
                    n_++;
                }
                type_ = MATCH_SET;
                return *this;
            }

            size_t size() const { return n_; }
            MatchType type() const { return type_; }
            AList::const_iterator begin() const { return data_.cbegin(); }
            AList::const_iterator end() const { return data_.cend(); }
            const Atom& at(uint8_t idx) const {
                static Atom null;
                return (idx >= data_.size()) ? null : data_[idx];
            }

            static MatchData epsilon(double a, double b) {
                MatchData res(2, MATCH_EPSILON);
                res.data_[0].setFloat(a, true);
                res.data_[1].setFloat(b, true);
                return res;
            }

            static MatchData range(double a, double b, MatchType t) {
                MatchData res(2, t);
                res.data_[0].setFloat(a, true);
                res.data_[1].setFloat(b, true);
                return res;
            }

            static MatchData compare(double x, MatchType t) {
                MatchData res(1, t);
                res.data_[0].setFloat(x, true);
                return res;
            }
        };

        void pushMatch(const MatchData& d)
        {
            if(nmatches_ < matches_.size())
                matches_[nmatches_++] = d;
        }

        void pushLexerAtom(const LexerAtom& a)
        {
            atoms_.push_back(a);
        }

        void popLexerAtoms()
        {
            if(atoms_.size() == 1 && atoms_[0].is_float)
                pushMatch(MatchData(std::strtod(atoms_[0].txt.c_str(), nullptr)));
            else {
                std::string res;
                for(auto& a: atoms_)
                    res += a.txt;

                pushMatch(MatchData(res));
            }

            atoms_.clear();
        }

        const MatchData& operator[](size_t idx) const {
            if(idx >= nmatches_)
                throw std::out_of_range("invalid index");

            return matches_[idx];
        }

        size_t numMatches() const { return nmatches_; }
        void clearMatches() { nmatches_ = 0; }
        void mergeMatch() {
            if(nmatches_ < 2)
                return;

            auto& m0 = matches_[nmatches_-2];
            const auto& m1 = matches_[nmatches_-1];
            m0 += m1;
            nmatches_ -= 1;
        }

        void setErrorMsg(const std::string& str) { error_msg_ = str; }

    private:
        std::array<MatchData, 64> matches_;
        std::vector<LexerAtom> atoms_;
        size_t nmatches_ = {0};
        std::string error_msg_;

 public:
  typedef reflex::AbstractLexer<reflex::Matcher> AbstractBaseLexer;
  SelectLexer(
      const reflex::Input& input = reflex::Input(),
      std::ostream&        os    = std::cout)
    :
      AbstractBaseLexer(input, os)
  {
  }
  static const int INITIAL = 0;
  static const int RANGE = 1;
  static const int EPSILON = 2;
  virtual ceammc::SelectParser::symbol_type lex(void);
};

} // namespace ceammc

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %{ user code %}                                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 144 "select.l"
/*%option graphs-file*/
/*%option debug*/
/*%option perf-report*/
#line 154 "select.l"
/*%option fast*/


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

ceammc::SelectParser::symbol_type ceammc::SelectLexer::lex()
{
  static const char *REGEX_INITIAL = "(?mx)((?:[\\x09\\x0a\\x20]+))|((?:~)(?=(?:(?:0|[1-9][0-9]*)(?:\\.[0-9]+)?)))|((?:\\.\\.)(?=(?:(?:[\\x2b\\x2d]?(?:0|[1-9][0-9]*))(?:\\.[0-9]+)?)))|((?:\\[)(?=(?:(?:[\\x2b\\x2d]?(?:0|[1-9][0-9]*))(?:\\.[0-9]+)?)))|((?:\\]))|((?:\\()(?=(?:(?:[\\x2b\\x2d]?(?:0|[1-9][0-9]*))(?:\\.[0-9]+)?)))|((?:\\)))|((?:\\|))|((?:>=)(?=(?:(?:[\\x2b\\x2d]?(?:0|[1-9][0-9]*))(?:\\.[0-9]+)?)))|((?:>)(?=(?:(?:[\\x2b\\x2d]?(?:0|[1-9][0-9]*))(?:\\.[0-9]+)?)))|((?:<)(?=(?:(?:[\\x2b\\x2d]?(?:0|[1-9][0-9]*))(?:\\.[0-9]+)?)))|((?:<=)(?=(?:(?:[\\x2b\\x2d]?(?:0|[1-9][0-9]*))(?:\\.[0-9]+)?)))|((?:(?:[\\x2b\\x2d]?(?:0|[1-9][0-9]*))(?:\\.[0-9]+)?))|((?:(?:[\\x00-\\x08]|[\\x0b-\\x1f]|[!-/]|[:-{]|[}-\\x7f]|[\\xc2-\\xdf][\\x80-\\xbf]|\\xe0[\\xa0-\\xbf][\\x80-\\xbf]|[\\xe1-\\xec][\\x80-\\xbf][\\x80-\\xbf]|\\xed[\\x80-\\x9f][\\x80-\\xbf]|[\\xee\\xef][\\x80-\\xbf][\\x80-\\xbf]|\\xf0[\\x90-\\xbf][\\x80-\\xbf][\\x80-\\xbf]|[\\xf1-\\xf3][\\x80-\\xbf][\\x80-\\xbf][\\x80-\\xbf]|\\xf4[\\x80-\\x8f][\\x80-\\xbf][\\x80-\\xbf])+))|(.)";
  static const reflex::Pattern PATTERN_INITIAL(REGEX_INITIAL);
  static const char *REGEX_RANGE = "(?mx)(.)";
  static const reflex::Pattern PATTERN_RANGE(REGEX_RANGE);
  static const char *REGEX_EPSILON = "(?mx)(.)";
  static const reflex::Pattern PATTERN_EPSILON(REGEX_EPSILON);
  if (!has_matcher())
  {
    matcher(new Matcher(PATTERN_INITIAL, stdinit(), this));
  }
  while (true)
  {
    switch (start())
    {
      case INITIAL:
        matcher().pattern(PATTERN_INITIAL);
        switch (matcher().scan())
        {
          case 0:
            if (matcher().at_end())
            {
              return ceammc::SelectParser::symbol_type(0);
            }
            else
            {
              out().put(matcher().input());
            }
            break;
          case 1: // rule at line 185: (?:[\x09\x0a\x20]+)
#line 185 "select.l"
{ return SelectParser::make_SPACE(); }
            break;
          case 2: // rule at line 186: (?:~)(?=(?:(?:0|[1-9][0-9]*)(?:\.[0-9]+)?))
#line 186 "select.l"
{ return SelectParser::make_EPSILON(); }
            break;
          case 3: // rule at line 187: (?:\.\.)(?=(?:(?:[\x2b\x2d]?(?:0|[1-9][0-9]*))(?:\.[0-9]+)?))
#line 187 "select.l"
{ return SelectParser::make_RANGE(); }
            break;
          case 4: // rule at line 188: (?:\[)(?=(?:(?:[\x2b\x2d]?(?:0|[1-9][0-9]*))(?:\.[0-9]+)?))
#line 188 "select.l"
{ return SelectParser::make_OPEN_BRACKET('['); }
            break;
          case 5: // rule at line 189: (?:\])
#line 189 "select.l"
{ return SelectParser::make_CLOSE_BRACKET(']'); }
            break;
          case 6: // rule at line 190: (?:\()(?=(?:(?:[\x2b\x2d]?(?:0|[1-9][0-9]*))(?:\.[0-9]+)?))
#line 190 "select.l"
{ return SelectParser::make_OPEN_PAR('('); }
            break;
          case 7: // rule at line 191: (?:\))
#line 191 "select.l"
{ return SelectParser::make_CLOSE_PAR(')'); }
            break;
          case 8: // rule at line 192: (?:\|)
#line 192 "select.l"
{ return SelectParser::make_OR(); }
            break;
          case 9: // rule at line 193: (?:>=)(?=(?:(?:[\x2b\x2d]?(?:0|[1-9][0-9]*))(?:\.[0-9]+)?))
#line 193 "select.l"
{ return SelectParser::make_OP_GREATER_EQ(); }
            break;
          case 10: // rule at line 194: (?:>)(?=(?:(?:[\x2b\x2d]?(?:0|[1-9][0-9]*))(?:\.[0-9]+)?))
#line 194 "select.l"
{ return SelectParser::make_OP_GREATER(); }
            break;
          case 11: // rule at line 195: (?:<)(?=(?:(?:[\x2b\x2d]?(?:0|[1-9][0-9]*))(?:\.[0-9]+)?))
#line 195 "select.l"
{ return SelectParser::make_OP_LESS(); }
            break;
          case 12: // rule at line 196: (?:<=)(?=(?:(?:[\x2b\x2d]?(?:0|[1-9][0-9]*))(?:\.[0-9]+)?))
#line 196 "select.l"
{ return SelectParser::make_OP_LESS_EQ(); }
            break;
          case 13: // rule at line 197: (?:(?:[\x2b\x2d]?(?:0|[1-9][0-9]*))(?:\.[0-9]+)?)
#line 197 "select.l"
{ return SelectParser::make_FLOAT(text()); }
            break;
          case 14: // rule at line 199: (?:(?:[\x00-\x08]|[\x0b-\x1f]|[!-/]|[:-{]|[}-\x7f]|[\xc2-\xdf][\x80-\xbf]|\xe0[\xa0-\xbf][\x80-\xbf]|[\xe1-\xec][\x80-\xbf][\x80-\xbf]|\xed[\x80-\x9f][\x80-\xbf]|[\xee\xef][\x80-\xbf][\x80-\xbf]|\xf0[\x90-\xbf][\x80-\xbf][\x80-\xbf]|[\xf1-\xf3][\x80-\xbf][\x80-\xbf][\x80-\xbf]|\xf4[\x80-\x8f][\x80-\xbf][\x80-\xbf])+)
#line 199 "select.l"
{ return SelectParser::make_SYMBOL(text()); }

            break;
          case 15: // rule at line 201: .
#line 201 "select.l"
{   }

            break;
        }
        break;
      case RANGE:
        matcher().pattern(PATTERN_RANGE);
        switch (matcher().scan())
        {
          case 0:
            if (matcher().at_end())
            {
              return ceammc::SelectParser::symbol_type(0);
            }
            else
            {
              out().put(matcher().input());
            }
            break;
          case 1: // rule at line 201: .
#line 201 "select.l"
{   }

            break;
        }
        break;
      case EPSILON:
        matcher().pattern(PATTERN_EPSILON);
        switch (matcher().scan())
        {
          case 0:
            if (matcher().at_end())
            {
              return ceammc::SelectParser::symbol_type(0);
            }
            else
            {
              out().put(matcher().input());
            }
            break;
          case 1: // rule at line 201: .
#line 201 "select.l"
{   }

            break;
        }
        break;
      default:
        start(0);
    }
  }
}
