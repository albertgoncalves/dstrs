#include "beta.h"
#include "nbinom.h"

// NOTE: See `http://www.sumsar.net/blog/2014/10/tiny-data-and-the-socks-of-karl-broman/`.

typedef struct {
    u32 input_total;
    f32 input_ratio_pairs;
    u32 input_pairs;
    u32 input_singles;
    u32 output_pairs;
    u32 output_singles;
} Result;

#define SIZE_RESULTS 100000
#define SIZE_SAMPLE  200
#define SIZE_BUFFER  262144

const usize THRESHOLD = SIZE_BUFFER - 64;

typedef struct {
    Result results[SIZE_RESULTS];
    usize  sample[SIZE_SAMPLE];
    char   buffer[SIZE_BUFFER];
} Memory;

#define OBSERVED_PICKED  11
#define OBSERVED_SINGLES 11

const u32 OBSERVED_PAIRS = (OBSERVED_PICKED - OBSERVED_SINGLES) / 2;

#define PRIOR_NBINOM_MU    30.0f
#define PRIOR_NBINOM_SIGMA 15.0f
#define PRIOR_BETA_ALPHA   15.0f
#define PRIOR_BETA_BETA    2.0f

const f32 PRIOR_NBINOM_RATE =
    -((PRIOR_NBINOM_MU * PRIOR_NBINOM_MU) /
      (PRIOR_NBINOM_MU - (PRIOR_NBINOM_SIGMA * PRIOR_NBINOM_SIGMA)));
const f32 PRIOR_NBINOM_PROB =
    PRIOR_NBINOM_RATE / (PRIOR_NBINOM_RATE + PRIOR_NBINOM_MU);

DEFINE_SHUFFLE(shuffle, usize)
DEFINE_COUNT_DUPLICATES(count_duplicates, usize)

static void set_socks(usize* array, u32 input_pairs, u32 input_singles) {
    usize i = 0;
    usize j = 0;
    for (u32 _ = 0; _ < input_pairs; ++_) {
        array[i++] = j;
        array[i++] = j++;
    }
    for (u32 _ = 0; _ < input_singles; ++_) {
        array[i++] = j++;
    }
}

i32 main(i32 n, const char** args) {
    EXIT_IF(n < 2);
    printf("sizeof(Result) : %zu\n"
           "sizeof(Memory) : %zu\n"
           "\n",
           sizeof(Result),
           sizeof(Memory));
    Memory* memory = calloc(1, sizeof(Memory));
    {
        PcgRng rng = get_rng();
        set_seed(&rng, get_microseconds(), 1);
        for (usize i = 0; i < SIZE_RESULTS; ++i) {
            u32 input_total;
            do {
                input_total = get_random_nbinom(&rng,
                                                PRIOR_NBINOM_RATE,
                                                1.0f - PRIOR_NBINOM_PROB);
            } while ((input_total < OBSERVED_PICKED) ||
                     (SIZE_SAMPLE < input_total));
            f32 input_ratio_pairs =
                get_random_beta(&rng, PRIOR_BETA_ALPHA, PRIOR_BETA_BETA);
            u32 input_pairs =
                (u32)roundf((f32)(input_total / 2) * input_ratio_pairs);
            u32 input_singles = input_total - (input_pairs * 2);
            set_socks(memory->sample, input_pairs, input_singles);
            shuffle(&rng, memory->sample, input_total);
            u32 output_pairs =
                count_duplicates(memory->sample, OBSERVED_PICKED);
            memory->results[i].input_total = input_total;
            memory->results[i].input_ratio_pairs = input_ratio_pairs;
            memory->results[i].input_pairs = input_pairs;
            memory->results[i].input_singles = input_singles;
            memory->results[i].output_pairs = output_pairs;
            memory->results[i].output_singles =
                OBSERVED_PICKED - (output_pairs * 2);
        }
        {
            usize size = 0;
            for (usize i = 0; i < SIZE_RESULTS; ++i) {
                EXIT_IF(THRESHOLD < size);
                if ((memory->results[i].output_singles == OBSERVED_SINGLES) &&
                    (memory->results[i].output_pairs == OBSERVED_PAIRS))
                {
                    i32 m = sprintf(&memory->buffer[size],
                                    "%u\n",
                                    memory->results[i].input_total);
                    EXIT_IF(m < 0);
                    size += (usize)m;
                }
            }
            set_file(args[1], memory->buffer, size);
        }
    }
    free(memory);
    return EXIT_SUCCESS;
}
