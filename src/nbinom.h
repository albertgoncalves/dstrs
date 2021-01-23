#ifndef __NBINOM_H__
#define __NBINOM_H__

#include "gamma.h"
#include "poisson.h"

// NOTE: See `https://github.com/ampl/gsl/blob/master/randist/nbinomial.c#L27-L41`.
// NOTE: See `http://gregorygundersen.com/blog/2019/09/16/poisson-gamma-nb/`.
static u32 get_random_nbinom(PcgRng* rng, f32 rate, f32 prob) {
    EXIT_IF((prob <= 0.0f) || (1.0f <= prob));
    return get_random_poisson(
        rng,
        (f64)(get_random_gamma(rng, rate, prob / (1.0f - prob))));
}

#endif
