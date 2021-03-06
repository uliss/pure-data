/*****************************************************************************
 * Copyright 2017 Serge Poltavsky. All rights reserved.
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
#include "datatype_string.h"
#include "ceammc_atomlist.h"
#include "ceammc_datastorage.h"
#include "ceammc_format.h"
#include "ceammc_log.h"
#include "ceammc_string.h"

#include <algorithm>
#include <iostream>

namespace ceammc {

#define NDEBUG 1

static Atom newString(const AtomList& l)
{
    return new DataTypeString(l);
}

const int DataTypeString::dataType = DataStorage::instance().registerNewType("String", newString);

DataTypeString::DataTypeString(t_symbol* s)
    : str_(s->s_name)
{
#ifndef NDEBUG
    LIB_DBG << "string created: " << str_;
#endif
}

DataTypeString::DataTypeString(const Atom& a)
    : str_(to_string(a))
{
#ifndef NDEBUG
    LIB_DBG << "string created: " << str_;
#endif
}

DataTypeString::DataTypeString(const AtomList& l)
    : str_(to_string(l, " "))
{
#ifndef NDEBUG
    LIB_DBG << "string created: " << str_;
#endif
}

DataTypeString::DataTypeString(const char* str)
    : str_(str)
{
#ifndef NDEBUG
    LIB_DBG << "string created: " << str_;
#endif
}

DataTypeString::DataTypeString(const std::string& str)
    : str_(str)
{
#ifndef NDEBUG
    LIB_DBG << "string created: " << str_;
#endif
}

DataTypeString::DataTypeString(const DataTypeString& d)
    : str_(d.str_)
{
}

DataTypeString::DataTypeString(DataTypeString&& d) noexcept
    : str_(std::move(d.str_))
{
}

DataTypeString& DataTypeString::operator=(const DataTypeString& s)
{
    if (&s != this)
        str_ = s.str_;

    return *this;
}

DataTypeString& DataTypeString::operator=(DataTypeString&& s)
{
    if (&s != this)
        str_ = std::move(s.str_);

    return *this;
}

DataTypeString::~DataTypeString() noexcept
{
#ifndef NDEBUG
    LIB_DBG << "string destructed: " << str_;
#endif
}

void DataTypeString::clear() noexcept
{
    str_.clear();
}

int DataTypeString::type() const noexcept
{
    return dataType;
}

DataTypeString* DataTypeString::clone() const
{
    return new DataTypeString(str_);
}

std::string DataTypeString::toString() const
{
    return str();
}

std::string DataTypeString::valueToJsonString() const
{
    return "\"" + string::escape_for_json(str()) + '"';
}

void DataTypeString::set(t_symbol* s)
{
    str_ = s->s_name;
}

void DataTypeString::set(const std::string& s)
{
    str_ = s;
}

void DataTypeString::split(std::vector<std::string>& res, const std::string& sep) const
{
    if (sep.empty())
        splitEveryChar(res);
    else
        splitBySep(res, sep);
}

DataTypeString DataTypeString::removeAll(const std::string& s) const
{
    return string::remove_all(str_, s);
}

DataTypeString DataTypeString::removeFirst(const std::string& s) const
{
    return string::remove_first(str_, s);
}

DataTypeString DataTypeString::removeLast(const std::string& s) const
{
    return string::remove_last(str_, s);
}

DataTypeString DataTypeString::replaceAll(const std::string& from, const std::string& to) const
{
    return string::replace_all(str_, from, to);
}

DataTypeString DataTypeString::replaceFirst(const std::string& from, const std::string& to) const
{
    return string::replace_first(str_, from, to);
}

DataTypeString DataTypeString::replaceLast(const std::string& from, const std::string& to) const
{
    return string::replace_last(str_, from, to);
}

size_t DataTypeString::length() const
{
    return string::utf8_strlen(str_.c_str());
}

DataTypeString DataTypeString::toLower() const
{
    return string::utf8_to_lower(str_.c_str());
}

DataTypeString DataTypeString::toUpper() const
{
    return string::utf8_to_upper(str_.c_str());
}

DataTypeString DataTypeString::substr(int from, size_t len) const
{
    return string::utf8_substr(str_.c_str(), from, len);
}

bool DataTypeString::isEqual(const AbstractData* d) const noexcept
{
    if (type() != d->type())
        return false;

    if (this == d)
        return true;

    const DataTypeString* cmp = d->as<DataTypeString>();

    static_assert(noexcept(operator==(*cmp)), "noexcept required");

    return this->operator==(*cmp);
}

bool DataTypeString::isLess(const AbstractData* d) const noexcept
{
    if (type() != d->type())
        return type() < d->type();

    if (this == d)
        return false;

    return str_ < (d->as<DataTypeString>()->str_);
}

void DataTypeString::splitEveryChar(std::vector<std::string>& res) const
{
    string::utf8_split_by_char(res, str_.c_str());
}

void DataTypeString::splitBySep(std::vector<std::string>& res, const std::string& sep) const
{
    string::split(res, str_, sep.c_str());
}

std::ostream& operator<<(std::ostream& os, const DataTypeString& d)
{
    os << d.toString();
    return os;
}

}
