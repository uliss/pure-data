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
#ifndef WIDGET_H
#define WIDGET_H

#include <array>
#include <cstdint>
#include <type_traits>

#include "ceammc_canvas.h"
#include "ceammc_object.h"
#include "nui/common.h"
#include "nui/rect.h"

namespace ceammc {
namespace ui {

    namespace utils {
        int canvas_zoom(const t_glist* c);
        bool canvas_is_visible(const t_glist* c);
        bool canvas_is_edit(const t_glist* c);
        void canvas_delete_object_lines(const t_glist* c, t_text* x);
        void canvas_update_object_lines(const t_glist* c, t_text* x);
        Point object_pos(t_text* x);
        Point object_abs_pos(t_text* x, const t_glist* parent);
        void object_move(t_text* x, int dx, int dy);
        void object_bind(t_text* x);
        t_glist* object_get_draw_canvas(t_glist* c);
        void widget_bind_mouse(t_glist* c, t_object* obj, UIFactoryFlags flags);
        void widget_create(t_glist* c, t_object* obj, const Point& pos, const Size& sz, int zoom);
        void widget_erase(t_glist* c, t_object* obj);
        void widget_focus(t_glist* c, t_object* obj);
    }

    template <typename T>
    class Widget : public T {
        Size size_;
        std::vector<Property*> widget_props_;
        UIFactoryFlags ui_flags_ { UI_FACTORY_NONE };
        t_glist* draw_canvas_;
        bool mouse_down_ = { false };

    public:
        Widget(const PdArgs& args)
            : T(args)
        {
            static_assert(std::is_base_of<BaseObject, T>::value, "");

            draw_canvas_ = T::canvas();
        }

        void initDone() override
        {
            T::initDone();
            buildUI();
        }

        void setWidgetFlags(UIFactoryFlags flags)
        {
            LIB_ERR << __FUNCTION__;
            ui_flags_ = flags;
            subscribeMouseEvents();
        }

        Property* addWidgetProperty(Property* p)
        {
            T::addProperty(p);
            widget_props_.push_back(p);
            p->setSuccessFn([this](Property* p) { notifyPropChange(p); });
            return p;
        }

        Point absPos() const { return utils::object_abs_pos(T::owner(), T::canvas()); }
        const Size& size() const { return size_; }
        void setSize(const Size& sz) { size_ = sz; }
        int zoom() const { return utils::canvas_zoom(T::canvas()); }
        bool isVisible() const { return utils::canvas_is_visible(T::canvas()); }
        bool isEdit() const { return utils::canvas_is_edit(drawCanvasCache()); }

        t_glist* drawCanvasCache() const { return draw_canvas_; }
        void syncDrawCanvasCache() { draw_canvas_ = utils::object_get_draw_canvas(T::canvas()); }

        Rect viewBBox(t_glist* owner) const { return Rect(absPos(), size_ * zoom()); }

        virtual void activateWidget(t_glist* owner, bool state)
        {
            LIB_ERR << __FUNCTION__;
        }

        virtual void displaceWidget(t_glist* owner, int dx, int dy)
        {
            LIB_ERR << __FUNCTION__;

            syncDrawCanvasCache();
            utils::object_move(T::owner(), dx, dy);

            if (isVisible()) {
                const Point norm_pos = absPos() / zoom();
                // move model/view
                //                view_.move(norm_pos);
                utils::canvas_update_object_lines(drawCanvasCache(), T::owner());
            }
        }

        virtual void deleteWidget(t_glist* owner)
        {
            LIB_ERR << __FUNCTION__;

            syncDrawCanvasCache();
            utils::canvas_delete_object_lines(drawCanvasCache(), T::owner());
        }

        virtual void selectWidget(t_glist* owner, bool state)
        {
            LIB_ERR << __FUNCTION__;

            syncDrawCanvasCache();
        }

        virtual void showWidget(t_glist* owner)
        {
            LIB_ERR << __FUNCTION__;

            syncDrawCanvasCache();
            utils::widget_create(drawCanvasCache(), T::owner(), absPos(), size(), zoom());
            utils::widget_bind_mouse(drawCanvasCache(), T::owner(), ui_flags_);
        }

        virtual void hideWidget(t_glist* owner)
        {
            LIB_ERR << __FUNCTION__;

            syncDrawCanvasCache();
            utils::widget_erase(drawCanvasCache(), T::owner());
        }

        virtual void buildUI()
        {
            // view controller
        }

        virtual void notifyPropChange(Property* p)
        {
        }

        virtual void onMouseEnter() { LIB_ERR << __FUNCTION__; }
        virtual void onMouseLeave() { LIB_ERR << __FUNCTION__; }
        virtual void onMouseMove() { LIB_ERR << __FUNCTION__; }

        void mouseEnter()
        {
            syncDrawCanvasCache();

            if (!isEdit() && !mouse_down_) {
                utils::widget_focus(drawCanvasCache(), T::owner());
                onMouseEnter();
            }
        }

        void mouseLeave()
        {
            syncDrawCanvasCache();

            if (!isEdit() && !mouse_down_) {
                onMouseLeave();
            }
        }

        void mouseMove(const Point& pt, uint32_t mod)
        {
            LIB_ERR << __FUNCTION__ << ' ' << pt << ", mod: " << mod;
        }

    private:
        void subscribeMouseEvents()
        {
            utils::object_bind(T::owner());
        }
    };

}
}

#endif // WIDGET_H
