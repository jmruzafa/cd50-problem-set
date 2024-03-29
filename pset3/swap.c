#include <stdio.h>
#include <stdlib.h>

void swap (int *a, int *b);

int main (void)
{
    int x = 4, y = 8;

    printf("x: %i, y: %i\n", x, y);
    swap(&x, &y);
    printf("x: %i, y: %i\n", x, y);
}

void swap (int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}