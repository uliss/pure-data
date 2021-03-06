// this is autogenerated file, do not edit!
#ifndef LABEL_H_
#define LABEL_H_
// clang-format off

#include "nui/model.h"
#include "nui/style.h"
#include "m_pd.h"

#include <tuple>

namespace ceammc {
namespace ui {

class LabelData
    : public std::tuple<std::string, t_symbol*, Size, int, HexColor, Font, AnchorPosition, TextAlign, int> {
public:
    enum Fields {
        TEXT,
        TOOLTIP,
        SIZE,
        TEXT_WIDTH,
        COLOR,
        FONT,
        ANCHOR,
        ALIGN,
        STYLE_IDX,
    };
public:
    LabelData()
        : std::tuple<std::string, t_symbol*, Size, int, HexColor, Font, AnchorPosition, TextAlign, int>(std::string(), &s_, Size(40, 10), 0, colors::st_text, Font(), ANCHOR_CORNER_LEFT_TOP, TEXT_ALIGN_LEFT, 0) { }

    LabelData(int style)
        : LabelData() {
        setStyle(style);
        loadStyle(style);
    }


    // getters
    std::string const& text() const noexcept { return std::get<TEXT>(*this); }
    t_symbol* const& tooltip() const noexcept { return std::get<TOOLTIP>(*this); }
    Size const& size() const noexcept { return std::get<SIZE>(*this); }
    int const& textWidth() const noexcept { return std::get<TEXT_WIDTH>(*this); }
    HexColor const& color() const noexcept { return std::get<COLOR>(*this); }
    Font const& font() const noexcept { return std::get<FONT>(*this); }
    AnchorPosition const& anchor() const noexcept { return std::get<ANCHOR>(*this); }
    TextAlign const& align() const noexcept { return std::get<ALIGN>(*this); }
    int const& style() const noexcept { return std::get<STYLE_IDX>(*this); }

    // setters
    void setText(std::string v) { std::get<TEXT>(*this) = v; }
    void setTooltip(t_symbol* v) { std::get<TOOLTIP>(*this) = v; }
    void setSize(Size v) { std::get<SIZE>(*this) = v; }
    void setTextWidth(int v) { std::get<TEXT_WIDTH>(*this) = v; }
    void setColor(HexColor v) { std::get<COLOR>(*this) = v; }
    void setFont(Font v) { std::get<FONT>(*this) = v; }
    void setAnchor(AnchorPosition v) { std::get<ANCHOR>(*this) = v; }
    void setAlign(TextAlign v) { std::get<ALIGN>(*this) = v; }
    void setStyle(int v) { std::get<STYLE_IDX>(*this) = v; }

    // refs
    std::string& textRef() { return std::get<TEXT>(*this); }
    t_symbol*& tooltipRef() { return std::get<TOOLTIP>(*this); }
    Size& sizeRef() { return std::get<SIZE>(*this); }
    int& textWidthRef() { return std::get<TEXT_WIDTH>(*this); }
    HexColor& colorRef() { return std::get<COLOR>(*this); }
    Font& fontRef() { return std::get<FONT>(*this); }
    AnchorPosition& anchorRef() { return std::get<ANCHOR>(*this); }
    TextAlign& alignRef() { return std::get<ALIGN>(*this); }
    int& styleRef() { return std::get<STYLE_IDX>(*this); }

    // style
    void loadStyle(int st) {
        using sc = StyleCollection;
        setSize(sc::size(st, "label:size"_hash, Size(40, 10)));
        setColor(sc::color(st, "label:color"_hash, colors::st_text));
        setFont(sc::font(st, "label:font"_hash, Font()));
    }
};

using LabelModel = ModelBase<LabelData>;

}
}

// clang-format on
#endif
