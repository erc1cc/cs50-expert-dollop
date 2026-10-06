// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 200003;

// Hash table
node *table[N];

unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int index = hash(word);
    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long hash = 0;
    int i = 0;

    while (word[i] != '\0')
    {
        hash = (hash * 31) + tolower(word[i]);
        i++;
    }

    return (hash % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    // Read each word in the file
    while (fscanf(source, "%s", word) != EOF) // EOF means End Of File
    {
        // Create space for a new hash table node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Copy the word into the new node
        strcpy(n->word, word);
        n->next = NULL;

        // Hash the word to obtain its hash value
        unsigned int index = hash(word);

        // Insert the new node into the hash table (using the index specified by its hash value)
        n->next = table[index];
        table[index] = n;

        word_count++;
    }

    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

        table[i] = NULL;
    }
    return true;
}
