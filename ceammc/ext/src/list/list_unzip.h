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
#ifndef LIST_UNZIP_H
#define LIST_UNZIP_H

#include "ceammc_object.h"

using namespace ceammc;

class DataTypeMList;

class ListUnzip : public BaseObject {
    const size_t out_count_;
    AtomList in_list_;
    std::vector<AtomList> out_lists_;
    Atom pad_;
    SymbolEnumProperty* method_;

public:
    ListUnzip(const PdArgs& a);
    void onBang() override;
    void onList(const AtomList& l) override;
    void onDataT(const DataTypeMList& lst);

private:
    void clearOutputList();
    void initOutlets();
    void initProperties();

    AtomList getPadValue() const;
    void setPadValue(const AtomList& l);
};

void setup_list_unzip();

#endif // LIST_UNZIP_H
