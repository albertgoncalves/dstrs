#ifndef __PCG_RNG_H__
#define __PCG_RNG_H__

#include "prelude.h"

typedef struct {
    u64 state;
    u64 increment;
} PcgRng;

static PcgRng get_rng(void) {
    return (PcgRng){
        .state = 9600629759793949339llu,
        .increment = 15726070495360670683llu,
    };
}

static u32 get_random_uniform_u32(PcgRng* rng) {
    const u64 state = rng->state;
    rng->state = (state * 6364136223846793005llu) + (rng->increment | 1u);
    const u32 xor_shift = (u32)(((state >> 18u) ^ state) >> 27u);
    const u32 rotate = (u32)(state >> 59u);
    return (xor_shift >> rotate) | (xor_shift << ((-rotate) & 31u));
}

static void set_seed(PcgRng* rng, u64 state, u64 increment) {
    rng->state = 0u;
    rng->increment = (increment << 1u) | 1u;
    get_random_uniform_u32(rng);
    rng->state += state;
    get_random_uniform_u32(rng);
}

// NOTE: See `https://www.pcg-random.org/using-pcg-c-basic.html#generating-doubles`.
static f32 get_random_uniform_f32(PcgRng* rng) {
    return ldexpf((f32)get_random_uniform_u32(rng), -32);
}

static f64 get_random_uniform_f64(PcgRng* rng) {
    return ldexp((f64)get_random_uniform_u32(rng), -32);
}

// NOTE: See `https://github.com/imneme/pcg-c-basic/blob/master/pcg_basic.c#L75-L109`.
static u32 get_random_bounded_u32(PcgRng* rng, u32 bound) {
    const u32 threshold = (-bound) % bound;
    for (;;) {
        const u32 r = get_random_uniform_u32(rng);
        if (threshold < r) {
            return r % bound;
        }
    }
}

// NOTE: See `https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle`.
#define DEFINE_SHUFFLE(fn, type)                               \
    static void fn(PcgRng* rng, type* array, u32 n) {          \
        for (u32 i = n - 1; 0 < i; --i) {                      \
            const u32  j = get_random_bounded_u32(rng, i + 1); \
            const type t = array[i];                           \
            array[i] = array[j];                               \
            array[j] = t;                                      \
        }                                                      \
    }

#endif
