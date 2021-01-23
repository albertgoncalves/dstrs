#include "gamma.h"

#define SIZE_BUFFER 262144

const usize THRESHOLD = SIZE_BUFFER - 128;

i32 main(i32 n, const char** args) {
    EXIT_IF(n < 2);
    char* buffer = malloc(sizeof(char) * SIZE_BUFFER);
    usize size = 0;
    {
        PcgRng rng = get_rng();
        set_seed(&rng, get_microseconds(), 1);
        // NOTE: See `https://en.wikipedia.org/wiki/Gamma_distribution`.
        f32 alpha = 1.5f;
        f32 theta = 2.0f;
        f32 beta = 1.0f / theta;
        for (usize i = 0; i < 10000; ++i) {
            EXIT_IF(THRESHOLD < size);
            i32 m = sprintf(&buffer[size],
                            "%.6f\n",
                            (f64)get_random_gamma(&rng, alpha, beta));
            EXIT_IF(m < 0);
            size += (usize)m;
        }
    }
    set_file(args[1], buffer, size);
    free(buffer);
    return EXIT_SUCCESS;
}
