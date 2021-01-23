#ifndef __BETA_H__
#define __BETA_H__

#include "gamma.h"

// NOTE: See `https://en.wikipedia.org/wiki/Beta_distribution#Generating_beta-distributed_random_variates`.
static f32 get_random_beta(PcgRng* rng, f32 alpha, f32 beta) {
    f32 x = get_random_gamma(rng, alpha, 1.0f);
    f32 y = get_random_gamma(rng, beta, 1.0f);
    return x / (x + y);
}

#endif
