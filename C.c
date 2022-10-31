#include <stdlib.h>
#include "simpfun.h"

int main(int argc, char *argv[])
{
    int m = atoi(argv[1]);
    int I = atoi(argv[2]);
    int J = atoi(argv[3]);
    int K = atoi(argv[4]);
    simpstart(m);
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