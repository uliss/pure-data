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
#ifndef TEST_WRAPPERS_H
#define TEST_WRAPPERS_H

#include "ceammc_atomlist.h"
#include "ceammc_data.h"
#include "ceammc_dataatomlist.h"

using namespace ceammc;

// clang-format off

/**
 * Atoms wraps
 */
Atom test_atom_wrap(const char* v);
Atom test_atom_wrap(t_symbol* v) ;
Atom test_atom_wrap(float v);
Atom test_atom_wrap(const Atom& v);
Atom test_atom_wrap(const DataPtr& d);
// clang-format on

Atom D(DataType t, DataId id);

#endif // TEST_WRAPPERS_H