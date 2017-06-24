/*****************************************************************************
 * Copyright 2017 Serge Poltavsky. All rights reserved.
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
#ifndef LIST_AT_H
#define LIST_AT_H

#include "ceammc_object.h"

using namespace ceammc;

class ListAt : public BaseObject {
    ListProperty* pos_;
    SymbolEnumProperty* at_method_;

public:
    ListAt(const PdArgs& a);
    void onInlet(size_t idx, const AtomList& l);
    void onList(const AtomList& l);

private:
    const Atom* at(const AtomList& l, const Atom& p);
};

#endif // LIST_AT_H
