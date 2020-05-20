#!/bin/python3
import cs50
import math

def main():

    # array of coins
    coin_array = [25, 10, 5, 1]

    while True:
        # ask for the change owed
        dollars = cs50.get_float("Change owed: ")
        if dollars >= 0:
            break
    
    # round input to cents 
    cents = round(dollars * 100)
    coins = findCoins(cents, coin_array, 0);


    # recursive function call to get coins amount
    print("", coins);


# recursive function
def findCoins(cents, coin_array, position):
    # get the number of coins of selected
    coins = round (cents // coin_array[position])
    remain = round(cents % coin_array[position])
    
    # this is the condition to exit from recursion
    if remain != 0:
        # call function recursively
        coins += findCoins(remain, coin_array, position +1)
    return coins


main()