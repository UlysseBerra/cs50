#include "readability.h"

int main(void)
{
    // gets input from user
    string in = get_string("Text: ");

    // gets values from functions
    int letters = get_letters(in);
    int words = get_words(in);
    int sentences = get_sentences(in);

    // printf("%i\n", letters);
    // printf("%i\n", words);
    // printf("%i\n", sentences);

    // prints out grade level
    float L = ((float)letters / words)*100;
    printf("%f\n", L);
    float S = ((float)sentences / words)*100;
    printf("%f\n", S);
    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    printf("%f\n", index);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    } else if (index >= 16)
    {
        printf("Grade 16+\n");
    } else { printf("Grade %i\n", (int)index); }
}

// finds the number of letters
int get_letters(string in)
{
    int letters = 0;
    int i = 0;

    while (in[i] != '\0')
    {
        if (isalpha(in[i]))
        {
            letters++;
        }
        i++;
    }

    return letters;
}

// finds the number of words
int get_words(string in)
{
    int words = 0;
    int i = 0;

    while (in[i] != '\0')
    {
        if (in[i] == ' ')
        {
            words++;
        }
        i++;
    }

    words++;
    return words;
}

// finds the number of sentences
int get_sentences(string in)
{
    int sentences = 0;
    int i = 0;

    while (in[i] != '\0')
    {
        bool isSentence = (in[i] == '.' || in[i] == '!' || in[i] == '?');
        if (isSentence)
        {
            sentences++;
        }
        i++;
    }

    return sentences;
}