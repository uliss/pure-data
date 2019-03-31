#ifndef CEAMMC_NEW_GUI_H
#define CEAMMC_NEW_GUI_H

#include "ceammc_atomlist.h"
#include "ceammc_cicm.h"
#include "ceammc_data.h"
#include "ceammc_externals.h"
#include "ceammc_log.h"
#include "m_pd.h"

#include <string>
#include <unordered_map>
#include <utility>

namespace ceammc {

static const char* DEFAULT_ACTIVE_COLOR = "0. 0.75 1. 1.";
static const char* DEFAULT_BORDER_COLOR = "0.6 0.6 0.6 1.";
static const char* DEFAULT_BACKGROUND_COLOR = "0.93 0.93 0.93 1.";
static const char* DEFAULT_TEXT_COLOR = "0. 0. 0. 1.";

static const char* PROP_ACTIVE_COLOR = "active_color";
static const char* PROP_BACKGROUND_COLOR = "background_color";
static const char* PROP_BORDER_COLOR = "border_color";
static const char* PROP_TEXT_COLOR = "text_color";

static const char* PROP_PRESET_NAME = "presetname";

//! Gettext extract message helper
#ifndef _
#define _(msg) msg
#endif

#define UI_METHOD_PTR(m) reinterpret_cast<t_typ_method>(&UIObjectFactory<UI>::m)

#define HIDE_FONT_PROPS(cl)                        \
    {                                              \
        CLASS_ATTR_INVISIBLE(cl, "fontname", 1);   \
        CLASS_ATTR_INVISIBLE(cl, "fontweight", 1); \
        CLASS_ATTR_INVISIBLE(cl, "fontslant", 1);  \
        CLASS_ATTR_INVISIBLE(cl, "fontsize", 1);   \
    }

// clang-format off
enum MouseEvents {
    UI_MOUSE_DOWN      = 1,
    UI_MOUSE_UP        = 1 << 1,
    UI_MOUSE_DRAG      = 1 << 2,
    UI_MOUSE_ENTER     = 1 << 3,
    UI_MOUSE_LEAVE     = 1 << 4,
    UI_MOUSE_MOVE      = 1 << 5,
    UI_MOUSE_DBL_CLICK = 1 << 6,
    UI_MOUSE_WHEEL     = 1 << 7
};
// clang-format on

template <class UI>
class UIObjectFactory {
    std::string name_;

public:
    typedef void (UI::*bangMethodPtr)();
    typedef void (UI::*floatMethodPtr)(t_float);
    typedef void (UI::*listMethodPtr)(const AtomList&);
    typedef float (UI::*propFloatGet)() const;
    typedef void (UI::*propFloatSet)(float);
    typedef AtomList (UI::*propListGet)() const;
    typedef void (UI::*propListSet)(const AtomList&);
    typedef std::pair<propFloatGet, propFloatSet> propertyFloatAccess;
    typedef std::pair<propListGet, propListSet> propertyListAccess;

    typedef std::unordered_map<t_symbol*, bangMethodPtr> BangMethodMap;
    typedef std::unordered_map<t_symbol*, floatMethodPtr> FloatMethodMap;
    typedef std::unordered_map<t_symbol*, listMethodPtr> ListMethodMap;
    typedef std::unordered_map<t_symbol*, propertyFloatAccess> FloatPropertyMap;
    typedef std::unordered_map<t_symbol*, propertyListAccess> ListPropertyMap;

public:
    UIObjectFactory(const char* name, long fl = EBOX_GROWINDI, int pd_flags = 0)
        : name_(name)
    {
        flags = fl;
        if (pd_class) {
            pd_error(0, "class already initialized: %s", name);
            return;
        }

        pd_class = eclass_new(name_.c_str(),
            UI_METHOD_PTR(alloc),
            UI_METHOD_PTR(free),
            sizeof(UI), pd_flags, A_GIMME, 0);

        if (!pd_class) {
            pd_error(0, "can't allocate class: %s", name);
            return;
        }

        eclass_guiinit(pd_class, flags);
        setupMethods();
        setupAttributes();
        register_ui_external(&pd_class->c_class);
    }

