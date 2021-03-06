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
#ifndef SYSTEM_EXIT_H
#define SYSTEM_EXIT_H

#include "ceammc_clock.h"
#include "ceammc_object.h"
using namespace ceammc;

class SystemExit : public BaseObject {
    ClockLambdaFunction clock_;
    FloatProperty* delay_;
    IntProperty* rc_;
    BoolProperty* auto_;

public:
    SystemExit(const PdArgs& args);
    void initDone() override;
    void m_exit(t_symbol* s, const AtomListView& lv);

private:
    void exit(int rc);
};

void setup_system_exit();

#endif // SYSTEM_EXIT_H
