#include "poisson.h"

#define SIZE_BUFFER 262144

static const usize THRESHOLD_BUFFER = SIZE_BUFFER - 64;

i32 main(i32 n, const char** args) {
    EXIT_IF(n < 2);
    char* buffer = malloc(sizeof(char) * SIZE_BUFFER);
    usize size = 0;
    {
        PcgRng rng = get_rng();
        set_seed(&rng, get_microseconds(), 1);
        for (usize i = 0; i < 10000; ++i) {
            EXIT_IF(THRESHOLD_BUFFER < size);
            const i32 line =
                sprintf(&buffer[size], "%u\n", get_random_poisson(&rng, 2.25));
            EXIT_IF(line <= 0);
            size += (usize)line;
        }
    }
    set_file(args[1], buffer, size);
    free(buffer);
    return EXIT_SUCCESS;
}
