// includes
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
// defines alphabet length and ASCII numbers for capital and lowercase letters
#define ABL 26
#define ASCIIU 65
#define ASCIIL 97


string encrypt(string plaintext, int key);

int main(int argc, string argv[])
{
    // if incorrect number of args
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string keystring = argv[1];

    // test if char is digit
    for (int i = 0; i < strlen(keystring); i++)
    {
        if (!isdigit(keystring[i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int key = atoi(argv[1]);

    string plaintext = get_string("plaintext:  ");

    string ciphertext = encrypt(plaintext, key);

    printf("ciphertext: %s\n", ciphertext);
}

// encrypts
string encrypt(string plaintext, int key)
{
    string ciphertext = plaintext;

    // rotates alphabet
    for (int j = 0; j < strlen(plaintext); j++)
    {
        if (isupper(ciphertext[j]))
        {
            ciphertext[j] = ((ciphertext[j] - ASCIIU + key) % ABL) + ASCIIU;
        }
        else if (islower(ciphertext[j]))
        {
            ciphertext[j] = ((ciphertext[j] - ASCIIL + key) % ABL) + ASCIIL;
        }
        // idk if there's a pass keyword in C so this is it
        else
        {
            NULL;
        }
    }

    return ciphertext;
}