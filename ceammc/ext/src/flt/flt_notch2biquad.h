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
#ifndef FLT_NOTCH2BIQUAD_H
#define FLT_NOTCH2BIQUAD_H

#include "flt_calc_biquad.h"

class FltNotch2Biquad : public FltCalcBiquad {
public:
    FltNotch2Biquad(const PdArgs& args);
    void calc() override;
};

void setup_flt_c_notch();

#endif // FLT_NOTCH2BIQUAD_H
