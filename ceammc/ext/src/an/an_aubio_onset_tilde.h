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
#ifndef AN_AUBIO_ONSET_TILDE_H
#define AN_AUBIO_ONSET_TILDE_H

#include "aubio_base.h"
#include "ceammc_clock.h"
#include "ceammc_sound_external.h"

using namespace ceammc;

class AubioOnsetTilde : public SoundExternal {
    IntPropertyMinEq* buffer_size_;
    IntProperty* hop_size_;
    OnsetFloatProperty* threshold_;
    OnsetFloatProperty* delay_;
    OnsetFloatProperty* speedlim_;
    OnsetFloatProperty* silence_threshold_;
    OnsetFloatProperty* compression_;
    OnsetUIntProperty* awhitening_;
    SymbolEnumProperty* method_;
    bool active_;

    int dsp_pos_;
    t_float last_ms_;

    FVecPtr in_, out_;
    OnsetPtr onset_;

    ClockMemberFunction<AubioOnsetTilde> tick_;

public:
    AubioOnsetTilde(const PdArgs& args);

    void parseProperties() final;

    void processBlock(const t_sample** in, t_sample** out) final;
    void samplerateChanged(size_t sr) final;

    void m_reset(t_symbol* m, const AtomList&);

private:
    void clock_tick();
    void initOnset(uint_t sr);
    void updateMethodProperty();
    static void propCallback(BaseObject* this_, t_symbol* name);
};

void setup_an_onset_tilde();

#endif // AN_AUBIO_ONSET_TILDE_H
