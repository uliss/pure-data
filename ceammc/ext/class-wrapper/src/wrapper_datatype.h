/*
 * The MIT License (MIT)
 *
 * Copyright (C) 2018-2019 Alex Nadzharov, Serge Poltavsky
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

// template class to wrap class into AbstractData
#ifndef WRAPPER_DATATYPE_H
#define WRAPPER_DATATYPE_H

#include "ceammc_abstractdata.h"
#include "ceammc_data.h"
#include "ceammc_datastorage.h"
#include "ceammc_log.h"

#include <algorithm>
#include <memory>
#include <string>
#include <type_traits>

using namespace ceammc;

namespace wrapper {

template <typename T>
class AbstractDataWrapper : public AbstractData {
    T value_;

public:
    AbstractDataWrapper() = default;
    explicit AbstractDataWrapper(const T& v);

    /**
     * Copy ctor
     */
    AbstractDataWrapper(const AbstractDataWrapper& v);

    /**
     * Move ctor
     */
    AbstractDataWrapper(AbstractDataWrapper&& v) noexcept;

    /**
     * Copy assign
     */
    AbstractDataWrapper& operator=(const AbstractDataWrapper& v);

    /**
     * Move assign
     */
    AbstractDataWrapper& operator=(AbstractDataWrapper&& v);

    /**
     * Polymorphic clone function
     */
    AbstractDataWrapper* clone() const final;

    /**
     * Polymorphic equality check
     */
    bool isEqual(const AbstractData* d) const noexcept final;

    /**
     * Reference to wrapped value
     */
    const T& value() const noexcept { return value_; }
    T& value() noexcept { return value_; }

    /**
     * Data type
     */
    int type() const noexcept final { return AbstractDataWrapper<T>::dataType; }

    /**
     * Polymorphic convertion to string
     */
    std::string toString() const final { return value_.toString(); }

    /**
     * Polymorphic convertsion to json string
     */
    std::string valueToJsonString() const final { return value_.toJsonString(); }

public:
    static const int dataType;
};

template <typename T>
AbstractDataWrapper<T>::AbstractDataWrapper(const T& v)
    : value_(v)
{
}

template <typename T>
AbstractDataWrapper<T>::AbstractDataWrapper(const AbstractDataWrapper& v)
    : value_(v.value_)
{
}

template <typename T>
bool AbstractDataWrapper<T>::isEqual(const AbstractData* d) const noexcept
{
    if (d->type() != type())
        return false;

    auto* dw = static_cast<const AbstractDataWrapper*>(d);
    return value_ == dw->value_;
}

template <typename T>
AbstractDataWrapper<T>* AbstractDataWrapper<T>::clone() const
{
    return new AbstractDataWrapper(value_);
}

template <typename T>
AbstractDataWrapper<T>::AbstractDataWrapper(AbstractDataWrapper&& v) noexcept
    : value_(std::move(v.value()))
{
}

template <typename T>
AbstractDataWrapper<T>& AbstractDataWrapper<T>::operator=(const AbstractDataWrapper& v)
{
    if (&v == this)
        return *this;

    value_ = v.value_;
    return (*this);
}

template <typename T>
AbstractDataWrapper<T>& AbstractDataWrapper<T>::operator=(AbstractDataWrapper&& v)
{
    if (&v == this)
        return *this;

    value_ = std::move(v.value_);
    return (*this);
}

template <typename T>
const int AbstractDataWrapper<T>::dataType = ceammc::DataStorage::instance().registerNewType(
    T::typeName(),
    [](const AtomList& lst) -> Atom {
        T data;
        auto st = data.setFromPd(lst);
        std::string err;
        if (st.error(&err)) {
            LIB_ERR << err;
            return Atom();
        } else {
            return new AbstractDataWrapper(data);
        }
    });

}

#endif // WRAPPER_DATATYPE_H
