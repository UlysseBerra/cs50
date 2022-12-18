#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask the user for a card number
    long n;
    n = get_long("Card number to check: ");
    long n_test = n;

    // Check that the number of digits matches valid card numbers
    // American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers
    int n_length = 0;
    while (n_test > 0)
    {
        n_test = (n_test / 10);
        n_length = n_length + 1;
    }
    if (n_length != 13 && n_length != 15 && n_length != 16)
    {
        printf("INVALID\n");
    }
    // If the number is valid, proceed to analyse its digits and compute checksum
    else
    {
        long checksum;
        long checksum_odd;
        long checksum_even;
        int i = 1, current_digit = 0;
        long n_test_2 = n;
        for (i = 1; i < n_length + 1; i++)
        {
            current_digit = n_test_2 % 10;
            n_test_2 = n_test_2 / 10;
            // Multiply every other digit by 2 starting with the second-to-last digit
            // Deal with these "even" digits, i.e. every other digit starting with the second-to-last digit
            if (i % 2 == 0)
            {
                int current_checksum_even;
                current_checksum_even = (current_digit * 2);
                // Add those products' digits together: do the sum of their digits, not of their values
                // Dealing first with 2-digit numbers: separate first and second digits, then add them together
                int current_checksum_even_length = 0;
                if (current_checksum_even > 9)
                {
                    current_checksum_even = (current_checksum_even / 10) + current_checksum_even % 10;
                    checksum_even = checksum_even + current_checksum_even;
                }
                // Then dealing with 1-digit numbers: do a simple sum
                else
                {
                    checksum_even = checksum_even + current_checksum_even;
                }
            }
            // Do the sum of "odd" digits, i.e. every other digit starting with the last digit, without multiplying them by 2
            else
            {
                checksum_odd = checksum_odd + current_digit;
            }
        }
        // Compute total checksum, adding partial checksums
        checksum = checksum_odd + checksum_even;

        // If the total's last digit is 0, the number is valid
        if (checksum % 10 == 0)
        {
            long first_digit = n;
            long second_digit = n;
            while (first_digit >= 10)
            {
                first_digit = first_digit / 10;
                printf("first_digit : %ld\n", first_digit);
            }
            while (second_digit >= 100)
            {
                second_digit = second_digit / 10;
                printf("second_digit : %ld\n", second_digit);
            }
            second_digit = second_digit % 10;
            printf("second_digit : %ld\n", second_digit);

            // If numbers start with 4, identify the card as a Visa
            if (first_digit == 4)
            {
                printf("VISA\n");
            }
            // If numbers start with 34 or 37, identify the card as an American Express
            else if (first_digit == 3 && (second_digit == 4 || second_digit == 7))
            {
                printf("AMEX\n");
            }
            // If numbers start with 51, 52, 53, 54, or 55, identify the card as a MasterCard
            else if (first_digit == 5 &&
                     (second_digit == 1 ||
                      second_digit == 2 ||
                      second_digit == 3 ||
                      second_digit == 4 ||
                      second_digit == 5))
            {
                printf("MASTERCARD\n");
            }
            // If the first digits are not the expected ones, declare the number invalid
            else
            {
                printf("INVALID\n");
            }
        }
        // If the total's last digit is not 0, declare the number invalid
        else
        {
            printf("INVALID\n");
        }
    }
}