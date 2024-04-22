import cs50
import csv
from sys import argv, exit


def main():
    # number of arguments
    argc = len(argv)

    # dna sequence
    dna = ""

    # result dicctionary of STRs
    results = {}

    # if there aren't two params with data and sequence then exit
    if argc != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # get data file path + name
    dbfilename = argv[1]
    # get sequence file path + name
    secfilename = argv[2]

    # if they don't fit the expected extension then exit
    if dbfilename.find(".csv") == -1 or secfilename.find(".txt") == -1:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # open the files
    dbfile = open(dbfilename, "r")
    if dbfile:
        database = csv.reader(dbfile)
    else:
        exit(1)

    # open sequence file and read them all
    seqfile = open(secfilename, "r")
    if seqfile:
        dna = seqfile.read()
    else:
        exit(1)

    # get the header (sequences)
    # and calculate the SRTs in the DNA
    fieldnames = next(database)
    for strs in fieldnames[1:]:
        results[strs]= numberofstrs(dna, strs)

    # result
    match = "No match"

    # conver result dic into a list of values to compare with user db
    strslist = list(results.values())
    
    # iterate the users database
    for row in database:
        # number of coincidences
        coincidence = 0 

        # the list of results
        for i in range (len(strslist)):
            if int(row[i + 1]) == int(strslist[i]):
                coincidence += 1  
        # after each iteration we look for the amount of coincidences. If it's equals to the total of results we found a match
        if coincidence == len(strslist):
            # getting name of the match
            match =  row[0]
            break
    print(match)
    exit(0)


def numberofstrs(dna, sequence):

    # get the dna total length     
    dnalen = len(dna)
    # sequence length
    seqlen = len(sequence)
    # flag
    found = 0
    #counter
    maxconsecutive = 0

    #find the first sequence in the DNA
    pos = dna.find(sequence)

    # if we found someting we go through the DNA looking for the STRs
    while pos <= dnalen and pos != -1:
        # we examine 'chunks' of DNA adding the length of the sequence we are looking for
        if dna[pos: pos + seqlen] == sequence:
            # we found the sequence
            found += 1  
            # move the cursor to the next chunk of DNA (increase the sequence length)
            pos += seqlen
            if found > maxconsecutive:
                # if the found chunks are bigger than in the previous range we increase to get the max of STRs
                maxconsecutive = found 
        else:
            # there's no found sequence so we restart the flag
            found = 0
            # find for the next ocurrence in the DNA starting from last position
            pos = dna.find(sequence, pos)

    return maxconsecutive


main()
