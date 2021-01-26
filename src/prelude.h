#ifndef __PRELUDE_H__
#define __PRELUDE_H__

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef uint32_t u32;
typedef uint64_t u64;
typedef size_t   usize;

typedef int32_t i32;

typedef float  f32;
typedef double f64;

typedef FILE File;

typedef struct timeval TimeValue;

#define PI_F32 3.1415926535897932385f

#define EXIT_IF(condition)         \
    if (condition) {               \
        fprintf(stderr,            \
                "%s:%s:%d `%s`\n", \
                __FILE__,          \
                __func__,          \
                __LINE__,          \
                #condition);       \
        exit(EXIT_FAILURE);        \
    }

static u64 get_microseconds() {
    TimeValue time;
    gettimeofday(&time, NULL);
    return (u64)time.tv_usec;
}

static void set_file(const char* filename, const char* buffer, usize n) {
    File* file = fopen(filename, "w");
    EXIT_IF(fwrite(buffer, sizeof(char), n, file) != n);
    fclose(file);
}

#define DEFINE_PAIR(label, type) \
    typedef struct {             \
        type a;                  \
        type b;                  \
    } label;

#define DEFINE_PRINT_ARRAY(fn, type, fmt)           \
    static void print_array(type* array, usize n) { \
        printf("[ ");                               \
        for (usize i = 0; i < n; ++i) {             \
            printf(fmt " ", array[i]);              \
        }                                           \
        printf("]\n");                              \
    }

#define DEFINE_COUNT_DUPLICATES(fn, type)               \
    static u32 count_duplicates(type* array, usize n) { \
        u32 result = 0;                                 \
        for (usize i = 0; i < n; ++i) {                 \
            for (usize j = i + 1; j < n; ++j) {         \
                if (array[i] == array[j]) {             \
                    ++result;                           \
                }                                       \
            }                                           \
        }                                               \
        return result;                                  \
    }

#endif
