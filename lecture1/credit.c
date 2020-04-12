#include<stdio.h>
#include <cs50.h>
#include <math.h>

void get_digits_array(int* digits, long number);

int main(void)
{
    string result = "INVALID";
    bool error = true;
    // ask for credit card number
    long creditcard = 0;
    do
    {
        creditcard = get_long("Number: ");
        if(creditcard > 0)
        {
        error = false;
        }
    }
    while(error);

    //get the number of digits in the credit card
    int length = (int) (floor(log10(creditcard)) + 1);
    int digits[length];
    //get an array of digits
    get_digits_array(digits, creditcard);

    //extract the control digit
    int sum = digits[length-1];

    //parity to know whic are the digits to multiply
    int parity = length % 2;

    //iterate through digits of the card to calculate
    for (int i = 0; i < length - 1; i++)
    {
        int digit = digits[i];
        //multiply every other digit by 2
        if (i % 2 == parity)
        {
        digit = digit * 2;
        }
        if (digit > 9)
        {
        digit = digit - 9;
        }
        sum += digit;
    }
    //this is another way to calcultate the control digit.
    /*The check digit (x) is obtained by computing the sum of the other digits (third row) then subtracting the units digit from 10 */
    if (sum % 10 == 0)
    {
        //extract the two first digits to know which is the issuer along wiht length
        int first_digit = digits[0];
        int second_digit = digits[1];
        if(length == 15 && first_digit == 3 && (second_digit == 4 || second_digit == 7))
        {
            result = "AMEX";
        }
        else if(length == 16 && first_digit == 5 &&
            (second_digit == 1 || second_digit == 2 || second_digit == 3 || second_digit == 4 || second_digit == 5))
        {
            result = "MASTERCARD";
        }
        else if((length == 13 || length == 16) && first_digit == 4)
        {
            result = "VISA";
        }

    }
    printf("%s\n", result);
}

void get_digits_array(int *digits, long number)
{
    long temp,factor = 1;
    temp=number;
    while(temp)
    {
        temp = temp / 10;
        factor = factor * 10;
    }
    int i = 0;
    while(factor > 1)
    {
        factor = factor / 10;
        digits[i] = (int)(number / factor);
        number = number % factor;
        i++;
    }
}
