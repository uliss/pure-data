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
#include "view.h"
#include "ceammc_convert.h"
#include "ceammc_log.h"

namespace ceammc {
namespace ui {

    void EmptyViewImpl::create(const RectF& /*bbox*/, const EmptyData& /*data*/) { }

    void EmptyViewImpl::erase() { }

    void EmptyViewImpl::update(const RectF& /*bbox*/, const EmptyData& /*data*/) { }

    void EmptyViewImpl::updateCoords(const RectF& /*bbox*/) { }

    FrameView::FrameView(FrameModel* model, ViewImplPtr&& impl, const PointF& pos)
        : ModelView<FrameData>(model, std::move(impl), pos)
    {
    }

    void FrameView::create(WinId win, WidgetId wid, float scale)
    {
        child_->create(win, wid, scale);
        Base::create(win, wid, scale);
    }

    void FrameView::erase()
    {
        child_->erase();
        Base::erase();
    }

    void FrameView::redraw()
    {
        child_->redraw();
        Base::redraw();
    }

    void FrameView::updateCoords()
    {
        child_->updateCoords();
        Base::updateCoords();
    }

    void FrameView::layout()
    {
        if (!child_)
            return;

        auto pad = model() ? model()->getT<int, FrameData::PADDING>() : 0;
        child_->setPos(PointF(pad, pad));
        child_->layout();
        auto sz = child_->size();
        sz.enlarge(pad * 2, pad * 2);
        setSize(sz);
    }

    void FrameView::setChild(ViewPtr&& v)
    {
        child_ = std::move(v);
        child_->setParent(this);
    }

    EventStatus FrameView::onEvent(EventType t, const PointF& pos, const EventContext& ctx)
    {
        if (!child_ || !absBBox().contains(pos))
            return EVENT_STATUS_IGNORE;

        return child_->onEvent(t, pos, ctx);
    }

    EmptyModel GroupView::empty_model;

    GroupView::GroupView(ViewImplPtr&& impl, const PointF& pos)
        : ModelView<EmptyData>(&empty_model, std::move(impl), pos)
    {
    }

    void GroupView::add(ViewPtr&& b)
    {
        if (!b)
            return;

        views_.push_back(std::move(b));
        views_.back()->setParent(this);
    }

    void GroupView::create(WinId win, WidgetId wid, float scale)
    {
        for (auto& v : views_)
            v->create(win, wid, scale);
    }

    void GroupView::erase()
    {
        for (auto& v : views_)
            v->erase();
    }

    void GroupView::redraw()
    {
        for (auto& v : views_)
            v->redraw();
    }

    void GroupView::updateCoords()
    {
        for (auto& v : views_)
            v->updateCoords();
    }

    void GroupView::layout()
    {
        for (auto& v : views_)
            v->layout();

        if (layout_) {
            layout_->doLayout(views_);
            adjustBBox();
        }
    }

    RectF GroupView::calcBBox() const
    {
        RectF res;
        if (views_.empty())
            return res;

        res = RectF(views_[0]->pos(), views_[0]->size());
        for (size_t i = 1; i < views_.size(); i++)
            res = res.unite(RectF(views_[i]->pos(), views_[i]->size()));

        return res;
    }

    EventStatus GroupView::onEvent(EventType t, const PointF& pos, const EventContext& ctx)
    {
        if (!absBBox().contains(pos))
            return EVENT_STATUS_IGNORE;

        int continue_num = 0;

        for (auto& v : views_) {
            auto status = v->onEvent(t, pos, ctx);
            switch (status) {
            case EVENT_STATUS_ACCEPT:
                return status;
            case EVENT_STATUS_CONTINUE:
                continue_num++;
                continue;
                break;
            case EVENT_STATUS_IGNORE:
            default:
                continue;
                break;
            }
        }

        return (continue_num > 0)
            ? EVENT_STATUS_CONTINUE
            : EVENT_STATUS_IGNORE;
    }

    void GroupView::adjustBBox()
    {
        if (views_.empty())
            return;

        const RectF bbox = calcBBox();
        size_ = bbox.size();
    }

    HGroupView::HGroupView(const PointF& pos)
        : GroupView(ViewImplPtr(new EmptyViewImpl), pos)
    {
        this->setLayout(new HLayout);
    }

    void HGroupView::setSpace(float space)
    {
        if (this->getLayout()) {
            auto lt = static_cast<HLayout*>(this->getLayout().get());
            lt->setSpace(space);
        } else {
            this->setLayout(new HLayout(space));
        }
    }

    VGroupView::VGroupView(const PointF& pos)
        : GroupView(ViewImplPtr(new EmptyViewImpl), pos)
    {
        this->setLayout(new VLayout);
    }

    void VGroupView::setSpace(float space)
    {
        if (this->getLayout()) {
            auto lt = static_cast<VLayout*>(this->getLayout().get());
            lt->setSpace(space);
        } else {
            this->setLayout(new VLayout(space));
        }
    }

    ModelViewBase::~ModelViewBase() { }

    HSliderView::HSliderView(SliderModel* model, ModelView::ViewImplPtr&& impl, const PointF& pos)
        : ModelView<SliderData>(model, std::move(impl), pos)
    {
    }

    EventStatus HSliderView::onEvent(EventType t, const PointF& pos, const EventContext& ctx)
    {
        if (!absBBox().contains(pos))
            return EVENT_STATUS_IGNORE;

        switch (t) {
        case EVENT_MOUSE_DOWN: {
            auto vpos = toViewCoords(pos);
            auto value = convert::lin2lin<t_float>(vpos.x(), 0, size().width(), this->data().min(), this->data().max());
            this->data().setValue(value);
            this->redraw();
            this->notifyOthers();
        } break;
        case EVENT_MOUSE_DRAG: {
            auto vpos = toViewCoords(pos);
            LIB_ERR << vpos;
            auto value = convert::lin2lin<t_float>(vpos.x(), 0, size().width(), this->data().min(), this->data().max());
            this->data().setValue(value);
            this->redraw();
            this->notifyOthers();
        } break;
        case EVENT_MOUSE_UP:
            break;
        default:
            return EVENT_STATUS_IGNORE;
        }

        LIB_ERR << __FUNCTION__;
        return EVENT_STATUS_ACCEPT;
    }

    PointF HSliderView::toViewCoords(const PointF& pt) const
    {
        const auto abs = absPos();
        return { pt.x() - abs.x(), pt.y() - abs.y() };
    }

}
}
