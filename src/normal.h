#ifndef __NORMAL_H__
#define __NORMAL_H__

#include "pcg_rng.h"

// NOTE: This is inefficient!
static f32 get_random_normal(PcgRng* rng, f32 mu, f32 sigma) {
    EXIT_IF(sigma <= 0.0f);
    f32 a = sqrtf(-2.0f * logf(get_random_uniform_f32(rng)));
    f32 b = 2.0f * PI_F32 * get_random_uniform_f32(rng);
    return ((a * cosf(b)) * sigma) + mu;
}

// NOTE: See `https://mathworld.wolfram.com/Box-MullerTransformation.html`.
// NOTE: See `https://www.doc.ic.ac.uk/~wl/papers/07/csur07dt.pdf`.
static PairF32 get_random_normal_pair(PcgRng* rng, f32 mu, f32 sigma) {
    EXIT_IF(sigma <= 0.0f);
    f32 a = sqrtf(-2.0f * logf(get_random_uniform_f32(rng)));
    f32 b = 2.0f * PI_F32 * get_random_uniform_f32(rng);
    return (PairF32){
        .a = ((a * cosf(b)) * sigma) + mu,
        .b = ((a * sinf(b)) * sigma) + mu,
    };
}

#endif
