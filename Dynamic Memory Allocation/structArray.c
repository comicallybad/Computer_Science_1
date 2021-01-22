#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define maxNumber 500

struct point
{
    int x;
    int y;
};

void displayPoints(struct point *p, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("point %d = (%d, %d)\n", i, p->x, p->y);
    }
}

struct point *readArray(int n)
{
    struct point *temp = (struct point *)malloc(sizeof(struct point) * n);

    for (int i = 0; i < n; i++)
    {
        temp[i].x = rand() % maxNumber;
        temp[i].y = rand() % maxNumber;
    }
    return temp;
}

int main(void)
{
    srand(time(0));
    int n;
    printf("How many points? ");
    scanf("%d", &n);

    struct point *points = readArray(n);
    displayPoints(points, n);

    free(points);

    return 0;
}