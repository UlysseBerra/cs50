#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

string encrypt(string plaintext, int key);

int main(int argc, string argv[])
{
    if (argc != 2 || atoi(argv[1]) <= 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);

    string plaintext = get_string("plaintext:  ");

    string ciphertext = encrypt(plaintext, key);

    printf("ciphertext: %s\n", ciphertext);
}

string encrypt(string plaintext, int key)
{
    if (key > 25)
    {
        key -= 26;
    }

    for (int i = 0; i < strlen(plaintext); i++)
    {
        plaintext[i] += key;
    }

    return plaintext;
}