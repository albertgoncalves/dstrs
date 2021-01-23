#ifndef __NORMAL_H__
#define __NORMAL_H__

#include "pcg_rng.h"

// NOTE: See `https://mathworld.wolfram.com/Box-MullerTransformation.html`.
static PairF32 get_random_normal_pair(PcgRng* rng, f32 mu, f32 sigma) {
    EXIT_IF(sigma <= 0.0f);
    f32 a = sqrtf(-2.0f * logf(get_random_f32(rng)));
    f32 b = 2.0f * PI * get_random_f32(rng);
    return (PairF32){
        .a = ((a * cosf(b)) * sigma) + mu,
        .b = ((a * sinf(b)) * sigma) + mu,
    };
}

#endif
