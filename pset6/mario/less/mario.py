#!/bin/python3
import cs50

#ask until valid height value
while True:
    height = cs50.get_int("Height: ")
    if height >= 1 and height <= 8:
        break
# loop for pyramid height
for i in range (1, height+1):
    # loop to draw the pyramid blocks
    for base in range (height, 0, -1):
        # print(f"i: {i}, b: {base}")
        if base <= i:
            print("#", end="")
        else:
            print(" ", end="")
    # insert a new line
    print("", end="\n")