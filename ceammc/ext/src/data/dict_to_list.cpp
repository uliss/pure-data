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
#include "dict_to_list.h"
#include "ceammc_factory.h"

DictToList::DictToList(const PdArgs& args)
    : BaseObject(args)
{
    createOutlet();
}

void DictToList::onDataT(const DataTypeDict& d)
{
    AtomList res;

    auto& dict = d.innerData();
    for (auto& kv : dict) {
        res.append(kv.first);

        auto& v = kv.second;
        if (v.type() == typeid(Atom))
            res.append(boost::get<Atom>(v));
        else if (v.type() == typeid(AtomList))
            res.append(boost::get<AtomList>(v));
        else if (v.type() == typeid(DataAtom))
            res.append(boost::get<DataAtom>(v).toAtom());
    }

    listTo(0, res);
}

void setup_dict_to_list()
{
    ObjectFactory<DictToList> obj("dict.to_list");
    obj.addAlias("dict->list");
    obj.processData<DataTypeDict>();
}