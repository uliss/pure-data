/*****************************************************************************
 * Copyright 2018 Serge Poltavsky. All rights reserved.
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
#include "synth_rhodey.h"
#include "ceammc_factory.h"

#include "Rhodey.h"
#include "stksynth_p.h"

typedef StkFMSynth<stk::Rhodey> Synth;

SynthRhodey::SynthRhodey(const PdArgs& args)
    : StkSynth(args, new Synth())
{
    createProperty(new Synth::CCProperty("@mod", 2, *this));
    createProperty(new Synth::CCProperty("@xfade", 4, *this));
    createProperty(new Synth::CCProperty("@lfo_speed", 11, *this));
    createProperty(new Synth::CCProperty("@lfo_depth", 1, *this));
    createProperty(new Synth::CCProperty("@adsr", 128, *this));
}

void setup_synth_rhodey()
{
    SoundExternalFactory<SynthRhodey> obj("synth.rhodey~", OBJECT_FACTORY_DEFAULT);
}