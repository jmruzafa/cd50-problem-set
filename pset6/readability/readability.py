import cs50


def main():
    # ask the user for the text to be parsed
    text = cs50.get_string("Text: ")

    # length of the string
    length = len(text)

    # initialise some variables
    letters = 0
    sentences = 0
    words = len(text.split(" "))

    # check for the number of letters
    for i in range(0, length):
        # check if character is alphanumeric
        if text[i].isalnum():
            letters += 1
        # check if character is a space
        # elif text[i].isspace() or text[i] == "\0":
        #     words += 1
        elif text[i] == "." or text[i] == "!" or text[i] == "?":
            sentences += 1

    # calculate L & S of Coleman-Liau index
    # to be precised we must cast the integers into floats first
    L = float(letters) / float(words) * 100.00
    S = float(sentences) / float(words) * 100.00

    # calculate the index of readability of Coleman-Liau.
    # the formula is: index = 0.0588 * L - 0.296 * S - 15.8
    index = round(0.0588 * L - 0.296 * S - 15.8)

    grade = "Grade"
    # if grade is between 1 and 16
    if index >= 1 and index <= 16:
        print(f"{grade} {index}")
    # index is higher that 16
    elif index > 16:
        print(f"{grade} 16+")
    # grade index below 1
    else:
        print("Before Grade 1")


main()
