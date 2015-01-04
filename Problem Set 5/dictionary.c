/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// define hash length as alphabet + apostrophe
#define RLENGTH 27


// define TRIE struct
typedef struct node
{
    bool is_word;
    struct node* child[RLENGTH];
}
node;

node *root;

// to track number of words read from the dictionary
int num_words = 0;

// define a function to initialize all pointers in each node to NULL
// function inspired from: http://www.inf.ufrgs.br/~arcoelho/rslp/html/rslpTrie_8c-source.html
void trie_init(node *node);

// define function to iterate and free memory blocks holding pointers to nodes
// function inspired from: http://www.inf.ufrgs.br/~arcoelho/rslp/html/rslpTrie_8c-source.html
void free_node(node *cnode);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node *cnode = root;
    int i = 0;
 
    // continue iterating until end of string    
    while (word[i] != '\0')
    {   
        int index = 0;
        
        // set index to 26 if apostrophe since index formula below won't work
        if (word[i] == '\'')
            index = 26;
        else
            index = tolower(word[i])-'a';    
        
        // if child node containing letter isn't null, assign to current, continue
        if (cnode->child[index] != NULL)
        {
            cnode = cnode->child[index];
            i++;
        }
        else
            break;     
    }
    
    // if the word exists in dictionary AND we are at end of reading word from f_in, confirm proper spelling
    if (cnode->is_word == true && word[i] == '\0')
        return true;
    
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Failed to read %s.\n", dictionary);
        return false;
    }
    
    // malloc space for rootq
    root = (node *) malloc(sizeof(node));
    trie_init(root);
    
    // create node for iteration
    node *cnode = NULL;
    
    // buffer for reading each char
    int c;
    
    while ((c = fgetc(fp)) != EOF)
    {   
        // reset cnode to root for next word
        cnode = root;
        
        // copy one letter at a time into int buffer
        for (; c != '\n'; c = fgetc(fp))
        {   
            int index = c - 'a';
            
            if (c == '\'')
                index = 26;
                
            // if that child does not exist at index 
            if (!cnode->child[index])
            {    
                // create new node at that index
                cnode->child[index] = (node *) malloc(sizeof(node));
                trie_init(cnode->child[index]);
                cnode = cnode->child[index];
            }    
            // point cnode to that new node to continue iterating through the word
            else
                cnode = cnode->child[index];
        }  
        // once newline character reached, set current node is_word to true to indicate word has been read
        cnode->is_word = true;  
        num_words++;
    }

    fclose(fp);
    
    return true;  
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return num_words;
}

// define Trie init node for root
void trie_init(node *node)
{
    node->is_word = false;
    for (int i = 0; i < RLENGTH; i++)
        node->child[i] = NULL;
}

// define TRIE free function for memory used in children
void free_node(node *cnode)
{   
    node *current = cnode;

    for (int i = 0; i < RLENGTH; i++)
    {
        // continue down each branch until null 
        if (current->child[i])
        {
            free_node(current->child[i]);
            free(current->child[i]);
        }
    }
    
    // if iterator at the top of tree, free root
    if(current==root)
        free(current);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    free_node(root);
        return true;
    return false;
}
