#include "readability.h"

int main(void)
{
    string in = get_string("Text: ");

    int letters = get_letters(in);
    int words = get_words(in);
    int sentences = get_sentences(in);

    printf("%i\n", letters);
    printf("%i\n", words);
    printf("%i\n", sentences);

    float L = (float) (letters / words)*100;
    printf("%f\n", L);
    float S = (float) (sentences / words)*100;
    printf("%f\n", S);
    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    printf("%f\n", index);

    printf("Grade %f\n", index);
}

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