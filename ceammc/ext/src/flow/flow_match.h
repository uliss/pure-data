/*****************************************************************************
 * Copyright 2019 Serge Poltavsky. All rights reserved.
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
#ifndef FLOW_MATCH_H
#define FLOW_MATCH_H

#include "ceammc_data.h"
#include "ceammc_object.h"

#include <memory>

namespace re2 {
class RE2;
}

using namespace ceammc;

class FlowMatch : public BaseObject {
    using RE2ptr = std::unique_ptr<re2::RE2>;
    using RE2list = std::vector<RE2ptr>;
    ListProperty* patterns_;
    RE2list re_;
    BoolProperty* cut_;

public:
    FlowMatch(const PdArgs& args);
    void initDone() override;
    void onInlet(size_t idx, const AtomList& l) override;

    void onSymbol(t_symbol* s) override;
    void onAny(t_symbol* s, const AtomList& l) override;
    void onDataT(const StringAtom& data);
};

void setup_flow_match();

#endif // FLOW_MATCH_H
