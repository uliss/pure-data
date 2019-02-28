/*****************************************************************************
 * Copyright 2018 Serge Poltavsky. All rights reserved.
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
#ifndef DICT_PASS_H
#define DICT_PASS_H

#include "ceammc_object.h"
#include "datatype_dict.h"

using namespace ceammc;

class DictPass : public BaseObject {
    AtomList keys_;

public:
    DictPass(const PdArgs& args);

    void parseProperties() override;
    void onInlet(size_t, const AtomList&) override;

    void onDataT(const DataTypeDict& dict);
};

void setup_dict_pass();

#endif // DICT_PASS_H