/*****************************************************************************
 * Copyright 2016 Serge Poltavski. All rights reserved.
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
#ifndef CEAMMC_ATOM_H
#define CEAMMC_ATOM_H

#include "m_pd.h"

#include <iostream>
#include <string>
#include <utility>

#if defined(__has_feature)
#if __has_feature(address_sanitizer)
#define CEAMMC_NO_ASAN __attribute__((no_sanitize("address"))) __attribute__((no_sanitize("undefined")))
#else
#define CEAMMC_NO_ASAN
#endif
#else
#define CEAMMC_NO_ASAN
#endif

#if defined(__GNUC__) || defined(__clang__)
#define CEAMMC_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define CEAMMC_DEPRECATED __declspec(deprecated)
#else
#pragma message("WARNING: You need to implement CEAMMC_DEPRECATED for this compiler")
#define CEAMMC_DEPRECATED
#endif

#if defined(__GNUC__) || defined(__clang__)
#define CEAMMC_WARN_UNUSED __attribute__((warn_unused_result))
#define CEAMMC_PACKED __attribute__((packed))
#else
#define CEAMMC_WARN_UNUSED
#define CEAMMC_PACKED
#endif

namespace ceammc {

class Atom;
typedef Atom (*AtomMapFunction)(const Atom& a);
typedef t_float (*AtomFloatMapFunction)(t_float f);
typedef t_symbol* (*AtomSymbolMapFunction)(t_symbol* s);

typedef unsigned int DataId;
typedef unsigned short DataType;

struct DataDesc {
    DataType type;
    DataId id;

    DataDesc(DataType t, DataId i);
    bool operator==(const DataDesc& d) const;
    bool operator!=(const DataDesc& d) const;
};

class Atom : t_atom {
public:
    /**
     * @brief logical atom type
     */
    enum Type {
        NONE,
        FLOAT,
        SYMBOL,
        PROPERTY,
        DATA
    };

    static const char PROP_PREFIX = '@';

public:
    Atom();
    CEAMMC_NO_ASAN Atom(const t_atom& a);
    Atom(t_float v);
    Atom(t_symbol* s);
    Atom(const DataDesc& d);

    /**
     * Checks if atom is (0|1|true|false)
     */
    bool isBool() const;

    /**
     * @returns true if atom has logical type Atom::FLOAT
     */
    bool isFloat() const;

    /**
     * @return true if atom has logical type Atom::FLOAT and >= 0
     */
    bool isNonNegative() const;

    /**
     * @return true if atom has logical type Atom::FLOAT and > 0
     */
    bool isPositive() const;

    /**
     * @returns true if atom has logical type Atom::NONE
     */
    bool isNone() const;

    /**
     * @returns true if atom has logical type Atom::SYMBOL
     */
    bool isSymbol() const;

    /**
     * @returns true if atom has logical type Atom::PROPERTY
     */
    bool isProperty() const;

    /**
     * @returns true if atom has logical type Atom::FLOAT and value is integer
     */
    bool isInteger() const;

    /**
     * @returns true if atom has logical type Atom::FLOAT and value is natural (with 0)
     */
    bool isNatural() const;

    /**
     * template parameterized atom type check
     */
    template <typename T>
    inline bool isA() const;

    /**
     * template parameterized atom value as typed value
     * @note no type checks are done
     */
    template <typename T>
    inline T asT() const;

    /**
     *template parameterized atom value as typed value
     * @return valid atom typed value or def value, if type is invalid
     */
    template <typename T>
    inline T toT(T def) const { return (isA<T>()) ? asT<T>() : def; }

    /**
     * @returns atom logical type
     */
    CEAMMC_NO_ASAN Type type() const;

    /**
     * Tries to get float from atom - writes to destination only if atom type if float
     * @param v - pointer to destination
     * @return true on success, false - if atom is not float
     * @see getSymbol
     */
    bool getFloat(t_float* v) const;
    bool getSymbol(t_symbol** s) const;
    bool getString(std::string& str) const;

    bool setFloat(t_float v, bool force = false);
    bool setSymbol(t_symbol* s, bool force = false);

    bool asBool(bool def = false) const;
    t_float asFloat(t_float def = 0.f) const;
    int asInt(int def = 0) const;
    size_t asSizeT(size_t def = 0) const;
    t_symbol* asSymbol() const;

    const t_atom& atom() const { return *static_cast<const t_atom*>(this); }

    /**
     * @deprecated
     */
    CEAMMC_DEPRECATED std::string asString() const;

    /**
     * compare operator
     * compare atoms of same type.
     * @note now only floats and symbols
     */
    CEAMMC_NO_ASAN bool operator<(const Atom& a) const;

    /**
     * @brief outputs atom to given outlet
     * @param x - pointer to outlet
     */
    void output(t_outlet* x) const;

    void outputAsAny(t_outlet* x, t_symbol* sel) const;

    /**
     * Operators
     */
    Atom& operator+=(t_float v);
    Atom& operator-=(t_float v);
    Atom& operator*=(t_float v);
    Atom& operator/=(t_float v);

    Atom operator+(t_float v) const;
    Atom operator-(t_float v) const;
    Atom operator*(t_float v) const;
    Atom operator/(t_float v) const;

    /**
     * Apply function
     */
    void apply(AtomFloatMapFunction f);
    void apply(AtomSymbolMapFunction f);
    template <class F>
    void apply(F fn);
    template <class F>
    void applyFloat(F fn);

    /**
     * Data functions
     */

    /**
     * @brief dataType
     * @return data type or 0 on error
     */
    DataType dataType() const;

    /**
     * @brief dataId
     * @return data id or 0 on error
     */
    DataId dataId() const;

    CEAMMC_NO_ASAN DataDesc getData() const;
    CEAMMC_NO_ASAN void setData(const DataDesc& d);

    /**
     * @returns true if atom is a data structure
     */
    bool isData() const;

    /**
     * @returns true if atom is a data structure of specified type
     */
    bool isDataType(DataType type) const;

