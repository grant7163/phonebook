#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_bst_opt.h"

int listLength(entry* head)
{
  int count = 0;
  entry* current = head;

  while(current != NULL)
  {
    count++;
    current = current->pNext; 
  }

  return count;
}

void binarySearch(BSTNode* tmp_root)
{
  if (tmp_root != NULL)
  {
    binarySearch(tmp_root->left);
    binarySearch(tmp_root->right);
    free(tmp_root);
    tmp_root = NULL;
  }
}

BSTNode *BST(entry **tmp_head, int length)
{
    if (length <= 0)
        return NULL;

    BSTNode *left = BST(tmp_head, length/2);
    BSTNode *root = malloc(sizeof(BSTNode));
    root->entryData = *tmp_head;
    root->left = left;

    *tmp_head = (*tmp_head)->pNext;

    root->right = BST(tmp_head, length - (length / 2 + 1));

    return root;
}

entry *findName(char lastName[], BSTNode *root)
{
    BSTNode *current = root;
    int result;

    while (current != NULL && (result = strcasecmp(lastName, current->entryData->lastName)) != 0) {
        if (result < 0)
            current = current -> left;
        else
            current = current -> right;
    }

    if (root)
        return (current->entryData);
    else
        return NULL;
}

entry *append(char lastName[], entry *e)
{
    e->pNext = (entry *) malloc(sizeof(entry));
    e->other = NULL;
    e = e -> pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
}

