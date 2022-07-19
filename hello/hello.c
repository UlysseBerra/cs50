#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Gets name of user and greets them in standard output
    string name = get_string("What's your name? ");
    printf("hello, %s\n", name);
}