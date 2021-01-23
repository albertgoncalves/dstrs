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

typedef struct {
    f32 a;
    f32 b;
} PairF32;

#define PI 3.1415926535897932385f

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

#endif
