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

static u32 rotr(u32 x, u32 n) {
    __asm__("ror %1,%0" : "+r"(x) : "c"(n));
    return x;
}

static u32 get_random_uniform_u32(PcgRng* rng) {
    const u64 state = rng->state;
    rng->state = (state * 6364136223846793005llu) + (rng->increment | 1u);
    const u32 xor_shift = (u32)(((state >> 18u) ^ state) >> 27u);
    const u32 rotate = (u32)(state >> 59u);
    return rotr(xor_shift, rotate);
}

static void set_seed(PcgRng* rng, u64 state, u64 increment) {
    rng->state = 0u;
    rng->increment = (increment << 1u) | 1u;
    get_random_uniform_u32(rng);
    rng->state += state;
    get_random_uniform_u32(rng);
}

// NOTE: See `https://github.com/hfinkel/sleef-bgq/blob/master/purec/sleefsp.c#L117-L130`.
static f32 ldexpf_(f32 x, i32 q) {
    i32 m = q >> 31;
    m = (((m + q) >> 6) - m) << 4;
    q = q - (m << 2);
    m += 127;
    m = m < 0 ? 0 : m;
    m = m > 255 ? 255 : m;
    union {
        f32 as_f32;
        i32 as_i32;
    } u;
    u.as_i32 = m << 23;
    x = x * u.as_f32 * u.as_f32 * u.as_f32 * u.as_f32;
    u.as_i32 = (q + 0x7F) << 23;
    return x * u.as_f32;
}

// NOTE: See `https://www.pcg-random.org/using-pcg-c-basic.html#generating-doubles`.
static f32 get_random_uniform_f32(PcgRng* rng) {
    return ldexpf_((f32)get_random_uniform_u32(rng), -32);
}

// NOTE: See `https://github.com/hfinkel/sleef-bgq/blob/master/purec/sleefdp.c#L113-L126`.
static f64 ldexp_(f64 x, i64 q) {
    i64 m = q >> 31l;
    m = (((m + q) >> 9l) - m) << 7;
    q = q - (m << 2l);
    m += 0x3FFl;
    m = m < 0l ? 0l : m;
    m = m > 0x7FFl ? 0x7FFl : m;
    union {
        f64 as_f64;
        i64 as_i64;
    } u;
    u.as_i64 = m << 52l;
    x = x * u.as_f64 * u.as_f64 * u.as_f64 * u.as_f64;
    u.as_i64 = (q + 0x3FFl) << 52l;
    return x * u.as_f64;
}

static f64 get_random_uniform_f64(PcgRng* rng) {
    return ldexp_((f64)get_random_uniform_u32(rng), -32);
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
