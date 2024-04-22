#!/bin/python3
import cs50
import math

def main():
    # message
    result = "INVALID"
    
    while True:
        # ask for the change owed
        creditcard = cs50.get_int("Number: ")
        if creditcard >= 0:
            break
    # get the lenght of the CC number (easier in pyhton than C)
    # it could be done using this math calculation:
    # length = int(math.log10(creditcard))+1 
    # or simply getting the string (an array in fact)
    digits = str(creditcard)
    length = len(digits) 
    # because we got the number as integer but in Python it is a string by default
        
    # control digit 
    sum = int(digits[-1])
    
    # parity to know which are the digits to multiply
    parity = length % 2

    # now we can iterate through digits of the credit card but the last one (control)
    for i in range (length-1):
        
        #extract the digit
        digit = int(digits[i])
        #check if it equals to parity
        if i % 2 == parity:
            digit = digit * 2
        # if we go over 9 we need to get the sum of both ( x * 2 = y > 9 => x + y)
        if digit > 9:
            digit -= 9
        sum += digit
    
    # this is another way to calcultate the control digit.
    # the check digit (x) is obtained by computing the sum of the
    # digits (third row) then subtracting the units digit from 10  
    if sum % 10 == 0:
        first_digit = int(digits[0])
        second_digit = int(digits[1])
        if (length == 15 and first_digit == 3 and (second_digit == 4 or second_digit == 7)):
            result = "AMEX"
        elif (length == 16 and first_digit == 5 and
            (second_digit == 1 or second_digit == 2 or second_digit == 3 or second_digit == 4 or second_digit == 5)):
            result = "MASTERCARD"
        elif ((length == 13 or length == 16) and first_digit == 4):
            result = "VISA"
    print(f"{result}")


def getDigitsArray(digits, number):
    
    factor = 1
    temp = number
    while temp != 0:
        temp = temp / 10
        factor = factor * 10
    i = 0
    while factor > 1:
        factor = factor / 10
        digits[i] = number // factor
        number = number % factor
        i += 1

main()