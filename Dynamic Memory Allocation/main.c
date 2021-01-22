#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define maxNumber 500

int *readArray(int size)
{
    int *array = (int *)malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++)
    {
        array[i] = rand() % maxNumber;
    }

    return array;
}

int main(void)
{
    int n;
    printf("How many numbers? ");
    scanf("%d", &n);

    int *p = readArray(n);

    for (int i = 0; i < n; i++)
        printf("%d ", p[i]);

    free(p);

    return 0;
}