#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selection_sort(int list[], int size);
void swap(int *ap, int *bp);
int print_array(int size, int array[]);

int main(void)
{
    int n;
    int list[] = { 6,3, 8, 5, 2, 7, 4, 1};

    int found = -1;
    
    int size = sizeof list / sizeof list[0];
    printf("Initial array:  ");
    print_array(size, list);

    //start timer
    clock_t c0 = clock();

    //order the array
    printf("sorting....\n");
    selection_sort(list, size);
    
    //stop timer
    clock_t c2 = clock();
    printf("Ordered array:  ");
    print_array(size, list);
    
    double total_diff_ms = (c2 - c0) * 1000. / CLOCKS_PER_SEC;
    printf("Sorting took %f ms\n", total_diff_ms);
}

void selection_sort(int list[], int size)
{
    int smallest;
    
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
        swap(&list[i], &list[smallest]);
        print_array(size, list);
    }
}
void swap(int *ap, int *bp) 
{ 
    //swap the pointer to each value and that's all :D
    int temp = *ap; 
    *ap = *bp; 
    *bp = temp; 
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