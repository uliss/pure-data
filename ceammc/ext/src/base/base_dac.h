/*****************************************************************************
 * Copyright 2019 Serge Poltavsky. All rights reserved.
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
#ifndef BASE_DAC_H
#define BASE_DAC_H

#include "ceammc_sound_external.h"

using namespace ceammc;

class BaseDac : public SoundExternal {
    std::vector<t_int> vec_;

public:
    BaseDac(const PdArgs& args);
    void parseProperties() override;
    void processBlock(const t_sample** in, t_sample** out) override;
    void setupDSP(t_signal** sp) override;

    void m_click(t_symbol* s, const AtomList& l);
};

void setup_base_dac();

#endif // BASE_DAC_H
