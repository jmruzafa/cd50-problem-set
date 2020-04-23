#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int n;
    int list[] = {1,2,4,5,6,7,9,12};
    int found = -1;
    int pos = 0;
    clock_t c1;
    printf("Input your number: ");
    scanf("%d", &n);

    printf("El array está formado por ");
    
    int size = sizeof list / sizeof list[0];
    //start timer
    clock_t c0 = clock();
    for (int i = 0; i < size; i++)
    {
        printf("%i, ", list[i]);    
        if (n == list[i])
        {
            c1 = clock();
            
            found = 0;
            pos = i+1;
        }
    }
    //stop timer
    clock_t c2 = clock();
    double found_diff_ms = (c1 - c0) * 1000. / CLOCKS_PER_SEC;
    double total_diff_ms = (c2 - c0) * 1000. / CLOCKS_PER_SEC;
    printf("\n");
    if(found == 0)
    {
        printf("Your number was found!: %i, in the %ith position in %f ms\n", n, pos, found_diff_ms);
    }
    else
    {
        printf("Your number was not found!\n");
    }
    printf("Search took %f ms\n", total_diff_ms);
}