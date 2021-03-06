#include "MSPd.h"
#define OBJECT_NAME "quadpan~"
/*
 
 Front
 
 *out1         *out3
 
 
 
 *out2         *out4
 
 Back
 
 */

static t_class* quadpan_class;

typedef struct _quadpan {
    t_object x_obj;
    t_float x_f;
    //    short bypass;
    //    float pi_over_two;
    //    float twopi;
    float* in;
    float* Xin;
    float* Yin;
} t_quadpan;

void* quadpan_new(t_symbol* s, int argc, t_atom* argv);
t_int* offset_perform(t_int* w);
t_int* quadpan_perform(t_int* w);
void quadpan_dsp(t_quadpan* x, t_signal** sp);
void quadpan_showstate(t_quadpan* x);
void quadpan_free(t_quadpan* x);
void quadpan_tilde_setup(void)
{
    quadpan_class = class_new(gensym("quadpan~"), (t_newmethod)quadpan_new, (t_method)quadpan_free, sizeof(t_quadpan), 0, A_GIMME, 0);
    CLASS_MAINSIGNALIN(quadpan_class, t_quadpan, x_f);
    class_addmethod(quadpan_class, (t_method)quadpan_dsp, gensym("dsp"), A_CANT, 0);

    potpourri_announce(OBJECT_NAME);
}

void* quadpan_new(t_symbol* s, int argc, t_atom* argv)
{
    int i;
    t_quadpan* x = (t_quadpan*)pd_new(quadpan_class);

    for (i = 0; i < 2; i++) {
        inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("signal"), gensym("signal"));
    }
    for (i = 0; i < 4; i++) {
        outlet_new(&x->x_obj, gensym("signal"));
    }
    x->in = (float*)malloc(8192 * sizeof(float));
    x->Xin = (float*)malloc(8192 * sizeof(float));
    x->Yin = (float*)malloc(8192 * sizeof(float));
    //    x->pi_over_two = 1.5707963267948965;
    //    x->twopi = 6.283185307179586;

    return x;
}
void quadpan_free(t_quadpan* x)
{
    free(x->in);
    free(x->Xin);
    free(x->Yin);
}

t_int* quadpan_perform(t_int* w)
{
    float gain1, gain2, gain3, gain4;
    float xval, yval;
    float xsquared, ysquared, ix, iy, ixsquared, iysquared;
    int i;

    t_quadpan* x = (t_quadpan*)(w[1]);
    float* in = x->in;
    float* Xin = x->Xin;
    float* Yin = x->Yin;

    t_sample* in_loc = (t_sample*)(w[2]);
    t_sample* Xin_loc = (t_sample*)(w[3]);
    t_sample* Yin_loc = (t_sample*)(w[4]);

    t_sample* out1 = (t_sample*)(w[5]);
    t_sample* out2 = (t_sample*)(w[6]);
    t_sample* out3 = (t_sample*)(w[7]);
    t_sample* out4 = (t_sample*)(w[8]);
    int n = (int)(w[9]);

    // copy buffers to avoid writeovers in shared memory
    for (i = 0; i < n; i++) {
        in[i] = in_loc[i];
        Xin[i] = Xin_loc[i];
        Yin[i] = Yin_loc[i];
    }

    while (n--) {
        xval = *Xin++;
        yval = *Yin++;
        if (xval < 0.0)
            xval = 0.0;
        if (yval > 1.0)
            yval = 1.0;
        if (yval < 0.0)
            yval = 0.0;
        if (yval > 1.0)
            yval = 1.0;

        xsquared = xval * xval;
        ysquared = yval * yval;
        ix = 1.0 - xval;
        iy = 1.0 - yval;
        ixsquared = ix * ix;
        iysquared = iy * iy;

        gain1 = sqrt(xsquared + ysquared);
        if (gain1 > 1.0)
            gain1 = 1.0;
        gain1 = 1.0 - gain1; /* Left Rear Gain */

        gain2 = sqrt(ixsquared + ysquared);
        if (gain2 > 1.0)
            gain2 = 1.0;
        gain2 = 1.0 - gain2; /* Right Rear Gain */

        gain3 = sqrt(xsquared + iysquared);
        if (gain3 > 1.0)
            gain3 = 1.0;
        gain3 = 1.0 - gain3; /* Left Front Gain */

        gain4 = sqrt(ixsquared + iysquared);
        if (gain4 > 1.0)
            gain4 = 1.0;
        gain4 = 1.0 - gain4; /* Right Front Gain*/

        *out1++ = *in * gain3;
        *out2++ = *in * gain4;
        *out3++ = *in * gain2;
        *out4++ = *in++ * gain1;
    }

    return (w + 10);
}

void quadpan_dsp(t_quadpan* x, t_signal** sp)
{
    if (!sp[0]->s_sr) {
        return;
    }
    dsp_add(quadpan_perform, 9, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec,
        sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec,
        sp[0]->s_n);
}
