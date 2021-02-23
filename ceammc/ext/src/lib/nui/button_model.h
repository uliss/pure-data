// this is autogenerated file, do not edit!
#ifndef BUTTON_H_
#define BUTTON_H_
// clang-format off

#include "nui/model.h"
#include "nui/style.h"
#include "m_pd.h"

#include <tuple>

namespace ceammc {
namespace ui {

class ButtonData
    : public std::tuple<Size, HexColor, HexColor, HexColor, bool, int> {
public:
    enum Fields {
        SIZE,
        BORDER_COLOR,
        FILL_COLOR,
        KNOB_COLOR,
        STATE,
        STYLE_IDX,
    };
public:
    ButtonData()
        : std::tuple<Size, HexColor, HexColor, HexColor, bool, int>(Size(15, 15), colors::st_border, colors::st_fill, colors::st_active, false, 0) { }

    ButtonData(int style)
        : ButtonData() {
        setStyle(style);
        loadStyle(style);
    }


    // getters
    Size const& size() const noexcept { return std::get<SIZE>(*this); }
    HexColor const& borderColor() const noexcept { return std::get<BORDER_COLOR>(*this); }
    HexColor const& fillColor() const noexcept { return std::get<FILL_COLOR>(*this); }
    HexColor const& knobColor() const noexcept { return std::get<KNOB_COLOR>(*this); }
    bool const& state() const noexcept { return std::get<STATE>(*this); }
    int const& style() const noexcept { return std::get<STYLE_IDX>(*this); }

    // setters
    void setSize(Size v) { std::get<SIZE>(*this) = v; }
    void setBorderColor(HexColor v) { std::get<BORDER_COLOR>(*this) = v; }
    void setFillColor(HexColor v) { std::get<FILL_COLOR>(*this) = v; }
    void setKnobColor(HexColor v) { std::get<KNOB_COLOR>(*this) = v; }
    void setState(bool v) { std::get<STATE>(*this) = v; }
    void setStyle(int v) { std::get<STYLE_IDX>(*this) = v; }

    // refs
    Size& sizeRef() { return std::get<SIZE>(*this); }
    HexColor& borderColorRef() { return std::get<BORDER_COLOR>(*this); }
    HexColor& fillColorRef() { return std::get<FILL_COLOR>(*this); }
    HexColor& knobColorRef() { return std::get<KNOB_COLOR>(*this); }
    bool& stateRef() { return std::get<STATE>(*this); }
    int& styleRef() { return std::get<STYLE_IDX>(*this); }

    // style
    void loadStyle(int st) {
        using sc = StyleCollection;
        setSize(sc::size(st, "button:size"_hash, Size(15, 15)));
        setBorderColor(sc::color(st, "button:border_color"_hash, colors::st_border));
        setFillColor(sc::color(st, "button:fill_color"_hash, colors::st_fill));
        setKnobColor(sc::color(st, "button:knob_color"_hash, colors::st_active));
    }
};

using ButtonModel = ModelBase<ButtonData>;

}
}

// clang-format on
#endif