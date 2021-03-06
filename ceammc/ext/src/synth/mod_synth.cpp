#include "mod_synth.h"
#include "ceammc_platform.h"
#include "synth_bthree.h"
#include "synth_fgrain.h"
#include "synth_rhodey.h"
#include "synth_shakers.h"
#include "synth_sitar.h"
#include "synth_wurley.h"

extern void setup_synth_birds_tilde();
extern void setup_synth_church_bell_tilde();
extern void setup_synth_dubdub_tilde();
extern void setup_synth_dx7_tilde();
extern void setup_synth_eguitar_tilde();
extern void setup_synth_glass_harm_tilde();
extern void setup_synth_glitch();
extern void setup_synth_ks_tilde();
extern void setup_synth_harpsichord_tilde();
extern void setup_synth_marimba_tilde();
extern void setup_synth_risset_arp_tilde();
extern void setup_synth_risset_tone_tilde();
extern void setup_synth_russian_bell_tilde();
extern void setup_synth_piano_tilde();

void ceammc_synth_setup()
{
    // STK synths
    setup_synth_bthree();
    setup_synth_fgrain();
    setup_synth_rhodey();
    setup_synth_shakers();
    setup_synth_sitar();
    setup_synth_wurley();

    // faust synth
    setup_synth_birds_tilde();
    setup_synth_church_bell_tilde();
    setup_synth_dubdub_tilde();
    setup_synth_dx7_tilde();
    setup_synth_eguitar_tilde();
    setup_synth_glass_harm_tilde();
    setup_synth_harpsichord_tilde();
    setup_synth_ks_tilde();
    setup_synth_marimba_tilde();
    setup_synth_piano_tilde();
    setup_synth_risset_arp_tilde();
    setup_synth_risset_tone_tilde();
    setup_synth_russian_bell_tilde();

    // Glitch
    setup_synth_glitch();
}
