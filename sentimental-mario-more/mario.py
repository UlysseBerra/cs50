def main():
    # Get height from standard input
    n = 0

    while True:
        n = int(input("Height: "))

        if n >= 1 and n <= 8:
            break

    # Print out newlines
    for a, i in enumerate(range(0, n, 1)):
        # Print out indentation
        for b, j in enumerate(range(0, n - i - 1, 1)):
            printf(" ");

        // Print out hashes for first pyramid
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        // Print out spacing in between pyramids
        for (int l = 0; l < 2; l++)
        {
            printf(" ");
        }

        // Print out hashes for second pyramid
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        printf("\n");
    }
}