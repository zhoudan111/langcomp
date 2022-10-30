#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simpfun.h"

int main(int argc, char *argv[])
{
    int I = atoi(argv[1]);
    int J = atoi(argv[2]);
    int K = atoi(argv[3]);
    simpstart();
    for (int i = 0; i < I; ++i)
    {
        for (int j = 0; j < J; ++j)
        {
            for (int k = 0; k < K; ++k)
            {
                simpfun(i, j, k);
            }
        }
    }
    dumpfin();
    return 0;
}