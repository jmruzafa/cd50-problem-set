#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //get height value from user
    bool error = true;
    int height = 0;
    //ask until valid height value
    do
    {
        height = get_int("Height: ");
        if (height >= 1 && height <= 8)
        {
            error = false;
        }
    }
    while(error);

    //loop for pyramid height
    for (int i = 1; i <=  height; i++)
    {
        //loop to draw the pyramid blocks
        for (int j =  1;  j <= height + i ; j++)
        {
            if (j > height - i){
                printf("#");
            }
            else{
                printf(" ");
            }
            //if we have finished first side of the pyramid add empty spaces
            if (j == height)
            {
                printf("  ");
            }
        }
        //insert a new line
        printf("\n");
    }
}
