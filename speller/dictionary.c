// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

// Global incrementing variable
int counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int x = hash(word);
    // Iterate over nodes in list
    for (node *ptr = table[x]; ptr != NULL; ptr = ptr->next)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Hash function from reddit
    unsigned long value = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        value += tolower(word[i]);
    }
    return value % N; // N is the number of buckets
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    char *string = malloc(LENGTH + 1);
    if (string == NULL)
    {
        return false;
    }

    unsigned int x;
    // Read strings from file one at a time
    while (fscanf(source, "%s", string) != EOF)
    {
        // Create a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("unable to open %s\n", dictionary);
            return false;
        }

        strcpy(n->word, string);
        n->next = NULL;

        // Hash word to obtain a hash value
        x = hash(n->word);

        // Insert node into hash table at that location
        if (table[x] == NULL)
        {
            table[x] = n;
        }
        else
        {
            // Create linked list
            n->next = table[x];
            table[x] = n;
        }

        // Size counter
        counter++;
    }

    // Close dictionary file
    fclose(source);
    free(string);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int x = 0; x <= N; x++)
    {
        node *ptr = table[x];
        node *tmp = NULL;

        while (ptr != NULL)
        {
            tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
    }
    return true;
}
