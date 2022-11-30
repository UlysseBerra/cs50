def main():
    n: int = 0;

    while True:
        n = input("Height:  ");
        if (n >= 1 and n <= 8):
            break;

    for i in range(n):
        for j in range(n - i - 1):
            print(" ");

        for k in range(i - 1):
            print("#");

        for l in range(2):
            print(" ");

        for k in range(i - 1):
            print("#");

        print("\n");

if __name__ == "__main__":
    main();