    ~UIObjectFactory()
    {
        eclass_attr_sort(pd_class);
        eclass_register(CLASS_BOX, pd_class);
    }

    static UI* alloc(t_symbol* s, int argc, t_atom* argv)
    {
        void* mem = eobj_new(pd_class);
        t_binbuf* d = binbuf_via_atoms(argc, argv);

        if (mem && d) {
            UI* x = new (mem) UI();

            ebox_new(x->asEBox(), 0 | flags);
            ebox_attrprocess_viabinbuf(x, d);
            ebox_ready((t_ebox*)x);
            binbuf_free(d);

            x->init(s, AtomList(argc, argv), use_presets);
            return x;
        }

        return 0;
    }

    static void free(UI* x)
    {
        if (x) {
            x->~UI();
            ebox_free(x->asEBox());
        }
    }

    void setupMethods()
    {
        // clang-format off
        eclass_addmethod(pd_class, UI_METHOD_PTR(paint),         "paint",         A_GIMME, 0);

        eclass_addmethod(pd_class, UI_METHOD_PTR(notify),        "notify",        A_GIMME,  0);
        eclass_addmethod(pd_class, UI_METHOD_PTR(okSize),        "oksize",        A_GIMME,  0);
        eclass_addmethod(pd_class, UI_METHOD_PTR(onZoom),        "onzoom",        A_GIMME,  0);
        eclass_addmethod(pd_class, UI_METHOD_PTR(onPopup),       "popup",        A_GIMME,  0);
        eclass_addmethod(pd_class, UI_METHOD_PTR(setDrawParams), "getdrawparams", A_NULL, 0);
        // clang-format on
    }

    void setupAttributes()
    {
        // clang-format off
        //hide standard CICM attributes
        HIDE_FONT_PROPS(pd_class);

        // background / border color
        addProperty(PROP_BACKGROUND_COLOR,
                    _("Background Color"),
                    DEFAULT_BACKGROUND_COLOR,
                    &UI::prop_color_background);

        addProperty(PROP_BORDER_COLOR,
                    _("Border Color"),
                    DEFAULT_BORDER_COLOR,
                    &UI::prop_color_border);

        // default
        CLASS_ATTR_DEFAULT              (pd_class, "size", 0, "45. 15.");
        // clang-format on
    }

    void usePresets()
    {
        // clang-format off

        UIObjectFactory::use_presets = true;

        eclass_addmethod(pd_class, UI_METHOD_PTR(loadPreset),      "load",          A_GIMME,  0);
        eclass_addmethod(pd_class, UI_METHOD_PTR(storePreset),     "store",         A_GIMME,  0);
        eclass_addmethod(pd_class, UI_METHOD_PTR(clearPreset),     "clear",         A_GIMME,  0);

        CLASS_ATTR_SYMBOL   (pd_class, PROP_PRESET_NAME, 0, t_ebox, b_objpreset_id);
        CLASS_ATTR_DEFAULT  (pd_class, PROP_PRESET_NAME, 0, "(null)");
        CLASS_ATTR_SAVE     (pd_class, PROP_PRESET_NAME, 0);
        CLASS_ATTR_CATEGORY (pd_class, PROP_PRESET_NAME, 0, _("Basic"));
        CLASS_ATTR_LABEL    (pd_class, PROP_PRESET_NAME, 0, _("Preset Name"));
        CLASS_ATTR_ACCESSORS(pd_class, PROP_PRESET_NAME, NULL, ebox_set_presetid);

        // clang-format on
    }

