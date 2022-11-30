import cs50

# Get the amount of cents owed
def get_cents():
    cents = 0

    while True:
        cents = cs50.get_int("Change owed: ")

        if cents >= 0:
            break

    return cents

# Find how many quarters
def calculate_quarters(cents):
    quarters = 0

    for j in range(25):
        cents = cents - 25
        quarters +=1

    return quarters

# Find how many dimes
def calculate_dimes(cents):
    dimes = 0

    for k in range(11):
        cents = cents - 10
        dimes += 1

    return dimes

# Find how many nickels
def calculate_nickels(cents):
    nickels = 0

    for l in range(6):
        cents = cents - 5
        nickels += 1

    return nickels

# Find how many pennies
def calculate_pennies(cents):
    pennies = 0

    for m in range(2):
        cents = cents - 1
        pennies += 1

    return pennies

def main():
    # Ask how many cents the customer is owed
    cents = get_cents()

    # Calculate the number of quarters to give the customer
    quarters = calculate_quarters(cents)
    cents = cents - quarters * 25

    # Calculate the number of dimes to give the customer
    dimes = calculate_dimes(cents)
    cents = cents - dimes * 10

    # Calculate the number of nickels to give the customer
    nickels = calculate_nickels(cents)
    cents = cents - nickels * 5

    # Calculate the number of pennies to give the customer
    pennies = calculate_pennies(cents)
    cents = cents - pennies * 1

    # Sum coins
    coins = quarters + dimes + nickels + pennies

    # Print total number of coins to give the customer
    print(coins)

main()