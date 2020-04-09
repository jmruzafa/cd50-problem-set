#include <stdio.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("arguments error on command line; only %i arguments.\n", argc);
        return -1;
    }
    printf("Hello, %s\n", argv[1]);
    printf("Argument number: %i\n", argc);
}