#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertion_sort(int list[], int size);
int print_array(int size, int array[]);

int main(void)
{
    int n;
    int list[] = { 4,3, 2, 10, 12, 1, 5, 6};
    
    int size = sizeof list / sizeof list[0];
    printf("Initial array:  ");
    print_array(size, list);

    //start timer
    clock_t c0 = clock();

    //order the array
    printf("sorting....\n");
    insertion_sort(list, size);
    
    //stop timer
    clock_t c2 = clock();
    printf("Ordered array:  ");
    print_array(size, list);
    
    double total_diff_ms = (c2 - c0) * 1000. / CLOCKS_PER_SEC;
    printf("Sorting took %f ms\n", total_diff_ms);
}

void insertion_sort(int list[], int size)
{
    int tmp, j;
    
    for (int i = 0; i < size; i++)
    {
        tmp = list[i];
        j = i;
        while (j > 0 && tmp < list[j-1])
        {
           list[j] = list[j-1];
           j = j -1;
        } 
        print_array(size, list);   
    }
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