#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20

int main(void)
{
    FILE *input = fopen("in.txt", "r");

    int numCases, loop;
    fscanf(input, "%d", &numCases);

    for (loop = 1; loop <= numCases; loop++)
    {
        int weights[MAXSIZE];
        int values[MAXSIZE];
        int n, maxWeight, i;
        fscanf(input, "%d %d", &n, &maxWeight);

        for (i = 0; i < n; i++)
        {
            fscanf(input, "%d %d", &weights[i], &values[i]);
        }

        int bestValue = 0, bestSubset = 0, subset;

        for (subset = 1; subset < (1 << n); subset++)
        {
            int thisValue = 0, thisWeight = 0;

            for (i = 0; i < n; i++)
            {
                if ((subset & (1 << i)) != 0)
                {
                    thisValue += values[i];
                    thisWeight += weights[i];
                }
            }

            if (thisWeight > maxWeight)
                continue;

            if (thisValue > bestValue)
            {
                bestValue = thisValue;
                bestSubset = subset;
            }
        }

        printf("Shopping Spree %d: Max Value %d\n", loop, bestValue);

        for (i = 0; i < n; i++)
        {
            if ((bestSubset & (1 << i)) != 0)
                printf("%d ", i + 1);
        }

        printf("\n");
    }

    return 0;
}