    void useMouseEvents(int events)
    {
        if (events & UI_MOUSE_DOWN)
            eclass_addmethod(pd_class, UI_METHOD_PTR(mouseDown), "mousedown", A_GIMME, 0);

        if (events & UI_MOUSE_UP)
            eclass_addmethod(pd_class, UI_METHOD_PTR(mouseUp), "mouseup", A_GIMME, 0);

        if (events & UI_MOUSE_DRAG)
            eclass_addmethod(pd_class, UI_METHOD_PTR(mouseDrag), "mousedrag", A_GIMME, 0);

        if (events & UI_MOUSE_ENTER)
            eclass_addmethod(pd_class, UI_METHOD_PTR(mouseEnter), "mouseenter", A_GIMME, 0);

        if (events & UI_MOUSE_LEAVE)
            eclass_addmethod(pd_class, UI_METHOD_PTR(mouseLeave), "mouseleave", A_GIMME, 0);

        if (events & UI_MOUSE_MOVE)
            eclass_addmethod(pd_class, UI_METHOD_PTR(mouseMove), "mousemove", A_GIMME, 0);

        if (events & UI_MOUSE_DBL_CLICK)
            eclass_addmethod(pd_class, UI_METHOD_PTR(dblClick), "dblclick", A_GIMME, 0);

        if (events & UI_MOUSE_WHEEL)
            eclass_addmethod(pd_class, UI_METHOD_PTR(mouseWheel), "mousewheel", A_GIMME, 0);
    }

    void useKeys()
    {
        eclass_addmethod(pd_class, UI_METHOD_PTR(key), "key", A_GIMME, 0);
        eclass_addmethod(pd_class, UI_METHOD_PTR(keyFilter), "keyfilter", A_GIMME, 0);
    }

    void useBang()
    {
        eclass_addmethod(pd_class, UI_METHOD_PTR(onBang), "bang", A_GIMME, 0);
    }

    void useFloat()
    {
        eclass_addmethod(pd_class, UI_METHOD_PTR(onFloat), "float", A_FLOAT, 0);
    }

    void useSymbol()
    {
        eclass_addmethod(pd_class, UI_METHOD_PTR(onSymbol), "symbol", A_SYMBOL, 0);
    }

    void useList()
    {
        eclass_addmethod(pd_class, UI_METHOD_PTR(onList), "list", A_GIMME, 0);
    }

    void useAny()
    {
        eclass_addmethod(pd_class, UI_METHOD_PTR(onAny), "anything", A_GIMME, 0);
    }

    void useData()
    {
        eclass_addmethod(pd_class, UI_METHOD_PTR(onData), "list", A_GIMME, 0);
    }

    void addMethod(const char* name, listMethodPtr m)
    {
        addMethod(gensym(name), m);
    }

    void addMethod(t_symbol* name, listMethodPtr m)
    {
        list_map[name] = m;
        eclass_addmethod(pd_class, reinterpret_cast<t_typ_method>(customMethodList), name->s_name, A_GIMME, 0);
    }

    void addMethod(const char* name, floatMethodPtr m)
    {
        addMethod(gensym(name), m);
    }

    void addMethod(t_symbol* name, floatMethodPtr m)
    {
        float_map[name] = m;
        eclass_addmethod(pd_class, reinterpret_cast<t_typ_method>(customMethodFloat), name->s_name, A_GIMME, 0);
    }

    void addMethod(const char* name, bangMethodPtr m)
    {
        addMethod(gensym(name), m);
    }

    void addMethod(t_symbol* name, bangMethodPtr m)
    {
        bang_map[name] = m;
        eclass_addmethod(pd_class, reinterpret_cast<t_typ_method>(customMethodBang), name->s_name, A_GIMME, 0);
    }

    void addProperty(const char* name, const char* label, float def, float UI::*m, const char* category = "Misc")
    {
        char buf[32];
        snprintf(buf, 30, "%g", def);

        eclass_new_attr_typed(pd_class, name, "float", 1, 0, 0, offset(m));
        eclass_attr_label(pd_class, name, 0, label);
        eclass_attr_save(pd_class, name, 0);
        eclass_attr_paint(pd_class, name, 0);
        eclass_attr_default(pd_class, name, 0, buf);
        eclass_attr_style(pd_class, name, 0, "number");
        eclass_attr_category(pd_class, name, 0, category);
    }

