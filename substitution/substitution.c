#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool only_alphanum(char c);

int main(int argc, string argv[])
{
    // Test that there is one and only one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Test that key is valid
    string key = argv[1];
    int total_key;
    for (int i = 0; i < strlen(key); i++)
    {
        // contains 26 characters
        if (strlen(key) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        // contains only alphabetic characters
        if (only_alphanum(key[i]) == false)
        {
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }
    }
    // contains each letter exactly once
    int char_rep_count = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        for (int j = 0; j < strlen(key); j++)
        {
            if (tolower(key[i]) == tolower(key[j]))
            {
                char_rep_count++;
            }
        }
    }
    if (char_rep_count != 26)
    {
        printf("Key must contain each letter exactly once.\n");
        return 1;
    }

    // Ask the user for a text string
    string plaintext;
    plaintext = get_string("plaintext:  ");

    // Output ciphertext
    printf("ciphertext: ");

    // Each alphabetical character in the plaintext is substituted with the corresponding character in the key, preserving case and non-alphabetical characters.
    for (int i = 0; i < strlen(plaintext); i++)
    {
        char current_char = plaintext[i];
        if (isupper(current_char))
        {
            int n = (int)current_char - 65;
            char current_key = key[n];
            printf("%c", toupper(current_key));
        }
        else if (islower(current_char))
        {
            int n = (int)current_char - 97;
            char current_key = key[n];
            printf("%c", tolower(current_key));
        }
        else
        {
            printf("%c", current_char);
        }
    }
    printf("\n");
    return 0;
}

// Test if all characters are alphanumeric
bool only_alphanum(char c)
{
    if (isalpha(c) == 0)
    {
        return false;
    }
    return true;
}