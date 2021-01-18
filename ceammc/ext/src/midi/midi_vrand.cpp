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
#include "midi_vrand.h"
#include "ceammc_args.h"
#include "ceammc_convert.h"
#include "ceammc_factory.h"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <ctime>
#include <memory>

static t_symbol* SYM_UNIFORM;
static t_symbol* SYM_GAUSS;
static t_symbol* SYM_LINUP;
static t_symbol* SYM_LINDOWN;
static t_symbol* SYM_CONST_MIN;
static t_symbol* SYM_CONST_MAX;
static t_symbol* SYM_CONST_MEAN;

static std::unique_ptr<ArgChecker> onlist_chk;

MidiVRrand::MidiVRrand(const PdArgs& args)
    : BaseObject(args)
    , min_(nullptr)
    , max_(nullptr)
    , dist_(nullptr)
    , rel_(nullptr)
    , seed_(nullptr)
{
    min_ = new FloatProperty("@min", 0);
    min_->setArgIndex(0);
    addProperty(min_);

    max_ = new FloatProperty("@max", 127);
    max_->setArgIndex(1);
    addProperty(max_);

    dist_ = new SymbolEnumProperty("@dist", {
                                                SYM_UNIFORM,
                                                SYM_GAUSS,
                                                SYM_LINUP,
                                                SYM_LINDOWN,
                                                SYM_CONST_MIN,
                                                SYM_CONST_MAX,
                                                SYM_CONST_MEAN,
                                            });
    addProperty(dist_);

    rel_ = new BoolProperty("@rel", false);
    addProperty(rel_);

    seed_ = new SizeTProperty("@seed", 0);
    seed_->setSuccessFn([this](Property*) {
        const auto sd = seed_->value();
        gen_.seed(sd ? sd : time(nullptr));
    });
    addProperty(seed_);

    createOutlet();
}

void MidiVRrand::onFloat(t_float note)
{
    if (note < 0 || note > 127) {
        OBJ_ERR << "int value in [0..127] range is expected, got: " << note;
        return;
    }

    Atom msg[2] = { note, velocity(64) };
    listTo(0, AtomListView(msg, 2));
}

void MidiVRrand::onList(const AtomList& lst)
{
    if (!onlist_chk->check(lst.view())) {
        OBJ_ERR << "NOTE VEL [DUR] expected, got: " << lst;
        return;
    }

    const size_t N = lst.size();
    assert(N == 2 || N == 3);

    Atom msg[3] = { lst[0], velocity(lst[1].asFloat()), N > 2 ? lst[2] : 0. };
    listTo(0, AtomListView(msg, N));
}

t_float MidiVRrand::generate()
{
    const auto d = dist_->value();
    if (d == SYM_UNIFORM) {
        return std::uniform_int_distribution<int>(min_->value(), max_->value())(gen_);
    } else if (d == SYM_GAUSS) {
        const t_float mu = (min_->value() + max_->value()) / 2;
        const t_float sigma = (max_->value() - min_->value()) / 3;
        return std::normal_distribution<t_float>(mu, sigma)(gen_);
    } else if (d == SYM_LINUP) {
        const std::array<t_float, 2> i = { min_->value(), max_->value() };
        const std::array<t_float, 2> w = { 0, 1 };

        return std::piecewise_linear_distribution<t_float>(
            i.begin(),
            i.end(),
            w.begin())(gen_);
    } else if (d == SYM_LINDOWN) {
        const std::array<t_float, 2> i = { min_->value(), max_->value() };
        const std::array<t_float, 2> w = { 1, 0 };

        return std::piecewise_linear_distribution<t_float>(
            i.begin(),
            i.end(),
            w.begin())(gen_);
    } else if (d == SYM_CONST_MIN) {
        return min_->value();
    } else if (d == SYM_CONST_MAX) {
        return max_->value();
    } else if (d == SYM_CONST_MEAN) {
        return ((max_->value() + min_->value()) / 2);
    } else {
        OBJ_ERR << "unknown distribution: " << d;
        return 0;
    }
}

t_float MidiVRrand::velocity(t_float orig)
{
    if (rel_->value())
        return clip<int, 0, 127>(generate() + orig);
    else
        return clip<int, 0, 127>(generate());
}

void setup_midi_vrand()
{
    SYM_UNIFORM = gensym("uniform");
    SYM_GAUSS = gensym("gauss");
    SYM_LINUP = gensym("linup");
    SYM_LINDOWN = gensym("lindown");
    SYM_CONST_MIN = gensym("cmin");
    SYM_CONST_MAX = gensym("cmax");
    SYM_CONST_MEAN = gensym("cmean");

    onlist_chk.reset(new ArgChecker("f0..127 f0..127 f?"));

    ObjectFactory<MidiVRrand> obj("midi.vrand");
}
