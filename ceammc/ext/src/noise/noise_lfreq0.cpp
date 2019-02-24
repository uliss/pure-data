#include "noise_lfreq0.h"
#include "ceammc_factory.h"

using namespace ceammc;

static t_symbol* SYM_PROP_FREQ = gensym("@freq");

class NoiseLfreq0 : public faust_noise_lfreq0_tilde {
public:
    NoiseLfreq0(const PdArgs& args)
        : faust_noise_lfreq0_tilde(args)
    {
        bindPositionalArgsToProps({ SYM_PROP_FREQ });
    }
};

void setup_noise_lfreq0_tilde()
{
    SoundExternalFactory<NoiseLfreq0> obj("noise.lfreq0~");
}
