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
#ifndef LIST_CONTAINSX_H
#define LIST_CONTAINSX_H

#include "../data/datatype_mlist.h"
#include "ceammc_dataatomlist.h"
#include "ceammc_object.h"

using namespace ceammc;

class ListXContains : public BaseObject {
    DataAtomList lst_;

public:
    ListXContains(const PdArgs& args);

    void onFloat(t_float f) override;
    void onSymbol(t_symbol* s) override;
    void onList(const AtomList& lst) override;
    void onData(const DataPtr& ptr) override;

    void onInlet(size_t n, const AtomList& lst) override;

private:
    void output(bool v);
    template <typename T>
    void contains(const T& v);
};

template <typename T>
void ListXContains::contains(const T& v)
{
    auto mlist = lst_.asSingle<DataTypeMList>();
    if (mlist)
        output(mlist->contains(v));
    else
        output(lst_.contains(v));
}

void setup_list_xcontains();

#endif // LIST_CONTAINS_H