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
#include "list_prepend.h"
#include "datatype_mlist.h"
#include "ceammc_factory.h"

ListPrepend::ListPrepend(const PdArgs& args)
    : BaseObject(args)
    , lst_(args.args)
{
    createInlet();
    createOutlet();
}

void ListPrepend::parseProperties()
{
    // empty
}

void ListPrepend::onBang()
{
    // bang processed as empty list
    listTo(0, lst_.toList());
}

void ListPrepend::onFloat(t_float f)
{
    onList(AtomList(f));
}

void ListPrepend::onSymbol(t_symbol* s)
{
    onList(AtomList(s));
}

void ListPrepend::onList(const AtomList& lst)
{
    AtomList res(lst_.toList());
    res.reserve(lst.size() + lst_.size());
    res.append(lst);
    listTo(0, res);
}

void ListPrepend::onData(const DataPtr& d)
{
    if (d.isValid() && d->type() == DataTypeMList::dataType) {
        auto lst = d->as<DataTypeMList>();
        if (!lst) {
            OBJ_ERR << "invalid data pointer: " << d.data();
            return;
        }

        auto res = new DataTypeMList(*lst);
        DataPtr dptr(res);

        res->prepend(lst_);
        dataTo(0, dptr);
    } else
        onList(AtomList(d.asAtom()));
}

void ListPrepend::onInlet(size_t n, const AtomList& lst)
{
    lst_.set(lst);
}

void setup_list_prepend()
{
    ObjectFactory<ListPrepend> obj("list.prepend");
    obj.processData();
}
