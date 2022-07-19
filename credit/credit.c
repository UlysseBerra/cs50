#include <cs50.h>
#include <stdio.h>

bool luhn(long n);

int main(void)
{
    long n = get_long("Number: ");

    if (luhn(n) == false)
    {
        printf("INVALID\n");
    }
}

bool luhn(long n)
{
    
    bool result;
    return result;
}