    void addProperty(const char* name, const char* label, int def, int UI::*m, const char* category = "Misc")
    {
        char buf[32];
        snprintf(buf, 30, "%d", def);

        eclass_new_attr_typed(pd_class, name, "int", 1, 0, 0, offset(m));
        eclass_attr_label(pd_class, name, 0, label);
        eclass_attr_save(pd_class, name, 0);
        eclass_attr_paint(pd_class, name, 0);
        eclass_attr_default(pd_class, name, 0, buf);
        eclass_attr_style(pd_class, name, 0, "number");
        eclass_attr_category(pd_class, name, 0, category);
    }

    void addProperty(const char* name, const char* label, bool def, int UI::*m, const char* category = "Misc")
    {
        eclass_new_attr_typed(pd_class, name, "int", 1, 0, 0, offset(m));
        eclass_attr_label(pd_class, name, 0, label);
        eclass_attr_save(pd_class, name, 0);
        eclass_attr_paint(pd_class, name, 0);
        eclass_attr_default(pd_class, name, 0, def ? "1" : "0");
        eclass_attr_style(pd_class, name, 0, "onoff");
        eclass_attr_category(pd_class, name, 0, category);
    }

    void addProperty(const char* name, const char* label, const char* def, t_rgba UI::*m)
    {
        eclass_new_attr_typed(pd_class, name, "float", 4, 0, 0, offset(m));
        eclass_attr_label(pd_class, name, 0, label);
        eclass_attr_save(pd_class, name, 0);
        eclass_attr_paint(pd_class, name, 0);
        eclass_attr_default(pd_class, name, 0, def);
        eclass_attr_style(pd_class, name, 0, "color");
        eclass_attr_category(pd_class, name, 0, "Colors");
    }

    void addSymbolProperty(const char* name,
        const char* label,
        const char* def,
        t_symbol* UI::*m,
        const char* category = "Misc")
    {
        eclass_new_attr_typed(pd_class, name, "symbol", 1, 0, 0, offset(m));
        eclass_attr_label(pd_class, name, 0, label);
        eclass_attr_save(pd_class, name, 0);
        eclass_attr_paint(pd_class, name, 0);
        eclass_attr_default(pd_class, name, 0, def);
        eclass_attr_style(pd_class, name, 0, "entry");
        eclass_attr_category(pd_class, name, 0, category);
    }

    void addPathProperty(const char* name,
        const char* label,
        const char* def,
        t_symbol* UI::*m,
        const char* category = "Misc")
    {
        eclass_new_attr_typed(pd_class, name, "symbol", 1, 0, 0, offset(m));
        eclass_attr_label(pd_class, name, 0, label);
        eclass_attr_save(pd_class, name, 0);
        eclass_attr_paint(pd_class, name, 0);
        eclass_attr_default(pd_class, name, 0, def);
        eclass_attr_style(pd_class, name, 0, "path");
        eclass_attr_category(pd_class, name, 0, category);
    }

    void setPropertyMin(const char* name, float v)
    {
        eclass_attr_filter_min(pd_class, name, v);
    }

    void setPropertyMax(const char* name, float v)
    {
        eclass_attr_filter_max(pd_class, name, v);
    }

    void setPropertyLabel(const char* name, const char* label)
    {
        eclass_attr_label(pd_class, name, 0, label);
    }

    void setPropertyRange(const char* name, float min, float max)
    {
        setPropertyMin(name, min);
        setPropertyMax(name, max);
    }

    void setPropertyDefaultValue(const char* name, const char* def)
    {
        eclass_attr_default(pd_class, name, 0, def);
    }

