/*****************************************************************************
 * Copyright 2019 Serge Poltavsky. All rights reserved.
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
#include "hoa_recomposer.h"
#include "ceammc_factory.h"

static t_symbol* SYM_FREE;
static t_symbol* SYM_FIXE;
static t_symbol* SYM_FISHEYE;

HoaRecomposer::HoaRecomposer(const PdArgs& args)
    : HoaBase(args)
    , plain_waves_(nullptr)
    , mode_(nullptr)
    , ramp_(100)
{
    plain_waves_ = new IntProperty("@n", 0);
    createProperty(plain_waves_);

    mode_ = new SymbolEnumProperty("@mode", SYM_FREE);
    mode_->appendEnum(SYM_FIXE);
    mode_->appendEnum(SYM_FISHEYE);
    createProperty(mode_);

    createProperty(new SymbolEnumAlias("@free", mode_, SYM_FREE));
    createProperty(new SymbolEnumAlias("@fixe", mode_, SYM_FIXE));
    createProperty(new SymbolEnumAlias("@fisheye", mode_, SYM_FISHEYE));

    createCbProperty("@ramp", &HoaRecomposer::propRamp, &HoaRecomposer::propSetRamp);
}

void HoaRecomposer::parseProperties()
{
    HoaBase::parseProperties();
    parseNumPlainWaves();
    mode_->setReadonly(true);

    processor_.reset(new MultiEncoder2d(order(), plain_waves_->value()));

    if (mode_->value() == SYM_FREE) {
        lines_.reset(new PolarLines2d(plain_waves_->value()));
        lines_->setRamp(ramp_ / 1000 * sys_getsr());

        const size_t NSRC = processor_->getNumberOfSources();

        for (size_t i = 0; i < NSRC; i++) {
            lines_->setRadiusDirect(i, processor_->getWidening(i));
            lines_->setAzimuthDirect(i, processor_->getAzimuth(i));
        }

        line_buf_.resize(NSRC * 2);
    }

    createSignalInlets(processor_->getNumberOfSources() + (mode_->value() == SYM_FISHEYE ? 1 : 0));
    createSignalOutlets(processor_->getNumberOfHarmonics());

    in_buf_.resize(numInputChannels() * HOA_DEFAULT_BLOCK_SIZE);
    out_buf_.resize(numOutputChannels() * HOA_DEFAULT_BLOCK_SIZE);
}

void HoaRecomposer::blocksizeChanged(size_t bs)
{
    in_buf_.resize(numInputChannels() * bs);
    out_buf_.resize(numOutputChannels() * bs);
}

void HoaRecomposer::processBlock(const t_sample** in, t_sample** out)
{
}

void HoaRecomposer::setupDSP(t_signal** sp)
{
    HoaBase::setupDSP(sp);

    if (mode_->value() == SYM_FIXE) {
        dsp_add(dspPerformFixE, 1, static_cast<void*>(this));
    } else if (mode_->value() == SYM_FISHEYE) {
        dsp_add(dspPerformFisheye, 1, static_cast<void*>(this));
    } else if (mode_->value() == SYM_FREE) {
        lines_->setRamp(ramp_ / 1000 * sys_getsr());
        dsp_add(dspPerformFree, 1, static_cast<void*>(this));
    } else
        OBJ_ERR << "unknown mode: " << mode_->value();
}

void HoaRecomposer::m_angle(t_symbol* s, const AtomList& lst)
{
    const size_t N = std::min(lst.size(), processor_->getNumberOfSources());
    for (size_t i = 0; i < N; i++)
        lines_->setAzimuth(i, lst[i].asFloat());
}

void HoaRecomposer::m_wide(t_symbol* s, const AtomList& lst)
{
    const size_t N = std::min(lst.size(), processor_->getNumberOfSources());
    for (size_t i = 0; i < N; i++)
        lines_->setRadius(i, lst[i].asFloat());
}

AtomList HoaRecomposer::propRamp() const
{
    return Atom(ramp_);
}

void HoaRecomposer::propSetRamp(const AtomList& lst)
{
    if (!lst.isFloat()) {
        OBJ_ERR << "ramp: float value expected: " << lst;
        return;
    }

    auto v = lst.floatAt(0, 0);
    if (v < 0) {
        OBJ_ERR << "ramp: >= 0 value expected: " << v;
        return;
    }

    ramp_ = v;
    lines_->setRamp(ramp_ / 1000 * sys_getsr());
}

void HoaRecomposer::parseNumPlainWaves()
{
    const int MIN_PW_COUNT = 2 * order() + 1;

    auto pos_arg = positionalFloatArgument(1, 0);
    if (pos_arg != 0)
        plain_waves_->setValue(pos_arg);

    const auto N = plain_waves_->value();

    if (N < MIN_PW_COUNT) {
        // zero means auto calc
        if (N != 0)
            OBJ_ERR << "minimal number of plain waves should be >= " << MIN_PW_COUNT << ", setting to this value";

        plain_waves_->setValue(MIN_PW_COUNT);
    }

    plain_waves_->setReadonly(true);
}

void HoaRecomposer::processFixE()
{
    const size_t NINS = numInputChannels();
    const size_t NOUTS = numOutputChannels();
    const size_t BS = blockSize();

    t_sample** in_blocks = inputBlocks();
    t_sample** out_blocks = outputBlocks();

    for (size_t i = 0; i < NINS; i++)
        Signal::copy(BS, &in_blocks[i][0], 1, &in_buf_[i], NINS);

    for (size_t i = 0; i < BS; i++)
        processor_->process(&in_buf_[NINS * i], &out_buf_[NOUTS * i]);

    for (size_t i = 0; i < NOUTS; i++)
        Signal::copy(BS, &out_buf_[i], NOUTS, &out_blocks[i][0], 1);
}

void HoaRecomposer::processFree()
{
    const size_t NINS = numInputChannels();
    const size_t NOUTS = numOutputChannels();
    const size_t BS = blockSize();

    t_sample** in_blocks = inputBlocks();
    t_sample** out_blocks = outputBlocks();

    for (size_t i = 0; i < NINS; i++)
        Signal::copy(BS, &in_blocks[i][0], 1, &in_buf_[i], NINS);

    for (size_t i = 0; i < BS; i++) {
        lines_->process(line_buf_.data());

        for (size_t j = 0; j < NINS; j++)
            processor_->setWidening(j, line_buf_[j]);

        for (size_t j = 0; j < NINS; j++)
            processor_->setAzimuth(j, line_buf_[j + NINS]);

        processor_->process(&in_buf_[NINS * i], &out_buf_[NOUTS * i]);
    }

    for (size_t i = 0; i < NOUTS; i++)
        Signal::copy(BS, &out_buf_[i], NOUTS, &out_blocks[i][0], 1);
}

void HoaRecomposer::processFisheye()
{
    const size_t NPWS = numInputChannels() - 1;
    const size_t NOUTS = numOutputChannels();
    const size_t BS = blockSize();

    t_sample** in_blocks = inputBlocks();
    t_sample** out_blocks = outputBlocks();

    for (size_t i = 0; i < NPWS; i++)
        Signal::copy(BS, &in_blocks[i][0], 1, &in_buf_[i], NPWS);

    for (size_t i = 0; i < BS; i++) {
        // set from last inlet
        processor_->setFisheye(in_blocks[NPWS][i]);
        processor_->process(&in_buf_[NPWS * i], &out_buf_[NOUTS * i]);
    }

    for (size_t i = 0; i < NOUTS; i++)
        Signal::copy(BS, &out_buf_[i], NOUTS, &out_blocks[i][0], 1);
}

void setup_spat_hoa_recomposer()
{
    SYM_FREE = gensym("free");
    SYM_FIXE = gensym("fixe");
    SYM_FISHEYE = gensym("fisheye");

    SoundExternalFactory<HoaRecomposer> obj("!hoa.recomposer~");
    obj.addMethod("angle", &HoaRecomposer::m_angle);
    obj.addMethod("wide", &HoaRecomposer::m_wide);
}