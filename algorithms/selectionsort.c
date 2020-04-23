#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int print_array(int size, int array[]);

int main(void)
{
    int n;
    int list[] = { 6,3, 8, 5, 2, 7, 4, 1};

    int found = -1;
    
    int size = sizeof list / sizeof list[0];
    printf("Initial array:  ");
    print_array(size, list);
    //order the array
    int smallest;
    int tmp;

    printf("progressing....\n");
    //start timer
    clock_t c0 = clock();
    for (int i = 0; i < size; i++)
    {
        smallest = i;
        for (int j = i+1; j < size; j++)
        {
            //look for the smallest one
            if(list[j] < list[smallest])
            {
                smallest = j;
            }
        }
        tmp = list[i];
        list[i] = list[smallest];
        list[smallest] = tmp;
        print_array(size, list);
    }
    //stop timer
    clock_t c2 = clock();
    printf("Ordered array:  ");
    print_array(size, list);
    
    double total_diff_ms = (c2 - c0) * 1000. / CLOCKS_PER_SEC;
    printf("Sorting took %f ms\n", total_diff_ms);
}

int print_array(int size, int array[])
{
    for (int i = 0; i < size; i++)
    {
        i < size-1 ? printf("%i, ", array[i]) : printf("%i", array[i]);
    }
    printf("\n");
    return 0;
}