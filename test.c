#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char S1[6] = "cat", S2[10] = "red";
    strcat(S1, S2);
    printf("%s", S2);
    return 0;
}