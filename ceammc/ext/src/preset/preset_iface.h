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
#ifndef PRESET_IFACE_H
#define PRESET_IFACE_H

#include "../data/data_protocol.h"
#include "ceammc_factory.h"

namespace ceammc {

template <typename T>
class PresetIFaceFactory : public ObjectFactory<T> {
public:
    PresetIFaceFactory(const char* name, int flags = OBJECT_FACTORY_DEFAULT)
        : ObjectFactory<T>(name, flags)
    {
        protocol::Storage<ObjectFactory, T> obj(*this);
    }
};

}

#endif // PRESET_IFACE_H