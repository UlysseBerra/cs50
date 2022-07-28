#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

string encrypt(string plaintext);

int main(int argc, string argv[])
{
    int key = atoi(argv[1]);

    if (argvc || key <= 0 || argv[2] != '\0')
    {
        printf("Usage: ./caesar [key]");
        return 1;
    }

    encrypt()
}

string encrypt(string plaintext, int key)
{

}