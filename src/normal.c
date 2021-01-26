#include "normal.h"

#define SIZE_BUFFER 262144

const usize THRESHOLD_BUFFER = SIZE_BUFFER - 128;

#define FMT "%.6f\n"

i32 main(i32 n, const char** args) {
    EXIT_IF(n < 2);
    char* buffer = malloc(sizeof(char) * SIZE_BUFFER);
    usize size = 0;
    {
        PcgRng rng = get_rng();
        set_seed(&rng, get_microseconds(), 1);
        for (usize i = 0; i < 5000; ++i) {
            EXIT_IF(THRESHOLD_BUFFER < size);
            Pair_f32 pair = get_random_normal_pair(&rng, -2.0f, 10.0f);
            i32      line =
                sprintf(&buffer[size], FMT FMT, (f64)pair.a, (f64)pair.b);
            EXIT_IF(line <= 0);
            size += (usize)line;
        }
    }
    set_file(args[1], buffer, size);
    free(buffer);
    return EXIT_SUCCESS;
}
