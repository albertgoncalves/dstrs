#ifndef __POISSON_H__
#define __POISSON_H__

#include "pcg_rng.h"

#define STEP 500.0

// NOTE: See `https://en.wikipedia.org/wiki/Poisson_distribution#Random_drawing_from_the_Poisson_distribution`.
static u32 get_random_poisson(PcgRng* rng, f64 lambda) {
    EXIT_IF(lambda <= 0.0);
    f64 l = lambda;
    u32 k = 0;
    f64 p = 1.0;
    do {
        ++k;
        p *= get_random_uniform_f64(rng);
        while (p < 1.0) {
            if (STEP < l) {
                p *= exp(STEP);
                l -= STEP;
            } else {
                p *= exp(l);
                l = 0.0;
                break;
            }
        }
    } while (1.0 < p);
    return k - 1;
}

#endif
