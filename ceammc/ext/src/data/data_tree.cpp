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
#include "data_tree.h"
#include "ceammc_datatypes.h"
#include "ceammc_factory.h"
#include "ceammc_format.h"
#include "ceammc_log.h"

#include <array>
#include <tuple>

DataTree::DataTree(const PdArgs& args)
    : CollectionIFace<BaseObject>(args)
    , tree_(nullptr)
{
    createOutlet();

    auto str = to_string(args.args, " ");
    if (!str.empty())
        tree_ = DataTypeTree::newFromString(str);
    else
        tree_ = DataTypeTree::newEmpty();
}

void DataTree::proto_add(const AtomList& lst)
{
    if (tree_->isArray() || tree_->isNull()) {
        auto p = tree_->cloneT<DataTypeTree>();
        TreePtr j(p);

        if (lst.isFloat()) {
            auto f = atomlistToValue<t_float>(lst, 0);
            if (!p->arrayAdd(f))
                OBJ_ERR << "can't add float to json: " << f;
            else
                tree_ = j;
        } else if (lst.isSymbol()) {
            auto s = atomlistToValue<t_symbol*>(lst, &s_);
            if (!p->arrayAdd(s))
                OBJ_ERR << "can't add symbol to json: " << s;
            else
                tree_ = j;
        } else if (lst.isList() && lst.allOf(isFloat)) {
            if (!p->arrayAdd(lst))
                OBJ_ERR << "can't add list to json: " << lst;
            else
                tree_ = j;
        } else if (lst.isDataType(data::DATA_TREE)) {
            TreePtr ptr(lst[0]);
            if (ptr.isNull()) {
                OBJ_ERR << "invalid json data: " << lst;
                return;
            }

            if (ptr->isNull())
                return;

            if (!p->addTree(*ptr))
                OBJ_ERR << "can't add json to json: " << lst;
            else
                tree_ = j;
        } else {
            if (!p->addTree(DataTypeTree::fromString(to_string(lst, " "))))
                OBJ_ERR << "can't add json to json: " << lst;
            else
                tree_ = j;
        }
    }
}

bool DataTree::proto_remove(const AtomList& lst)
{
}

void DataTree::proto_set(const AtomList& lst)
{
    if (lst.isFloat())
        setFromFloat(atomlistToValue<t_float>(lst, 0));
    else if (lst.isSymbol())
        setFromSymbol(atomlistToValue<t_symbol*>(lst, &s_));
    else if (lst.isDataType(data::DATA_TREE))
        tree_ = TreePtr(lst[0]);
    else if (lst.isDataType(data::DATA_STRING)) {
        DataTPtr<DataTypeString> str_ptr(lst[0]);
        tree_ = TreePtr(new DataTypeTree(str_ptr->str()));
    } else if (lst.allOf(isFloat))
        tree_ = TreePtr(new DataTypeTree(lst.asFloats()));
    else
        tree_ = DataTypeTree::fromString(to_string(lst, " "));
}

void DataTree::proto_clear()
{
    if (!tree_->isNull())
        tree_ = TreePtr(new DataTypeTree);
}

size_t DataTree::proto_size() const
{
    return tree_->size();
}

void DataTree::onBang()
{
    dataTo(0, tree_);
}

void DataTree::onFloat(t_float f)
{
    setFromFloat(f);
    onBang();
}

void DataTree::onSymbol(t_symbol* s)
{
    setFromSymbol(s);
    onBang();
}

void DataTree::onList(const AtomList& lst)
{
    proto_set(lst);
    onBang();
}

void DataTree::dump() const
{
    CollectionIFace<BaseObject>::dump();
    OBJ_DBG << tree_->toString();
}

void DataTree::onDataT(const DataTPtr<DataTypeTree>& ptr)
{
    tree_ = ptr;
    onBang();
}

void DataTree::onDataT(const DataTPtr<DataTypeString>& ptr)
{
    tree_ = TreePtr(new DataTypeTree(ptr->str()));
    onBang();
}

void DataTree::onDataT(const DataTPtr<DataTypeSet>& ptr)
{
    auto* p = new DataTypeTree;
    tree_ = TreePtr(p);
    for (auto& a : ptr->toList()) {
        if (a.isFloat())
            p->arrayAdd(a.asFloat());
        else if (a.isSymbol())
            p->arrayAdd(a.asSymbol());
    }
}

