// Implements a dictionary's functionality

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

node *add_node(node *p, char *word);
node *remove_node (node *p);

// Number of buckets in hash table
const unsigned int HASH_T_SIZE = 100;

// Number of words in dicctionary
unsigned long words_counter = 0;

// Hash table
node *hash_table[HASH_T_SIZE];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // String to lowercase
    char term[strlen(word) + 1];
    strcpy(term, word);
    for (int i = 0; i < strlen(word); i++)
    {
        term[i] = tolower(word[i]);
    }

    // Get the hash value for a word
    int hash_value = hash(term) % HASH_T_SIZE;

    node *dict = hash_table[hash_value];

    // Iterate the list
    while (dict != NULL)
    {
        if (strcasecmp(dict->word, word) == 0)
        {
            return true;
        }
        // Move list pointer
        dict = dict->next;
    }

    return false;
}

// Hashes word to a number..
unsigned int hash(const char *word)
{
    //djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    words_counter = 0;

    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Allocate memory
    char *word = malloc(sizeof(char) * LENGTH);

    while (fscanf(file, "%s", word) != EOF)
    {
        // Add words to hash table
        int hash_value = hash(word) % HASH_T_SIZE;
        // Iterate over dictionary
        hash_table[hash_value] = add_node(hash_table[hash_value], word);
        words_counter++;
    }

    // Free allocated memory
    free(word);

    // Close dictionary
    fclose(file);

    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Counter
    return words_counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Iterate over hash table
    for (int i = 0; i < HASH_T_SIZE; i++)
    {
        // Remove linked list connected to the pointer
        while (hash_table[i] != NULL)
        {
            hash_table[i] = remove_node(hash_table[i]);
        }
    }

    return true;
}


// Auxiliar functions that manage the nodes list
node *add_node(node *p, char *word)
{
    // Allocate some memory for the node
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return NULL;
    }
    // Copy dictionary word in the node
    strcpy(n -> word, word);

    // Point to the new node
    n -> next = p;

    return n;
}

node *remove_node (node *p)
{
    // Temporary pointer to the next node of that we want to remove
    node *n = p->next;

    free(p);

    // Return the new node where pointed at
    return  n;

}
