#ifndef __EXPON_H__
#define __EXPON_H__

#include "pcg_rng.h"

// NOTE: See `https://en.wikipedia.org/wiki/Exponential_distribution#Generating_exponential_variates`.
static f32 get_random_expon(PcgRng* rng, f32 lambda) {
    return -logf(get_random_uniform_f32(rng)) / lambda;
}

#endif
