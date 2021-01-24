#include "gamma.h"

#define SIZE_BUFFER 262144

const usize THRESHOLD_BUFFER = SIZE_BUFFER - 64;

i32 main(i32 n, const char** args) {
    EXIT_IF(n < 2);
    char* buffer = malloc(sizeof(char) * SIZE_BUFFER);
    usize size = 0;
    {
        PcgRng rng = get_rng();
        set_seed(&rng, get_microseconds(), 1);
        // NOTE: See `https://en.wikipedia.org/wiki/Gamma_distribution`.
        f32 theta = 2.0f;
        // NOTE: $ R
        //       > rgamma(10000, shape = `alpha`, scale = `beta`)
        for (usize i = 0; i < 10000; ++i) {
            EXIT_IF(THRESHOLD_BUFFER < size);
            i32 line =
                sprintf(&buffer[size],
                        "%.6f\n",
                        (f64)get_random_gamma(&rng, 1.5f, 1.0f / theta));
            EXIT_IF(line <= 0);
            size += (usize)line;
        }
    }
    set_file(args[1], buffer, size);
    free(buffer);
    return EXIT_SUCCESS;
}
