n = 0

while True:
    n = int(input("Height: "))

    if n >= 1 and n <= 8:
        break

for i in range(n):
    print(" " * (n - i - 1))