public:
    friend bool operator==(const Atom& a1, const Atom& a2);
    friend bool operator!=(const Atom& a1, const Atom& a2);
};

template <>
inline bool Atom::isA<bool>() const { return isBool(); }
template <>
inline bool Atom::isA<t_float>() const { return isFloat(); }
template <>
inline bool Atom::isA<int>() const { return isInteger(); }
template <>
inline bool Atom::isA<t_symbol*>() const { return isSymbol(); }

template <>
inline bool Atom::asT<bool>() const { return asBool(); }
template <>
inline t_float Atom::asT<t_float>() const { return a_w.w_float; }
template <>
inline int Atom::asT<int>() const { return static_cast<int>(a_w.w_float); }
template <>
inline t_symbol* Atom::asT<t_symbol*>() const { return a_w.w_symbol; }

template <class F>
inline void Atom::apply(F fn) { *this = fn(*this); }
template <class F>
inline void Atom::applyFloat(F fn)
{
    if (isFloat())
        a_w.w_float = fn(a_w.w_float);
}

template <typename T>
static inline Atom atomFrom(T v) { return Atom(v); }
template <>
Atom atomFrom(const char* s) { return Atom(gensym(s)); }
template <>
Atom atomFrom(std::string v) { return Atom(gensym(v.c_str())); }

CEAMMC_NO_ASAN bool operator==(const Atom& a1, const Atom& a2);
bool operator!=(const Atom& a1, const Atom& a2);
std::ostream& operator<<(std::ostream& os, const Atom& a);

bool to_outlet(t_outlet* x, const Atom& a);

static inline bool isFloat(const Atom& a) { return a.isFloat(); }
static inline bool isSymbol(const Atom& a) { return a.isSymbol(); }
static inline bool isProperty(const Atom& a) { return a.isProperty(); }
static inline bool notFloat(const Atom& a) { return !a.isFloat(); }
static inline bool notSymbol(const Atom& a) { return !a.isSymbol(); }
static inline bool notProperty(const Atom& a) { return !a.isProperty(); }
static inline bool isData(const Atom& a) { return a.isData(); }

}

#endif // CEAMMC_ATOM_H
