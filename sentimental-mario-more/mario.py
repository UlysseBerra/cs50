def main():
    n: int = 0;

    while True:
        n = int(input("Height:  "));
        if (n >= 1 and n <= 8):
            break;

    for a, i in enumerate(range(n)):
        for b, j in enumerate(range(n - i - 1)):
            print(" ", end='');

        for c, k in enumerate(range(i - 1)):
            print("#", end='');

        for d, l in enumerate(range(2)):
            print(" ", end='');

        for e, k in enumerate(range(i - 1)):
            print("#", end='');

        print("\n");

if __name__ == "__main__":
    main();