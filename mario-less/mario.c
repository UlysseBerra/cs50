#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get height from standard input
    int n;

    while (true)
    {
        n = get_int("Height: ");

        if (n > 1 && n < 8)
        {
            break;
        }
    }

    // Print out newlines
    for (int i = 0; i < n; i++)
    {
        // Print out indentation
        for (int j = 0; j < (n - i - 1); j++)
        {
            printf(" ");
        }

        // Print out hashes for first pyramid
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        printf("\n");
    }
}