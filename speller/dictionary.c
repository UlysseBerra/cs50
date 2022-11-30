#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// creates node type for hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// word counter
int word_count = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 250000;

// hash table
node *table[N];

// true if word in dictionary, else false
bool check(const char *word)
{
    // add word to bucket
    int bucket = hash(word);

    // put bucket index in checker node
    node *checker = table[bucket];

    while (checker != NULL)
    {
        /* check, i.e. compare word with content of bucket
         * using case-insensitive function strcasecmp
         */
        if (strcasecmp(checker->word, word) == 0)
        {
            return true;
        }
        checker = checker->next;
    }
    return false;
}

// hash word to number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // returns toupper(word[0]) - 'A';
    unsigned int hashing = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hashing = (hashing << 2) ^ tolower(word[i]);
    }
    return hashing % N;
}

// loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open and read dictionary
    FILE *dict = fopen(dictionary, "r");

    // check if dictionary opens
    if (dict == NULL)
    {
        return false;
    }

    // allocate memory for input string, i.e. word, from dictionary
    char *string = malloc(LENGTH + 1);

    // iterate through dictionary to read each string
    while (fscanf(dict, "%s", string) != EOF)
    {
        // create new node
        node *new_node = malloc(sizeof(node));

        // copy string into new node "word" member
        strcpy(new_node->word, string);

        // hash string
        int hashed = hash(string);

        // if new node belongs at head, prepend
        // and specify pointer to next is null
        if (table[hashed] == NULL)
        {
            table[hashed] = new_node;
            new_node->next = NULL;
        }

        // else new node belongs in the middle or at the end
        else
        {
            new_node->next = table[hashed];
            table[hashed] = new_node;
        }

        // increment word count to keep track of dictionary size
        word_count++;
    }

    // prevent memory leak
    free(string);

    // close dictionary
    fclose(dict);

    return true;
}

// returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0)
    {
        return word_count;
    }
    else
    {
        return 0;
    }
}

// unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        // initialize cursor
        node *cursor;

        // put cursor in table head
        cursor = table[i];

        // iterate through table and free temporary nod
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }

        // clean the table
        table[i] = NULL;
    }
    return true;
}
