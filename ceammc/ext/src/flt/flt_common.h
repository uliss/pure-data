/*****************************************************************************
 * Copyright 2021 Serge Poltavsky. All rights reserved.
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
#ifndef FLT_COMMON_H
#define FLT_COMMON_H

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <cmath>

namespace ceammc {
namespace flt {

    constexpr double m_pi = M_PI;
    constexpr double m_2pi = 2 * M_PI;

    /**
     * converts frequency in herz to angular frequency
     * @param f0 - frequency
     * @param Fs - samplerate frequency
     * @return angular frequency
     */
    static inline double hz2w(double f0, double Fs)
    {
        return m_2pi * f0 / Fs;
    }

    /**
     * converts bandwidth in octaves to quality factor
     * @param bw - bandwidth in octaves
     * @param w - angular frequency
     * @return quality factor
     */
    double bandwidth2q(double bw, double w);

    /**
     * converts quality factor to bandwidth in octaves
     * @param q - quality factor
     * @param w - angular frequency
     * @return - bandwidth in octaves
     */
    double q2bandwidth(double q, double w);
}
}

#endif // FLT_COMMON_H
