import cs50


def main():

    # Ask the user for a card number
    n = cs50.get_string("Card number to check: ")

    # Check that the number of digits matches valid card numbers
    # American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers
    n_length = len(n)
    print("n_length : " + str(n_length))

    if (n_length != 13 and n_length != 15 and n_length != 16):
        print("INVALID")

    # If the number is valid, proceed to analyse its digits and compute checksum
    else:
        checksum = 0

        # Even card numbers
        if (n_length % 2 == 0):
            # For "even" digits, multiply every other digit by 2
            checksum_even_str = ""
            for i in reversed(range(0, n_length, 2)):
                current_digit = int(n[i])
                checksum_even_str = checksum_even_str + (str(current_digit * 2))
            # Add those products' digits together: do the sum of their digits, not of their values
            checksum_even = 0
            for j in checksum_even_str:
                checksum_even = checksum_even + int(j)

            # For "odd" digits, do a simple sum
            checksum_odd = 0
            for i in reversed(range(1, n_length, 2)):
                current_digit = int(n[i])
                checksum_odd = checksum_odd + current_digit

        # Odd card numbers
        else:
            # For "even" digits, multiply every other digit by 2
            checksum_even_str = ""
            for i in reversed(range(1, n_length, 2)):
                current_digit = int(n[i])
                checksum_even_str = checksum_even_str + (str(current_digit * 2))
            # Add those products' digits together: do the sum of their digits, not of their values
            checksum_even = 0
            for j in checksum_even_str:
                checksum_even = checksum_even + int(j)

            # For "odd" digits, do a simple sum
            checksum_odd = 0
            for i in reversed(range(0, n_length, 2)):
                current_digit = int(n[i])
                checksum_odd = checksum_odd + current_digit

        # Compute total checksum, adding partial checksums
        checksum = checksum_odd + checksum_even

        # Select digits of checksum which will be tested
        last_digit_checksum = int(str(checksum)[len(str(checksum))-1])
        first_digit_n = int(n[0])
        second_digit_n = int(n[1])

        # Check if the number is valid, i.e. if the total's last digit is 0
        if (last_digit_checksum == 0):

            # If a valid number starts with 4, identify the card as a Visa
            if (first_digit_n == 4):
                print("VISA")

            # If a valid number starts with 34 or 37, identify the card as an American Express
            elif (first_digit_n == 3 and (second_digit_n == 4 or second_digit_n == 7)):
                print("AMEX")

            # If a valid number starts with 51, 52, 53, 54, or 55, identify the card as a MasterCard
            elif (first_digit_n == 5 and (second_digit_n == 1 or second_digit_n == 2 or second_digit_n == 3 or second_digit_n == 4 or second_digit_n == 5)):
                print("MASTERCARD")

            # Declare the number invalid if the first digits of a valid number are not the ones expected for these card providers
            else:
                print("INVALID")

        # Declare the number invalid if the total's last digit is not 0
        else:
            print("INVALID")

    return 0


if __name__ == "__main__":
    main()