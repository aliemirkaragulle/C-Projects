// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 26;
const unsigned int M = ((N *N) + N);

// Number of words in the dictionary
unsigned int DICT_NUM = 0;

// Hash table
node *table[M];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to obtain a hash value
    int index = hash(word);

    // Access linked list at that index in the hash table
    node *tmp = table[index];

    // Traverse linked list, looking for the word
    while (tmp != NULL)
    {
        if (strcasecmp(tmp -> word, word) == 0)
        {
            return true;
        }
        tmp = tmp -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    const int X = 'A';
    const int Y = 'A' + 'a';
    const int Z = 25;

    const int W = 676;

    if (strlen(word) > 1)
    {
        return ((toupper(word[0]) + tolower(word[1])) - Y + (Z * ((toupper(word[0])) - X)));
    }
    // Argument can be a letter (one-letter word)
    else
    {
        return ((toupper(word[0]) - X) + W);
    }

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Can not open dictionary.\n");
        return false;
    }
    else
    {
        // Read strings from file one at a time
        char words[LENGTH + 1];
        while (fscanf(file, "%s", words) != EOF)
        {
            // Increment the number of words in the dictionary
            DICT_NUM ++;

            // Create a new node for each word
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                fclose(file);
                free(n);
                return false;
            }
            strcpy(n -> word, words);

            // Hash word to obtain a hash value
            unsigned int index = hash(words);

            // Insert node into hash table at that location
            n -> next = table[index];
            table[index] = n;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return DICT_NUM;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < M; i ++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor -> next;
            free(cursor);
            cursor = tmp;
        }
    }
    return true;
}