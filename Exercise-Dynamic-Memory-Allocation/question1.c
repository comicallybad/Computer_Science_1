#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "leak_detector_c.h"

float **AllocateArrayOfArrays(int P, int *Lengths)
{
    float **ptr = malloc(P * sizeof(Lengths));
    for (int i = 0; i < P; i++)
    {
        ptr[i] = malloc(Lengths[i] * sizeof(float));
        for (int j = 0; j < Lengths[i]; j++)
        {
            ptr[i][j] = (int)rand() % 100 + 1;
        }
    }
    return ptr;
}

int main(void)
{
    srand(time(0));
    atexit(report_mem_leak);
    int P = 5;
    int Lengths[5] = {3, 3, 4, 4, 5};
    float **array1 = AllocateArrayOfArrays(P, Lengths);

    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < Lengths[i]; j++)
        {
            printf("%f, ", array1[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < P; i++)
    {
        free(array1[i]);
    }

    free(array1);

    return 0;
}
