#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int n;
    int list[] = {1,2,4,5,6,7,9,12};
    int found = -1;
    int pos = 0;
    clock_t c1 = clock(); 
    clock_t c2 = clock();

    printf("Type your number: ");
    scanf("%d", &n);
    
    int size = sizeof list / sizeof list[0];
    int mid = size % 2;
    
    //start timer
    clock_t c0 = clock();

    if (list[mid] == n)
    {
        found = 0;
    }
    else if (n < list[mid])
    {
        for (int i = 0; i < mid; i++)
        {   
            if (n == list[i])
            {
                //stop timer
                c1 = clock();
                found = 0;
            }
        }
    }
    else if (n > list[mid])
    {
        for (int i = mid; i < size; i++)
        {    
            if (n == list[i])
            {
                //stop timer
                c1 = clock();
                found = 0;
            }
        }
    }
    
    printf("\n");
    
    c2 = clock();
    double found_diff_ms = (c1 - c0) * 1000. / CLOCKS_PER_SEC;
    double total_diff_ms = (c2 - c0) * 1000. / CLOCKS_PER_SEC;

    if(found == 0)
    {
        printf("Your number was found! in %f ms\n", found_diff_ms);
    }
    else
    {
        printf("Your number was not found!\n");
    }
    printf("Search took in total: %f ms\n", total_diff_ms);
}