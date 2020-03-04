/// this file is autogenerated, do not edit!
#include <cmath>

#include "ceammc_factory.h"
#include "ceammc_object.h"
#include "ceammc_sound_external.h"

using namespace ceammc;
        

class MathExp2 : public BaseObject
{
public:
    MathExp2(const PdArgs& a) : BaseObject(a)
    {
        createOutlet();
    }

    void onFloat(t_float f) final
    {
        floatTo(0, std::exp2(f));
    }

    void onList(const AtomList& l) final
    {
        listTo(0, l.map(std::exp2));
    }

};


class MathExp2Tilde : public SoundExternal
{
public:
    MathExp2Tilde(const PdArgs& a) : SoundExternal(a)
    {
        createSignalOutlet();
    }

    void processBlock(const t_sample** in, t_sample** out) final
    {
        const auto BS = blockSize();
        for(size_t i = 0; i < BS; i += 8) {
            out[0][i+0] = std::exp2(in[0][i+0]);
            out[0][i+1] = std::exp2(in[0][i+1]);
            out[0][i+2] = std::exp2(in[0][i+2]);
            out[0][i+3] = std::exp2(in[0][i+3]);
            out[0][i+4] = std::exp2(in[0][i+4]);
            out[0][i+5] = std::exp2(in[0][i+5]);
            out[0][i+6] = std::exp2(in[0][i+6]);
            out[0][i+7] = std::exp2(in[0][i+7]);
        }
    }
};


void setup_math_exp2() {
    ObjectFactory<MathExp2> obj0("math.exp2");
    SoundExternalFactory<MathExp2Tilde> obj1("math.exp2~");
}
        