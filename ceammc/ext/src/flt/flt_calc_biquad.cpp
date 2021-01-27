/*****************************************************************************
 * Copyright 2021 Serge Poltavsky. All rights reserved.
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
#include "flt_calc_biquad.h"
#include "flt_common.h"

FltCalcBiquad::FltCalcBiquad(const PdArgs& args)
    : BaseObject(args)
    , freq_(nullptr)
    , q_(nullptr)
    , rad_(nullptr)
{
    freq_ = new FloatProperty("@freq", 0);
    freq_->setArgIndex(0);
    addProperty(freq_);

    q_ = new FloatProperty("@q", M_SQRT1_2);
    q_->checkClosedRange(0.01, 100);
    addProperty(q_);

    rad_ = new FlagProperty("@rad");
    rad_->setInitOnly();
    addProperty(rad_);

    createOutlet();
}

void FltCalcBiquad::initDone()
{
    if (rad_->value()) {
        freq_->checkClosedRange(0, flt::m_pi);
        freq_->setUnits(PropValueUnits::RAD);
    } else {
        freq_->checkClosedRange(0, sys_getsr() / 2);
        freq_->setUnitsHz();
    }
}

void FltCalcBiquad::onBang()
{
    calc();
    output();
}

void FltCalcBiquad::onFloat(t_float v)
{
    if (!freq_->setValue(v))
        return;

    calc();
    output();
}

double FltCalcBiquad::angleFreq() const
{
    if (rad_->value())
        return freq_->value();
    else
        return flt::hz2w(freq_->value(), sys_getsr());
}

void FltCalcBiquad::m_bandwidth(t_symbol* s, const AtomListView& lv)
{
    if (!checkArgs(lv, ARG_FLOAT, s))
        return;

    auto q = flt::bandwidth2q(lv[0].asT<t_float>(), angleFreq());
    if (!q_->setValue(q))
        return;
}

void FltCalcBiquad::calc_lpf()
{
    const double w = angleFreq();
    const auto cosw = std::cos(w);
    const auto sinw = std::sin(w);
    const auto alpha = sinw / (2 * q_->value());

    b_[0] = (1 - cosw) / 2;
    b_[1] = 1 - cosw;
    b_[2] = b_[0];
    a_[0] = 1 + alpha;
    a_[1] = -2 * cosw;
    a_[2] = 1 - alpha;

    normalizeA();
}

void FltCalcBiquad::calc_hpf()
{
    const double w = angleFreq();
    const auto cosw = std::cos(w);
    const auto sinw = std::sin(w);
    const auto alpha = sinw / (2 * q_->value());

    b_[0] = (1 + cosw) / 2;
    b_[1] = -(1 + cosw);
    b_[2] = b_[0];
    a_[0] = 1 + alpha;
    a_[1] = -2 * cosw;
    a_[2] = 1 - alpha;

    normalizeA();
}

void FltCalcBiquad::output()
{
    Atom res[6];
    res[0] = b_[0];
    res[1] = b_[1];
    res[2] = b_[2];
    res[3] = a_[1];
    res[4] = a_[2];

    listTo(0, AtomListView(res, 5));
}

void FltCalcBiquad::normalizeA()
{
    const auto norm = a_[0];

    for (auto& v : b_)
        v /= norm;

    for (auto& v : a_)
        v /= norm;
}
