from cs50 import *

# finds the number of letters
def get_letters(text_in):
    letters = 0
    i = 0

    while text_in[i] != '\0':
        if text_in[i].isalpha():
            letters += 1
        i += 1

    return letters

# finds the number of words
def get_words(text_in):
    words = 0
    i = 0

    while text_in[i] != '\0':
        if text_in[i] == ' ':
            words += 1
        i += 1

    words += 1
    return words

# finds the number of sentences
def get_sentences(text_in):
    sentences = 0
    c = 0

    while text_in[c] != '\0':
        isSentence = text_in[c] == '.' or text_in[c] == '!' or text_in[c] == '?'
        if isSentence:
            sentences += 1
        c += 1

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

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {int(round(index))}")

main()