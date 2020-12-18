// units.lexer.h generated by reflex 1.6.3 from units.l

#ifndef REFLEX_HEADER_H
#define REFLEX_HEADER_H
#define IN_HEADER 1

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  OPTIONS USED                                                              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define REFLEX_OPTION_fast                true
#define REFLEX_OPTION_freespace           true
#define REFLEX_OPTION_header_file         "units.lexer.h"
#define REFLEX_OPTION_lex                 lex
#define REFLEX_OPTION_lexer               UnitsLexer
#define REFLEX_OPTION_namespace           ceammc::units
#define REFLEX_OPTION_noyywrap            true
#define REFLEX_OPTION_outfile             "units.lexer.cpp"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %top{ user code %}                                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 1 "units.l"

    # include <cerrno>
    # include <cstdlib>
    # include <cstdint>
    # include <cmath>
    # include <array>

    # include "ceammc_log.h"


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
namespace units {

class UnitsLexer : public reflex::AbstractLexer<reflex::Matcher> {
#line 11 "units.l"

    public:
        enum UnitType : uint8_t {
            U_UNKNOWN,
            U_MSEC,
            U_SEC,
            U_MINUTE,
            U_HOUR,
            U_DAY,
            U_SAMP,
            U_HZ,
            U_CENT,
            U_SEMITONE,
            U_TONE,
            U_BPM,
            U_RADIANS,
            U_DEGREE,
            U_DB,
            U_SMPTE,
            U_PERCENT,
            U_RATIO,
            U_PHASE
        };

        enum ValueType : uint8_t {
            T_DOUBLE, T_LONG, T_SMPTE, T_RATIO
        };

        enum Status {
            STATUS_UNKNOWN_TOKEN = -2,
            STATUS_PARSE_ERROR = -1,
            STATUS_EOF = 0,
            STATUS_OK = 1,
            STATUS_CONTINUE
        };

        struct Smpte {
            uint8_t hour;
            uint8_t min;
            uint8_t sec;
            uint8_t frame;

            double toSeconds(double framerate) const {
                return 3600 * hour + 60 * min + sec + (frame / framerate);
            }
        };

        struct Ratio {
            int32_t num;
            int32_t den;
        };

        union Value {
            long int_val;
            double dbl_val;
            Ratio ratio_val;
            Smpte smpte_val;
        };

        struct UnitValue {
            Value val;
            ValueType type;
            UnitType unit = {U_UNKNOWN};
            bool end_offset = {false};
        };

        static constexpr size_t MAX_UNITS = 8;

        struct UnitValues {
            std::array<UnitValue, MAX_UNITS> data;
            size_t n = {1};

            UnitValue& back() { return data[n-1]; }
            void append() { if(n < MAX_UNITS-1) data[n++].val.int_val = 0; }
            void set(double v, UnitType u) { back().val.dbl_val = v; back().unit = u; back().type = T_DOUBLE; }
            void set(long v, UnitType u) { back().val.int_val = v; back().unit = u; back().type = T_LONG; }
            void set(const Smpte& v) { back().val.smpte_val = v; back().unit = U_SMPTE; back().type = T_SMPTE; }
            void set(const Ratio& v) { back().val.ratio_val = v; back().unit = U_RATIO; back().type = T_RATIO; }

            UnitValue& operator[](size_t i) { return data[i]; }
        };

    public:
        UnitValues values;

        int parseSingle()
        {
            values.n = 1;
            int rc = STATUS_OK;
            for(rc = STATUS_OK; rc == STATUS_OK || rc == STATUS_CONTINUE; rc = lex()) {
                if(rc == STATUS_CONTINUE) {
                    // lookup next
                    if (lex() != STATUS_OK) // invalid next token
                       return STATUS_UNKNOWN_TOKEN;

                    // next token is valid, but we are parsing just one
                    values.n = 1;
                    return STATUS_EOF;
                }
            }

            return rc;
        }

        int parseMany()
        {
            values.n = 1;
            int rc;
            for(rc = STATUS_OK; rc == STATUS_OK || rc == STATUS_CONTINUE; rc = lex())
            ;

            return rc;
        }

 public:
  typedef reflex::AbstractLexer<reflex::Matcher> AbstractBaseLexer;
  UnitsLexer(
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
} // namespace units

#endif