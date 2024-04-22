#!/bin/python3
import cs50

#ask until valid height value
while True:
    height = cs50.get_int("Height: ")
    if height >= 1 and height <= 8:
        break

# loop for pyramid height
for h in range (0, height):

    # loop to draw the pyramid blocks
    for b in range (0, height + 1 + h):
        
        # empty spaces until the base = height - 1 - current height
        if b >= height - 1 - h:
            print("#", end = "")
        else:
            print(" ", end = "")
        # if we have finished first side of the pyramid add empty spaces
        if b == height - 1:
            print("  ", end = "")
    
    # insert a new line
    print("", end="\n")