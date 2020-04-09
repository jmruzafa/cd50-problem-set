#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <cs50.h>

int main()
{
    int l = get_char("Input letter: ");
    int k = get_int("Input key: ");
    int ac = (int)l;
    int nc = ((ac - 65) + k) % 26;
    printf("ciphered relative position %i\n", nc);
    printf("cipher ASCII code: %d, letter: %c\n", 65 + nc, (char)(65+nc));


    /* for (int i = 65; i <= 117; i++)
    {
        printf("%c ", i);
    } 
    printf("\n"); */
    return 0;
}