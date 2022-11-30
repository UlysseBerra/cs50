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
            print(" ", end="")

        # Print out hashes for first pyramid
        for c, k in enumerate(range(0, i - 1, 1)):
            print("#", end="")

        # Print out spacing in between pyramids
        for d, l in enumerate(range(0, 2, 1)):
            print(" ", end="")

        # Print out hashes for second pyramid
        for e, k in enumerate(range(0, i - 1, 1)):
            print("#", end="")

        print("\n")