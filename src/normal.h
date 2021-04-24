#ifndef __NORMAL_H__
#define __NORMAL_H__

#include "pcg_rng.h"

DEFINE_PAIR(Pair_f32, f32)

// NOTE: This is inefficient!
static f32 get_random_normal(PcgRng* rng, f32 mu, f32 sigma) {
    EXIT_IF(sigma <= 0.0f);
    const f32 a = sqrtf(-2.0f * logf(get_random_uniform_f32(rng)));
    const f32 b = 2.0f * PI_F32 * get_random_uniform_f32(rng);
    return ((a * cosf(b)) * sigma) + mu;
}

// NOTE: See `https://mathworld.wolfram.com/Box-MullerTransformation.html`.
// NOTE: See `https://www.doc.ic.ac.uk/~wl/papers/07/csur07dt.pdf`.
static Pair_f32 get_random_normal_pair(PcgRng* rng, f32 mu, f32 sigma) {
    EXIT_IF(sigma <= 0.0f);
    const f32 a = sqrtf(-2.0f * logf(get_random_uniform_f32(rng)));
    const f32 b = 2.0f * PI_F32 * get_random_uniform_f32(rng);
    return (Pair_f32){
        .a = ((a * cosf(b)) * sigma) + mu,
        .b = ((a * sinf(b)) * sigma) + mu,
    };
}

#endif
