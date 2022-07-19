#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get height from standard input
    int n;

    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // Prints out hashes
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            for (int k = 0; k <= j; k++)
            {
                printf(".");
            }
            printf("#");
        }
        printf("\n");
    }
}