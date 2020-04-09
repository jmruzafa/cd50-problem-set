#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //get height value from user
    bool error = true;
    int height = 0;
    //ask until valid height value
    while (error)
    {
        height = get_int("Height: ");
        if (height >= 1 && height <= 8)
        {
            error = false;
        }
    }
    //loop for pyramid height
    for (int i = 1; i <= height; i++)
    {
        //loop to draw the pyramid blocks
        for (int base = height-1; base >= 0 ; base--)
        {
            if(base < i){
                printf("#");
            }
            else{
                printf(" ");
            }
        }
        //insert a new line
        printf("\n");
    }
}
