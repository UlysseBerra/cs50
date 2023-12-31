#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// points assigned to each letter of the alphabet
const int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // print out result
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// compute the scores
int compute_score(string word)
{
    int score = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        char current_char = tolower(word[i]);
        int current_int = (int)current_char - 97;
        score += POINTS[current_int];
    }
    return score;
}