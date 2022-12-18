#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask the user for an integer (1 to 8 inclusive)
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // For each row
    for (int i = 0; i < n; i++)
    {
        // For each column
        // Print required spaces
        for (int j = 0; j < ((n - i) - 1); j++)
        {
            printf(" ");
        }
        // Print hashtags required
        for (int k = 0; k < (i + 1); k++)
        {
            printf("#");
        }
        // Go to next line
        printf("\n");
    }
}