    void setPropertyStep(const char* name, float step)
    {
        eclass_attr_step(pd_class, name, step);
    }

    void hideProperty(const char* name)
    {
        eclass_attr_invisible(pd_class, name, 0);
    }

    void showProperty(const char* name)
    {
        eclass_attr_visible(pd_class, name, 0);
    }

    void setDefaultSize(int w, int h)
    {
        char buf[32];
        snprintf(buf, 30, "%d. %d.", w, h);

        CLASS_ATTR_DEFAULT(pd_class, "size", 0, buf);
    }

    void addProperty(const char* name,
        float (UI::*getter)() const,
        void (UI::*setter)(float))
    {
        eclass_new_attr_typed(pd_class, name, "float", 1, 0, 0, 0);
        eclass_attr_invisible(pd_class, name, 0);
        setPropertyAccessor(name, getter, setter);
    }

    void addProperty(const char* name,
        AtomList (UI::*getter)() const,
        void (UI::*setter)(const AtomList&) = 0)
    {
        eclass_new_attr_typed(pd_class, name, "atom", 1, 0, 0, 0);
        eclass_attr_invisible(pd_class, name, 0);
        setPropertyAccessor(name, getter, setter);
    }

    void addProperty(const char* name, const char* label,
        const char* def, t_symbol* UI::*m,
        const char* items, const char* cat = "Misc")
    {
        eclass_new_attr_typed(pd_class, name, "symbol", 1, 0, 0, offset(m));
        eclass_attr_label(pd_class, name, 0, label);
        eclass_attr_save(pd_class, name, 0);
        eclass_attr_paint(pd_class, name, 0);
        eclass_attr_default(pd_class, name, 0, def);
        eclass_attr_style(pd_class, name, 0, "menu");
        eclass_attr_category(pd_class, name, 0, cat);
        eclass_attr_itemlist(pd_class, name, 0, items);
    }

    void addPropertyIntMenu(const char* name, const char* label,
        const char* def, int UI::*m,
        const char* items, const char* cat = "Misc")
    {
        eclass_new_attr_typed(pd_class, name, "int", 1, 0, 0, offset(m));
        eclass_attr_label(pd_class, name, 0, label);
        eclass_attr_save(pd_class, name, 0);
        eclass_attr_paint(pd_class, name, 0);
        eclass_attr_default(pd_class, name, 0, def);
        eclass_attr_style(pd_class, name, 0, "menu");
        eclass_attr_category(pd_class, name, 0, cat);
        eclass_attr_itemlist(pd_class, name, 0, items);
    }

    void addVirtualProperty(const char* name, const char* label, const char* def,
        AtomList (UI::*getter)() const, void (UI::*setter)(const AtomList&))
    {
        eclass_new_attr_typed(pd_class, name, "symbol", 1, 0, 0, 0);
        eclass_attr_label(pd_class, name, 0, label);
        eclass_attr_save(pd_class, name, 0);
        eclass_attr_paint(pd_class, name, 0);
        eclass_attr_default(pd_class, name, 0, def);
        eclass_attr_accessor(pd_class, name, (t_err_method)listPropGetter, (t_err_method)listPropSetter);
        prop_list_map[gensym(name)] = std::make_pair(getter, setter);
    }

    void setPropertyAccessor(const char* name, float (UI::*getter)() const, void (UI::*setter)(float))
    {
        eclass_attr_accessor(pd_class, name, (t_err_method)floatPropGetter, (t_err_method)floatPropSetter);
        prop_float_map[gensym(name)] = std::make_pair(getter, setter);
    }

    void setPropertyAccessor(const char* name, AtomList (UI::*getter)() const, void (UI::*setter)(const AtomList&))
    {
        eclass_attr_accessor(pd_class, name, (t_err_method)listPropGetter, (t_err_method)listPropSetter);
        prop_list_map[gensym(name)] = std::make_pair(getter, setter);
    }

