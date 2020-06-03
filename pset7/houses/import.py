import cs50
import csv
from sys import argv, exit
from cs50 import SQL


# number of arguments
argc = len(argv)

# if there aren't two params with data and sequence then exit
if argc != 2:
    print("Usage: import.py characters.csv")
    exit(1)

# get data file path + name
fname = argv[1]

# if they don't fit the expected extension then exit
if not fname.endswith(".csv"):
    print("Usage: import.py characters.csv")
    exit(1)

# connect to db file
studentsdb = SQL("sqlite:///students.db")
# open the files
with open(fname, "r") as characters:
    
    dic = csv.DictReader(characters, delimiter=",")
    for row in dic:

        name = row["name"]
        name_list = name.split()

        if len(name_list) == 2:
            first_name = name_list[0]
            last_name = name_list[1]
            studentsdb.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                    first_name, None, last_name, row["house"], row["birth"])
        elif len(name_list) == 3:
            first_name = name_list[0]
            middle_name = name_list[1]
            last_name = name_list[2]
            studentsdb.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                    first_name, middle_name, last_name, row["house"], row["birth"])

        


