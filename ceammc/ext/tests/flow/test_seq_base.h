#ifndef TEST_SEQ_BASE_H_
#define TEST_SEQ_BASE_H_

#include "m_pd.h"

#include <type_traits>

// windows PureData delay time fix
static int operator""_wd(unsigned long long x)
{
    return x + std::is_same<double, t_float>::value;
}

#endif // TEST_SEQ_BASE_H_