    void setPropertySave(const char* name, bool value = true)
    {
        eclass_attr_save(pd_class, name, 0, value);
    }

    void setPropertyRedirect(const char* name)
    {
        eclass_attr_redirect(pd_class, name, (t_gotfn)listPropRedirector);
    }

    void addAlias(const char* name)
    {
        class_addcreator(reinterpret_cast<t_newmethod>(alloc), gensym(name), A_GIMME, A_NULL);
    }

public:
    static void paint(UI* z, t_object* view)
    {
        z->paint(view);
    }

    template <class T>
    static size_t offset(T UI::*m)
    {
        static UI ui;

        char* v1 = (char*)static_cast<void*>(&(ui.*m));
        char* v0 = (char*)static_cast<void*>(&ui);
        return v1 - v0;
    }

    static void mouseMove(UI* z, t_object* view, t_pt pt, long modifiers)
    {
        updateMousePos(pt);
        z->onMouseMove(view, pt, modifiers);
    }

    static void mouseDown(UI* z, t_object* view, t_pt pt, t_pt abs_pt, long modifiers)
    {
        updateMousePos(pt);
        z->onMouseDown(view, pt, abs_pt, modifiers);
    }

    static void mouseUp(UI* z, t_object* view, t_pt pt, long modifiers)
    {
        updateMousePos(pt);
        z->onMouseUp(view, pt, modifiers);
    }

    static void mouseDrag(UI* z, t_object* view, t_pt pt, long modifiers)
    {
        updateMousePos(pt);
        z->onMouseDrag(view, pt, modifiers);
    }

    static void mouseLeave(UI* z, t_object* view, t_pt pt, long modifiers)
    {
        // invalidate mouse pointer coord on mouseLeave to prevent mouseWheel handle
        // when mouse is outside of widget
        t_pt pos;
        pos.x = std::numeric_limits<t_float>::max();
        pos.y = pos.x;
        updateMousePos(pos);

        z->onMouseLeave(view, pt, modifiers);
    }

    static void mouseEnter(UI* z, t_object* view, t_pt pt, long modifiers)
    {
        updateMousePos(pt);
        z->onMouseEnter(view, pt, modifiers);
    }

    static void mouseWheel(UI* z, t_object* view, t_pt pt, long modifiers, double delta)
    {
#ifdef __APPLE__
        z->onMouseWheel(view, pt, modifiers, delta);
#else
        z->onMouseWheel(view, mouse_pos_, modifiers, delta);
#endif
    }

    static void updateMousePos(const t_pt& pt)
    {
#ifndef __APPLE__
        mouse_pos_ = pt;
#endif
    }

    static void dblClick(UI* z, t_object* view, t_pt pt, long modifiers)
    {
        z->onDblClick(view, pt, modifiers);
    }

    static void key(UI* z, t_symbol*, int k, long modifiers)
    {
        z->onKey(k, modifiers);
    }

    static void keyFilter(UI* z, t_symbol*, int k, long modifiers)
    {
        z->onKeyFilter(k, modifiers);
    }

    static t_pd_err notify(UI* z, t_symbol* s, t_symbol* msg, void*, void*)
    {
        if (use_presets && msg == s_attr_modified && s == gensym(PROP_PRESET_NAME)) {
            z->handlePresetNameChange();
        }

        return z->notify(s, msg);
    }

    static void okSize(UI* z, ::t_rect* newrect)
    {
        z->okSize(newrect);
    }

    static void onZoom(UI* z, t_float zoom)
    {
        z->onZoom(zoom);
    }

    static void onPopup(UI* z, t_symbol* menu_name, long itemIdx)
    {
        z->onPopup(menu_name, itemIdx);
    }

    static void onBang(UI* z)
    {
        z->onBang();
    }

    static void onFloat(UI* z, t_float f)
    {
        z->onFloat(f);
    }

    static void onSymbol(UI* z, t_symbol* s)
    {
        z->onSymbol(s);
    }

