#include <cs50.h>
#include <stdio.h>

bool isInvalid(long n);

int main(void)
{
    long n = get_long("Number: ");
    isInvalid(n);
}

bool isInvalid(long n)
{
    printf("%li\n", (n%100)-((n%100)%10));
    return true;
}