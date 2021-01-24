#include "nbinom.h"

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
        //       > rnbinom(10000, size = `rate`, prob = 1.0 - `prob`)
        for (usize i = 0; i < 10000; ++i) {
            EXIT_IF(THRESHOLD < size);
            i32 m = sprintf(&buffer[size],
                            "%u\n",
                            get_random_nbinom(&rng, 20.0f, 0.1f));
            EXIT_IF(m < 0);
            size += (usize)m;
        }
    }
    set_file(args[1], buffer, size);
    free(buffer);
    return EXIT_SUCCESS;
}
