# prompt user for input until valid input is given
while True:
    n = int(input("Height: "))
    if n >= 1 and n <= 8:
        break

# print pyramids
for i in range(n):
    print(" " * (n - i - 1), end="")
    print("#" * (i + 1), end="")
    print(" " * 2, end="")
    print("#" * (i + 1))