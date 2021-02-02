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
#ifndef UI_FILTER_H
#define UI_FILTER_H

#include "ceammc_ui_object.h"

#include <array>

using namespace ceammc;

class UIFilter : public UIObject {
    t_float b0_, b1_, b2_, a1_, a2_;
    t_pt knob_pt_;
    t_symbol* prop_type;
    t_symbol* prop_scale;
    t_rgba prop_color_grid;
    t_rgba prop_color_plot;
    t_rgba prop_color_knob;
    t_float prop_freq;
    t_float prop_q;
    t_float prop_gain;

public:
    UIFilter();

    bool okSize(t_rect* newrect);
    void paint();

    void onList(const AtomListView& lv);

    void onMouseDown(t_object* view, const t_pt& pt, const t_pt& abs_pt, long modifiers);
    void onMouseUp(t_object* view, const t_pt& pt, long modifiers);
    void onMouseDrag(t_object* view, const t_pt& pt, long modifiers);
    void onMouseWheel(const t_pt& pt, long modifiers, float delta);

    void onPropChange(t_symbol* name);

    void loadPreset(size_t idx);
    void storePreset(size_t idx);

public:
    using Array = std::array<double, 6>;

private:
    void updateCoeffs();
    float q() const;
    float calcDb() const;
    float calcBandwidth(float q, float w) const;
    void saveMousePoint(const t_pt& pt);
    void output();
    void setBA(const Array& ba);

    void knobUpdateFreq();
    void knobUpdateQ();
    void knobUpdateGain();

    void freqUpdateKnob();
    void qUpdateKnob();
    void gainUpdateKnob();

    double nyquistFreq() const { return 0.5 * sys_getsr(); }

public:
    static void setup();
};

void setup_ui_filter();

#endif // UI_FILTER_H
