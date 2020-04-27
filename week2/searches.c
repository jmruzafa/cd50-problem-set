#include <stdio.h>
#include <cs50.h>

int main(void)
{
    bool error = true;
    printf("What kind of search do you want to use?\n");
    do
    {
        //this program implements different searches algorithms
        int search = get_int(" 1.- lineal, 2.- binary:  ");
        if(search == 1 || search == 2)
            error = false;
            
            
    }
    while(error);
}
