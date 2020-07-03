/*****************************************************************************
 * Copyright 2020 Serge Poltavsky. All rights reserved.
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
#ifndef IS_FILE_H
#define IS_FILE_H

#include "ceammc_data.h"
#include "ceammc_object.h"

using namespace ceammc;

class IsFile : public BaseObject {
public:
    IsFile(const PdArgs& a);
    void onSymbol(t_symbol* s) final;
    void onDataT(const StringAtom& str);

private:
    bool fileExists(const std::string& p) const;
};

void setup_is_file();

#endif // IS_FILE_H
