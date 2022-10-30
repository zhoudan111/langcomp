#include <stdio.h>
#include "simpfun.h"

#ifdef _WIN32
#include <Windows.h>

static LARGE_INTEGER freq, start;

void simpstart()
{
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
}

static simpfin()
{
    LARGE_INTEGER elapse;
    QueryPerformanceCounter(&elapse);
    elapse.QuadPart -= start.QuadPart;
    double dt = 1.0 * elapse.QuadPart / freq.QuadPart;
    printf_s("cost %f seconds, ", dt);
}
#endif

static long long sum = 0;

void simpfun(int i, int j, int k)
{
    ++sum;
}

void dumpfin()
{
    simpfin();
    printf_s("sum %lld\n", sum);
}