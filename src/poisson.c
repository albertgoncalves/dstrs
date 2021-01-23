#include "poisson.h"

#define SIZE_BUFFER 262144

const usize THRESHOLD = SIZE_BUFFER - 64;

i32 main(i32 n, const char** args) {
    EXIT_IF(n < 2);
    char* buffer = malloc(sizeof(char) * SIZE_BUFFER);
    usize size = 0;
    {
        PcgRng rng = get_rng();
        set_seed(&rng, get_microseconds(), 1);
        for (usize i = 0; i < 10000; ++i) {
            EXIT_IF(THRESHOLD < size);
            i32 m = sprintf(&buffer[size],
                            "%u.0\n",
                            get_random_poisson(&rng, 1000.0));
            EXIT_IF(m < 0);
            size += (usize)m;
        }
    }
    set_file(args[1], buffer, size);
    free(buffer);
    return EXIT_SUCCESS;
}