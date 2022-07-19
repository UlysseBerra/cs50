#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long n = get_long("Number: ");
    double first_digit = n;

    while (first_digit >= 10)
    {
        first_digit = n / 10;
    }

    printf("%li", n);
    printf("%f", first_digit);
}