/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "dictionary.h"

#define DICTIONARY "/home/cs50/pset5/dictionaries/large"

typedef struct node
{
    bool complete;
    struct node* children[27];
}
node;
node* root;
node* move;

extern int count;
int count = 0;
    

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* move = root;    
    for(int i = 0, n = strlen(word); i < n; i++)
    {
        int compare = 0;
        //converts the letters to numbers
        if(isupper(word[i]))
        {
            compare = word[i] - 'A';        
        }
        else if(islower(word[i]))
        {
            compare = word[i] - 'a';
        }
        else
        {
            //if not letters, then the char must be an apostrophe
            compare = 26;
        }
        
               
        if((move->children[compare]) != NULL)
        {
            move = move->children[compare];                     
        }
        else
        {
            return false;            
        }   
    }
    if (move->complete)
    {
        return true;
        move = root;
    }  
    else
    {
        return false;
        move = root;
    }
    free(move);
}


/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    root = malloc(sizeof(node));
    node* move = root;
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        return false;
    }
       
    //a pointer to keep track of the movement
   
    //loop runs until end of the file
    char* word = malloc(sizeof(char) * 46);
    while ((fscanf(fp, "%s", word)) != EOF)
    {
        move = root;
        for (int i = 0, n = strlen(word); i < n; i++)
        {
            //converts characters to numbers from 0 - 26
            int comp = 0;
            if (isalpha(word[i]))
            {
                comp = word[i] - 'a';
            }
            else
            {
                //if not a letter then it much be apostrophe aka 26
                comp = 26;
            }
            
            
            if (move->children[comp] == NULL) 
            {
                move->children[comp] = malloc(sizeof(node));
                move = move->children[comp];
                              
            }
           
            else
            {
                if((n - i) != 1)
                {
                    move = move->children[comp];                
                }              
                   
            }         
                          
        } 
        count++;
        move->complete = true;
    }    
   return true;
   move = root;
   free(move);
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
void freenode(node* move)
{
    for (int i = 0; i < 27; i++)
    {             
       
        if(move->children[i] != NULL)
        {
           freenode(move->children[i]);
           free(move->children[i]);
        }
    }

}

bool unload(void)
{   
   node* move = root; 
   freenode(move);
   free(root);
   return true;
}

