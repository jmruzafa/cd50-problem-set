#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//function definition 
bool is_numeric(string str);

int main(int argc, string argv[])
{
    //if user does not provide the "key" stop the program
    if(argc < 2 || argc > 2 || !is_numeric(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    //get key to cypher
    int rotation = (int) strtol(argv[1], NULL, 10);
    
    //ask the user for the text that will be parsed
    string plaintext = get_string("plaintext: ");
    
    //length of the text
    int len = strlen(plaintext);
    char *ciphertext = malloc(strlen(plaintext) + 1);


    //Checks for the number of letters
    int ascii_code = 0;
    int new_code = 0;

    for (int i = 0, n = len; i < n; i++)
    {
        //Checks if a character is an alphanumeric character
        if (isalpha(plaintext[i]))
        {
            //choose the base of ASCII code depending if character is upper or lower.
            int base = isupper(plaintext[i]) ? 65 : 97;
            //get actual ascii code
            ascii_code = plaintext[i];
            //get new ascii code (if the rotation goes beyond the last letter (Z or z) it returns back to A or a
            new_code = (((ascii_code - base) + rotation) % 26) + base;
            ciphertext[i] = new_code;
        }
        else
        {
            //exclude all no alphanumeric characters 
            ciphertext[i] = plaintext[i];
        }     
    }
    printf("ciphertext: %s\n", ciphertext);
}

bool is_numeric(string str) 
{
    // loop Through each character in the string
    for(int i = 0, n =  strlen(str); i < n; i++)
    {
        if(!isdigit(str[i])) // Check if a single character "x" its a digit
        {
            return false;  // if its not return false
        } 
    }
    return true; // else return true
}