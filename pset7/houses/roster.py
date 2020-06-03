import csv
from sys import argv, exit
from cs50 import SQL

# create an array with the house names
houseslist = ["Gryffindor", "Slytherin", "Hufflepuff", "Ravenclaw"]

# check that the script recevies a param with the name file and the name is into the list
if len(argv) != 2 or not argv[1] in houseslist:
    print("Usage: python roster.py house")
    exit(1)

housename = argv[1]
# open the database file
db = SQL("sqlite:///students.db")

# get the list of houses
house = db.execute("SELECT first, middle, last, birth FROM students WHERE house = (?) ORDER BY last, first", housename)

#go through the house getting students' data
for student in house:
    if student["middle"] == None:
        print(student["first"] + " " + student["last"] + ", born " + str(student["birth"]))
    else:
        print(student["first"] + " " + student["middle"] + " " + student["last"] + ", born " + str(student["birth"]))