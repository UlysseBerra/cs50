import cs50


def main():

    # Get value for height
    print('You will be asked for a number (1 to 8)')
    print('for the height of your half-pyramid.')
    height = 0

    # asking for value as long as input is not in required range
    while height not in range(1, 9):
        height = cs50.get_int('Height: ')

    # Print half-pyramid
    # by adding spaces and blocks until height is reached
    for row in range(1, height + 1):
        for spaces in range((height - row - 1), -1, -1):
            print(' ', end='')
        for blocks in range(0, (row - 1)):
            print('#', end='')
        print('#')
    return 0


if __name__ == "__main__":
    main()