    static void onList(UI* z, t_symbol* s, int argc, t_atom* argv)
    {
        z->onList(AtomList(argc, argv));
    }

    static void onAny(UI* z, t_symbol* s, int argc, t_atom* argv)
    {
        z->onAny(s, AtomList(argc, argv));
    }

    static int checkPresetIndex(UI* z, int argc, t_atom* argv)
    {
        int idx = 0;
        if (argc > 0) {
            if (argv->a_type != A_FLOAT) {
                pd_error(z->asPd(), "[%s] invalid preset index", z->name()->s_name);
                return -1;
            }

            idx = atom_getint(argv);
        }

        return idx;
    }

    static void loadPreset(UI* z, t_symbol*, int argc, t_atom* argv)
    {
        int idx = checkPresetIndex(z, argc, argv);

        if (idx < 0)
            return;

        z->loadPreset(idx);
    }

    static void storePreset(UI* z, t_symbol*, int argc, t_atom* argv)
    {
        int idx = checkPresetIndex(z, argc, argv);

        if (idx < 0)
            return;

        z->storePreset(idx);
    }

    static void clearPreset(UI* z, t_symbol*, int argc, t_atom* argv)
    {
        int idx = checkPresetIndex(z, argc, argv);

        if (idx < 0)
            return;

        z->clearPreset(idx);
    }

    static void customMethodList(UI* z, t_symbol* s, int argc, t_atom* argv)
    {
        typename ListMethodMap::iterator it = list_map.find(s);
        if (it == list_map.end()) {
            pd_error(z->asPdObject(), "[%s] unknown method: %s", z->name()->s_name, s->s_name);
            return;
        }

        listMethodPtr m = it->second;

        if (!m) {
            pd_error(z->asPdObject(), "[%s] NULL function pointer: %s", z->name()->s_name, s->s_name);
            return;
        }

        (z->*m)(AtomList(argc, argv));
    }

    static void customMethodFloat(UI* z, t_symbol* s, int argc, t_atom* argv)
    {
        if (argc < 1)
            return;

        typename FloatMethodMap::iterator it = float_map.find(s);
        if (it == float_map.end()) {
            pd_error(z->asPdObject(), "[%s] unknown method: %s", z->name()->s_name, s->s_name);
            return;
        }

        floatMethodPtr m = it->second;

        if (!m) {
            pd_error(z->asPdObject(), "[%s] NULL function pointer: %s", z->name()->s_name, s->s_name);
            return;
        }

        (z->*m)(atom_getfloat(argv));
    }

    static void customMethodBang(UI* z, t_symbol* s, int, t_atom*)
    {
        typename BangMethodMap::iterator it = bang_map.find(s);
        if (it == bang_map.end()) {
            pd_error(z->asPdObject(), "[%s] unknown method: %s", z->name()->s_name, s->s_name);
            return;
        }

        bangMethodPtr m = it->second;

        if (!m) {
            pd_error(z->asPdObject(), "[%s] NULL function pointer: %s", z->name()->s_name, s->s_name);
            return;
        }

        (z->*m)();
    }

    static void setDrawParams(UI* z, t_object* obj, t_edrawparams* params)
    {
        z->setDrawParams(obj, params);
    }

    static t_pd_err floatPropGetter(UI* z, t_eattr* attr, int* argc, t_atom** argv)
    {
        typename FloatPropertyMap::iterator it = prop_float_map.find(attr->name);
        if (it == prop_float_map.end())
            return 1;

        propFloatGet m = it->second.first;

        if (m == 0) {
            pd_error(z->asPdObject(), "[%s] non-readable property: @%s", z->name()->s_name, attr->name->s_name);
            argc = 0;
            *argv = 0;
            return 1;
        }

        *argc = 1;
        *argv = (t_atom*)getbytes(sizeof(t_atom));
        atom_setfloat(*argv, (z->*m)());
        return 0;
    }

