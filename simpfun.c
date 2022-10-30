#include <stdio.h>
#include <string.h>
#include "simpfun.h"

#if defined(_WIN32)
#include <Windows.h>

static LARGE_INTEGER freq, start;

void simpstart()
{
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

void simpstart()
{
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

void simpstart()
{
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
static char buffer0[65536 * 64];
static char buffer1[65536 * 64];

void simpfun(int i, int j, int k)
{
    ++sum;
    memset(buffer0, 0xc3, sizeof(buffer0));
    memset(buffer1, 0xb5, sizeof(buffer1));
    memcpy(buffer0, buffer1, sizeof(buffer1));
}

void dumpfin()
{
    simpfin();
    printf_s("sum %lld\n", sum);
}