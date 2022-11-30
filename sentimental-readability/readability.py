from cs50 import *

# finds the number of letters


def get_letters(text_in):
    letters = 0

    for i in text_in:
        if i.isalpha():
            letters += 1

    return letters

# finds the number of words


def get_words(text_in):
    words = 0

    for i in text_in:
        if i == ' ':
            words += 1

    words += 1
    return words

# finds the number of sentences


def get_sentences(text_in):
    sentences = 0

    for c in text_in:
        isSentence = c == '.' or c == '!' or c == '?'
        if isSentence:
            sentences += 1

    return sentences


def main():
    # gets input from user
    text_in = get_string("Text: ")

    # gets values from functions
    letters = get_letters(text_in)
    words = get_words(text_in)
    sentences = get_sentences(text_in)

    # prints out grade level
    L = (float(letters / words)) * 100
    S = (float(sentences / words)) * 100
    index = (0.0588 * L) - (0.296 * S) - 15.8

    # prints index
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {int(round(index))}")


main()