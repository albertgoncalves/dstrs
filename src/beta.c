#include "beta.h"

#define SIZE_BUFFER 262144

const usize THRESHOLD = SIZE_BUFFER - 64;

i32 main(i32 n, const char** args) {
    EXIT_IF(n < 2);
    char* buffer = malloc(sizeof(char) * SIZE_BUFFER);
    usize size = 0;
    {
        PcgRng rng = get_rng();
        set_seed(&rng, get_microseconds(), 1);
        // NOTE: $ R
        //       > rbeta(10000, shape1 = `alpha`, shape2 = `beta`)
        for (usize i = 0; i < 10000; ++i) {
            EXIT_IF(THRESHOLD < size);
            i32 m = sprintf(&buffer[size],
                            "%.6f\n",
                            (f64)get_random_beta(&rng, 15.0f, 2.0f));
            EXIT_IF(m < 0);
            size += (usize)m;
        }
    }
    set_file(args[1], buffer, size);
    free(buffer);
    return EXIT_SUCCESS;
}
