#ifndef __GAMMA_H__
#define __GAMMA_H__

#include "normal.h"

// NOTE: See `http://git.savannah.gnu.org/cgit/gsl.git/tree/randist/gamma.c#n192`
// NOTE: See `https://github.com/admb-project/admb/blob/master/contrib/qfclib/gsl_ran_gamma.cpp`
f32 get_random_gamma(PcgRng*, f32, f32);
f32 get_random_gamma(PcgRng* rng, f32 alpha, f32 beta) {
    EXIT_IF((alpha <= 0.0f) || (beta <= 0.0f));
    f32 u = get_random_uniform_f32(rng);
    if (alpha < 1.0f) {
        return get_random_gamma(rng, 1.0f + alpha, beta) *
               powf(u, 1.0f / alpha);
    }
    f32 v;
    f32 d = alpha - (1.0f / 3.0f);
    f32 c = (1.0f / 3.0f) / sqrtf(d);
    for (;;) {
        f32 x;
        do {
            x = get_random_normal(rng, 0.0, 1.0);
            v = 1.0f + (c * x);
        } while (v <= 0.0f);
        v = v * v * v;
        if ((u < (1.0f - (0.0331f * x * x * x * x))) ||
            (logf(u) < ((0.5f * x * x) + (d * ((1.0f - v) + logf(v))))))
        {
            break;
        }
    }
    return beta * d * v;
}

#endif
