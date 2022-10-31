#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "simpfun.h"

static size_t M;
static long long *buffer0, *buffer1;

static void simpini(int m)
{
    M = m;
    buffer0 = malloc(M * sizeof(long long));
    buffer1 = malloc(M * sizeof(long long));
    srand(time(NULL));
    for (int ndx = 0; ndx < M; ++ndx)
    {
        buffer0[ndx] = rand() * rand();
        buffer1[ndx] = rand() * rand();
    }
}

#if defined(_WIN32)
#include <Windows.h>

static LARGE_INTEGER freq, start;

void simpstart(int m)
{
    simpini(m);
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
}

static void simpfin()
{
    LARGE_INTEGER elapse;
    QueryPerformanceCounter(&elapse);
    elapse.QuadPart -= start.QuadPart;
    double dt = 1.0 * elapse.QuadPart / freq.QuadPart;
    printf_s("cost %f seconds, ", dt);
}
#elif defined(__APPLE__)
#include <time.h>

#define printf_s printf

static __uint64_t start;

void simpstart(int m)
{
    simpini(m);
    start = clock_gettime_nsec_np(CLOCK_MONOTONIC);
}

static void simpfin()
{
    __uint64_t elapse = clock_gettime_nsec_np(CLOCK_MONOTONIC) - start;
    double dt = elapse / 1000000000.0;
    printf_s("cost %f seconds, ", dt);
}
#else
#include <time.h>

#define printf_s printf

static struct timespec start;

void simpstart(int m)
{
    simpini(m);
    clock_gettime(CLOCK_MONOTONIC, &start);
}

static void simpfin()
{
    struct timespec finish;
    clock_gettime(CLOCK_MONOTONIC, &finish);
    double dt = ((finish.tv_sec - start.tv_sec) * 1000000000.0 + finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf_s("cost %f seconds, ", dt);
}
#endif

static long long sum = 0;

void simpfun(int i, int j, int k)
{
    for (int ndx = 0; ndx < M; ++ndx)
    {
        sum += buffer0[ndx] - buffer1[ndx];
    }
}

void dumpfin()
{
    simpfin();
    free(buffer0);
    free(buffer1);
    printf_s("sum %lld\n", sum);
}