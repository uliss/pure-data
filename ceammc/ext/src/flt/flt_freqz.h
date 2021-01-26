/*****************************************************************************
 * Copyright 2020 Serge Poltavsky. All rights reserved.
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
#ifndef FLT_FREQZ_H
#define FLT_FREQZ_H

#include "ceammc_object.h"

#include <complex>

using namespace ceammc;

class FltFreqZ : public BaseObject {
    ListProperty *ca_, *cb_;
    BoolProperty* db_scale_;
    std::vector<t_sample> kb_, ka_;

public:
    FltFreqZ(const PdArgs& args);
    void onBang() override;
    void dump() const override;

    void m_biquad(t_symbol* s, const AtomListView& lv);

    std::complex<t_float> Ajw(t_float w) const
    {
        std::complex<t_float> a(ka_.front());

        for (int j = 1; j < ka_.size(); j++) {
            auto ejw = std::complex<t_float>(0, -j * w);
            a += ka_[j] * std::exp(ejw);
        }

        return a;
    }

    std::complex<t_float> Bjw(t_float w) const
    {
        std::complex<t_float> b(kb_.front());

        for (int j = 1; j < kb_.size(); j++) {
            auto ejw = std::complex<t_float>(0, -j * w);
            b += kb_[j] * std::exp(ejw);
        }

        return b;
    }
};

void setup_flt_freqz();

#endif // FLT_FREQZ_H
