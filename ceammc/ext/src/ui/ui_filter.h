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

#include "ui_filter_t.h"

using namespace ceammc;

class UIFilter : public ui::TFilter<UIObject> {
public:
    UIFilter();

    const char* annotateOutlet(int n) const
    {
        return "list: biquad coefficients - b0 b1 b2 a1 a2";
    }
};

void setup_ui_filter();

#endif // UI_FILTER_H
