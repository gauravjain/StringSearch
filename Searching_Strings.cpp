// CPP program to search a string among a very large set of given string.
// Author - Gaurav Jain (11CO36)
#include <stdio.h>
#include <stdlib.h>
#include<fstream>
#include<iostream>
#include<string>
#define MAX 50

using namespace std;
// Defining the node of the search tree
struct Node
{
    char data;

    // True if this character is last character of one of the words
    unsigned isEndOfString: 1;

    struct Node *left, *eq, *right;
};

// To create a new tree node
struct Node* newNode(char data)
{
    struct Node* temp = (struct Node*) malloc(sizeof( struct Node ));
    temp->data = data;
    temp->isEndOfString = 0;
    temp->left = temp->eq = temp->right = NULL;
    return temp;
}

// Function to insert a new word in a Search Tree
void insert(struct Node** root, char *word)
{
    // Base Case: Tree is empty
    if (!(*root))
        *root = newNode(*word);

    // If current character of word is smaller than root's character,
    // then insert this word in left subtree of root
    if ((*word) < (*root)->data)
        insert(&((*root)->left), word);

    // If current character of word is greate than root's character,
    // then insert this word in right subtree of root
    else if ((*word) > (*root)->data)
        insert(&((*root)->right), word);

    // If current character of word is same as root's character,
    else
    {
        if (*(word+1))
            insert(&((*root)->eq), word+1);

        // the last character of the word
        else
            (*root)->isEndOfString = 1;
    }
}

// Function to search a given word
int searchTREE(struct Node *root, char *word)
{
    if (!root)
        return 0;

    if (*word < (root)->data)
        return searchTREE(root->left, word);

    else if (*word > (root)->data)
        return searchTREE(root->right, word);

    else
    {
        if (*(word+1) == '\0')
            return root->isEndOfString;

        return searchTREE(root->eq, word+1);
    }
}

// Main Function to retrieve and search words
int main()
{
    struct Node *root = NULL;
    char st1[1000];
    char str[1000],ch,c;
    //Taking input from the file words.tct in the same directory
    ifstream infile("words.txt");
    while(!infile.eof())
    {

            infile.getline(str,1000,'\n');
            insert(&root,str);
    }
    //Enter the word to be searched and enter 0 to exit
    while(printf("\nEnter the String:") && std::cin.getline(st1,1000,'\n') && st1[0]!='0')
    {
            printf("\nThe Search result is:\n");
            //Returning the respective search Results
            searchTREE(root,st1)? printf("Found\n"): printf("Not Found\n");
    }
    return 0;
}