void DataTree::onDataT(const DataTPtr<DataTypeDict>& ptr)
{
    auto* p = new DataTypeTree;
    tree_ = TreePtr(p);
    for (auto& a : ptr->innerData()) {
        auto& k = a.first;
        const DictValue& v = a.second;

        if (v.type() == typeid(Atom)) {
            auto a = boost::get<Atom>(v);
            if (a.isFloat())
                p->insertFloat(k.asSymbol()->s_name, a.asFloat());
            else if (a.isSymbol())
                p->insertSymbol(k.asSymbol()->s_name, a.asSymbol());
        }
    }
}

void DataTree::m_find(t_symbol* s, const AtomList& l)
{
    dataTo(0, tree_->match(to_string(l).c_str()));
}

void DataTree::m_at(t_symbol* s, const AtomList& l)
{
    if (l.isFloat()) {
        auto idx = atomlistToValue<int>(l, 0);
        if (idx < 0 || idx >= tree_->size()) {
            METHOD_ERR(s) << "invalid index: " << idx;
            return;
        }

        dataTo(0, tree_->at(idx).asDataPtr());
    } else if (l.isSymbol()) {
        auto idx = atomlistToValue<t_symbol*>(l, &s_);
        dataTo(0, tree_->at(idx).asDataPtr());
    } else
        METHOD_ERR(s) << "integer index or symbol key is expected: " << l;
}

void DataTree::m_key(t_symbol* s, const AtomList& l)
{
    //        dataTo(0, json_->key());
}

void DataTree::m_insert(t_symbol* s, const AtomList& lst)
{
    DataTypeTree* p = tree_->cloneT<DataTypeTree>();
    TreePtr j(p);

    if (lst.size() < 1 || !lst[0].isSymbol()) {
        METHOD_ERR(s) << "usage: " << s->s_name << " KEY [VALUES]";
        return;
    }

    const char* key = lst[0].asSymbol()->s_name;

    if (lst.size() < 2) {

    } else {
        if (lst[1].isFloat()) {
            auto f = lst[1].asFloat();
            if (!p->insertFloat(key, f))
                OBJ_ERR << "can't insert float to json: " << key << " " << f;
            else
                tree_ = j;
        } else if (lst[1].isSymbol()) {
            auto s = lst[1].asSymbol();
            if (!p->insertSymbol(key, s))
                OBJ_ERR << "can't insert symbol to json: " << key << " " << s;
            else
                tree_ = j;
        } /*else if (lst.isList() && lst.allOf(isFloat)) {
        if (!p->insert(lst))
            OBJ_ERR << "can't add list to json: " << lst;
        else
            json_ = j;
    }*/
    }
}

void DataTree::setFromSymbol(t_symbol* s)
{
    tree_ = TreePtr(new DataTypeTree(s));
}

void DataTree::setFromFloat(t_float f)
{
    tree_ = TreePtr(new DataTypeTree(f));
}

class TreeFactory : public ColectionIFaceFactory<DataTree> {
    typedef std::tuple<DataTypeSet, DataTypeString, DataTypeDict, DataTypeTree> TypeList;

public:
    TreeFactory(const char* name, int flags = OBJECT_FACTORY_DEFAULT)
        : ColectionIFaceFactory<DataTree>(name, flags)
    {
        setListFn(processDataTyped);
    }

    template <typename T>
    static bool processSingleData(ObjectProxy* x, const Atom& a)
    {
        DataTPtr<T> ptr(a);
        if (ptr.isValid()) {
            x->impl->onDataT(ptr);
            return true;
        } else
            return false;
    }

    template <int index>
    struct iterate_pred {
        static bool next(ObjectProxy* x, const Atom& a)
        {
            using T = typename std::tuple_element<index - 1, TypeList>::type;
            if (iterate_pred<index - 1>::next(x, a))
                return true;
            else
                return processSingleData<T>(x, a);
        }
    };

    static void processDataTyped(ObjectProxy* x, t_symbol*, int argc, t_atom* argv)
    {
        if (argc == 1 && Atom(*argv).isData()) {
            if (!iterate_pred<std::tuple_size<TypeList>::value>::next(x, Atom(*argv))) {
                DataPtr dptr(*argv);
                LIB_ERR << "unsupported data with type=" << dptr.desc().type;
            }
        } else {
            x->impl->onList(AtomList(argc, argv));
        }
    }
};

template <>
bool TreeFactory::iterate_pred<0>::next(ObjectFactory::ObjectProxy* x, const Atom& a)
{
    using T = typename std::tuple_element<0, TypeList>::type;
    if (processSingleData<T>(x, a))
        return true;

    return false;
}

void setup_data_tree()
{
    TreeFactory obj("data.tree");
    obj.addMethod("at", &DataTree::m_at);
    obj.addMethod("find", &DataTree::m_find);
    obj.addMethod("insert", &DataTree::m_insert);
}
