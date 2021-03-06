#include "fx_pitchshift_sig.h"
#include "ceammc_factory.h"

using namespace ceammc;

class FxPitchShiftSig : public faust_fx_pitchshift_sig_tilde {
public:
    FxPitchShiftSig(const PdArgs& args)
        : faust_fx_pitchshift_sig_tilde(args)
    {
    }
};

void setup_fx_pitchshift_sig_tilde()
{
    SoundExternalFactory<FxPitchShiftSig> obj("fx.pitchshift_s~");
    obj.addMethod("reset", &FxPitchShiftSig::m_reset);
}
