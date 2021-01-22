#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define maxNumber 500

struct point
{
    int x;
    int y;
};

struct point *createPoint()
{
    struct point *p = (struct point *)malloc(sizeof(struct point));
    p->x = rand() % 100;
    p->y = rand() % 100;

    return p;
}

struct point **createPA(int n)
{
    struct point **pa = malloc(n * sizeof(struct point *));

    for (int i = 0; i < n; i++)
    {
        pa[i] = createPoint();
        pa[i]->x = rand() % 100;
        pa[i]->y = rand() % 100;
    }
    return pa;
}

int main(void)
{
    int n;

    printf("How many points?");
    scanf("%d", &n);

    struct point **mypoints = createPA(n);

    for (int i = 0; i < n; i++)
    {
        printf("Point %d = (%d, %d)", i, mypoints[i]->x, mypoints[i]->y);
    }

    for (int i = 0; i < n; i++)
    {
        free(mypoints[i]);
    }

    free(mypoints);

    return 0;
}