    static t_pd_err floatPropSetter(UI* z, t_eattr* attr, int argc, t_atom* argv)
    {
        typename FloatPropertyMap::iterator it = prop_float_map.find(attr->name);
        if (it == prop_float_map.end())
            return 1;

        if (argc < 1)
            return 2;

        propFloatSet m = it->second.second;

        if (m == 0) {
            pd_error(z->asPdObject(), "[%s] readonly property: @%s", z->name()->s_name, attr->name->s_name);
            return 1;
        }

        (z->*m)(atom_getfloat(argv));
        return 0;
    }

    static t_pd_err listPropGetter(UI* z, t_eattr* attr, int* argc, t_atom** argv)
    {
        typename ListPropertyMap::iterator it = prop_list_map.find(attr->name);
        if (it == prop_list_map.end())
            return 1;

        propListGet m = it->second.first;

        if (m == 0) {
            pd_error(z->asPdObject(), "[%s] non-readable property: @%s", z->name()->s_name, attr->name->s_name);
            argc = 0;
            *argv = 0;
            return 1;
        }

        AtomList res = (z->*m)();

        *argc = res.size();
        *argv = (t_atom*)copybytes(res.toPdData(), sizeof(t_atom) * res.size());
        return 0;
    }

    static t_pd_err listPropSetter(UI* z, t_eattr* attr, int argc, t_atom* argv)
    {
        typename ListPropertyMap::iterator it = prop_list_map.find(attr->name);
        if (it == prop_list_map.end())
            return 1;

        propListSet m = it->second.second;

        if (m == 0) {
            pd_error(z->asPdObject(), "[%s] readonly property: @%s", z->name()->s_name, attr->name->s_name);
            return 1;
        }

        (z->*m)(AtomList(argc, argv));
        return 0;
    }

    static void onData(UI* z, t_symbol*, int argc, t_atom* argv)
    {
        AtomList l(argc, argv);
        if (l.size() == 1 && l[0].isData()) {
            DataPtr ptr(l[0]);
            if (ptr.isValid()) {
                z->onData(ptr);
            } else {
                DataDesc desc = l[0].getData();
                LIB_ERR << "can't get data with type=" << desc.type << " and id=" << desc.id;
            }
        } else {
            z->onList(l);
        }
    }

    static void listPropRedirector(UI* z, t_symbol* s, int argc, t_atom* argv)
    {
        z->onProperty(s, AtomList(argc, argv));
    }

public:
    static t_eclass* pd_class;
    static bool use_presets;
    static long flags;
    static BangMethodMap bang_map;
    static FloatMethodMap float_map;
    static ListMethodMap list_map;
    static FloatPropertyMap prop_float_map;
    static ListPropertyMap prop_list_map;

    // trick to get valid mouse pointer coordinates on MouseWheel event on Linux and Windows
#ifndef __APPLE__
    static t_pt mouse_pos_;
#endif
};

template <class UI>
t_eclass* UIObjectFactory<UI>::pd_class = 0;

template <class UI>
bool UIObjectFactory<UI>::use_presets = false;

template <class UI>
long UIObjectFactory<UI>::flags = 0;

#ifndef __APPLE__
template <class UI>
t_pt UIObjectFactory<UI>::mouse_pos_;
#endif

template <class UI>
typename UIObjectFactory<UI>::BangMethodMap UIObjectFactory<UI>::bang_map;

template <class UI>
typename UIObjectFactory<UI>::FloatMethodMap UIObjectFactory<UI>::float_map;

template <class UI>
typename UIObjectFactory<UI>::ListMethodMap UIObjectFactory<UI>::list_map;

template <class UI>
typename UIObjectFactory<UI>::FloatPropertyMap UIObjectFactory<UI>::prop_float_map;

template <class UI>
typename UIObjectFactory<UI>::ListPropertyMap UIObjectFactory<UI>::prop_list_map;
}

#endif // CEAMMC_NEW_GUI_H
