#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int print_array(int array[], int size);
int binary_search(int list[], int start, int end, int key);

clock_t c1,c2;
int main(void)
{
    int n;
    int list[] = {1,2,4,5,6,7,9,12};
    int found = -1;
    int pos = 0;
    

    printf("Type your number: ");
    scanf("%d", &n);
    
    int size = sizeof list / sizeof list[0];
    print_array(list, size);
    
    //start timer
    clock_t c0 = clock();
    found = binary_search(list, 0, size-1, n);

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

int binary_search(int list[], int start, int end, int key)
{
    //loop while start is still lower that end point
    while (start <= end)
    {
        int mid = (start + end) / 2;
        printf("start: %i, end: %i, mid: %i. Value: %i\n", start, end, mid, list[mid]);
        if (list[mid] == key)
        {
            c1 = clock();
            return 0;
        }
        else if (key < list[mid])
        {
            //shorten the range and start again (recursive candidate)
            return binary_search(list, start, mid - 1, key); 
        }
        else
        {
            //look for the value on the other side 
            return binary_search(list, mid + 1, end, key);
        }
    }
    return -1;
}
int print_array(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        i < size-1 ? printf("%i, ", array[i]) : printf("%i", array[i]);
    }
    printf("\n");
    return 0;
}