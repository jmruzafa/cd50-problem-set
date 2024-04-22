#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    //ask the user for the text that will be parsed
    string text = get_string("Text: \n");
    
    //length of the text
    int len = strlen(text);

    //initialise some variables
    int letters = 0, sentences = 0, words = 0;

    //Checks for the number of letters
    for (int i = 0, n = len; i <= n; i++)
    {
        //Checks if a character is an alphanumeric character
        if (isalpha(text[i]))
        {
            letters++;
        }
        //Checks if a character is a space
        else if (isspace(text[i]) || text[i] == '\0')
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    printf("%i letters, %i words, %i sentences\n", letters, words, sentences);
    //calculate L & S of Coleman-Liau index
    //to be precised we must cast the integers into floats first
    float L = (float)letters / (float)words * 100.00;
    float S = (float)sentences / (float)words * 100.00;

    //calculate the index of readability of Coleman-Liau.
    //the formula is: index = 0.0588 * L - 0.296 * S - 15.8
    int index = round(0.0588 * L - 0.296 * S - 15.8); 

    string grade = "Grade";
    //if grade is between 1 and 16 
    if (index >= 1 && index <=16)
        printf("%s %i\n", grade, index);
    //index is higher that 16
    else if (index > 16)
        printf("%s 16+\n", grade);
    //grade index below 1
    else
        printf("Before Grade 1\n");
}

