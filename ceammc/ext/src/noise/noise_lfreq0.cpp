#include "noise_lfreq0.h"

EXTERNAL_NEW
{
    FAUST_EXT* x = reinterpret_cast<FAUST_EXT*>(pd_new(FAUST_EXT_CLASS));
    PdArgParser p(x, argc, argv);
    p.initFloatArg("freq", 1);
    return p.pd_obj();
}

EXTERNAL_SETUP_NO_IN(noise);