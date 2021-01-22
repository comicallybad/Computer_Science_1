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

int main(void)
{
    struct point *mypoint = createPoint();

    printf("The point is %d %d", mypoint->x, mypoint->y);

    free(mypoint);

    mypoint = createPoint();

    return 0;
}