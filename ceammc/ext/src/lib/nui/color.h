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
#ifndef CEAMMC_NUI_COLOR_H
#define CEAMMC_NUI_COLOR_H

#include <cstdint>

namespace ceammc {
namespace ui {
    using HexColor = uint32_t;

    static inline uint8_t color_red(HexColor c)
    {
        return (c >> 16) & 0xFF;
    }

    static inline uint8_t color_green(HexColor c)
    {
        return (c >> 8) & 0xFF;
    }

    static inline uint8_t color_blue(HexColor c)
    {
        return c & 0xFF;
    }

    namespace colors {
        static inline HexColor make_rgb(uint8_t r, uint8_t g, uint8_t b, uint8_t opacity = 0x00)
        {
            return (opacity << 24) | (r << 16) | (g << 8) | b;
        }

        constexpr HexColor white = 0x00FFFFFF;
        constexpr HexColor black = 0x00000000;
        constexpr HexColor dark = 0x00222222;
        constexpr HexColor alpha_mask = 0xFF000000;
        constexpr HexColor rbg_mask = 0x00FFFFFF;
        constexpr HexColor red = 0xFF0000;
        constexpr HexColor green = 0x00FF00;
        constexpr HexColor blue = 0x0000FF;

        constexpr HexColor st_border = 0x00222222;
        constexpr HexColor st_fill = 0x00FAFAFA;
        constexpr HexColor st_active = 0x00FA00FA;
        constexpr HexColor st_text = 0x00000000;
        constexpr HexColor st_xlet_ctl = 0x00000000;
        constexpr HexColor st_xlet_sig = 0x002200AA;
    }
}
}

#endif // CEAMMC_NUI_COLOR_H
