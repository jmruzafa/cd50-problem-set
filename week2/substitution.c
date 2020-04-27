#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//function definition 
bool is_valid_key(char *str);
void error_message(int error_code);
bool is_unique_characters_string(char *str);

int main(int argc, string argv[])
{
    //if user does not provide the "key" stop the program
    if(argc < 2 || argc > 2)
    {
        error_message(1);
        return 1;
    }
    else if (strlen(argv[1]) < 26 || !is_valid_key(argv[1]))
    {
        error_message(2);
        return 1;
    }
    else if (!is_unique_characters_string(argv[1]))
    {
        error_message(3);
        return 1;
    }

    
    //get key to cypher
    char *key = argv[1]; 
    
    //ask the user for the text that will be parsed
    string plaintext = get_string("plaintext: ");
    
    //length of the text
    int len = strlen(plaintext);
    char *ciphertext = malloc(strlen(plaintext) + 1);


    //Checks for the number of letters
    int ascii_code = 0, new_code = 0, position = 0;
    
    for (int i = 0, n = len; i < n; i++)
    {
        //Checks if a character is an alphanumeric character
        if (isalpha(plaintext[i]))
        {
            //choose the base of ASCII code depending if character is upper or lower.
            int base = isupper(plaintext[i]) ? 65 : 97;
            //get actual ascii code
            ascii_code = plaintext[i];

            //look for the relative position in the alphabet
            position = ascii_code - base;

            //letter from our keypass phrase
            char substitute = key[position];
            //get new ascii code remaining capitalized letters
            ciphertext[i] = isupper(plaintext[i]) ? toupper(substitute) : tolower(substitute);
            
        }
        else
        {
            //exclude all no alphanumeric characters 
            ciphertext[i] = plaintext[i];
        }     
    }
    printf("ciphertext: %s\n", ciphertext);
}

bool is_valid_key(char *str)
{
 // loop Through each character in the string
    for(int i = 0, n =  strlen(str); i < n; i++)
    {
        if(!isalpha(str[i])) // Check if a single character "x" its a letter
        {
            return false;  // if its not return false
        } 
    }
    return true; // else return true
}

bool is_unique_characters_string(char *str)
{
    int len = strlen(str);
     // If at any time we encounter 2 
    // same characters, return false 
    for (int i = 0; i < len - 1; i++) { 
        for (int j = i + 1; j < len; j++) { 
            if (str[i] == str[j]) { 
                return false; 
            } 
        } 
    } 
    //no duplication found 
    return true;
}

void error_message(int code_error)
{
    string message = "";
    switch (code_error)
    {
    case 1:
        message = "Usage: ./substitution key";
        break;
    case 2:
        message = "Key must contain 26 characters.";
        break; 
    case 3:
        message = "Key must not contain repeated characters";
        break;
    default:
        message = "Something went wrong. Please, try again";
        break; 
    }
    printf("%s\n", message);  
}