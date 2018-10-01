#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

#define BST_OPT 1

typedef struct __PHONE_BOOK_DETAIL_ENTRY {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} detailEntry;

typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    detailEntry *other;
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

typedef struct __BST_NODE {
    entry *entryData;
    struct __BST_NODE *right;
    struct __BST_NODE *left;
} BSTNode;

int listLength(entry *head);
BSTNode *BST(entry **tmp_head, int length);
entry *findName(char lastName[], BSTNode *root);
entry *append(char lastName[], entry *e);
void binarySearch(BSTNode* tmp_root);

#endif
