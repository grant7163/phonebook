#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */

#define MAX_LAST_NAME_SIZE 16
#define HASH_TABLE_LENGTH  12289   //24593   //1543  //1024   //取質數為了reduce 碰撞 and 均勻分佈
#define HASH_OPT 1

typedef struct __PHONE_OTHER_ENTRY {
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
    struct __PHONE_BOOK_ENTRY *pNext;
    detailEntry *other;
} entry;

typedef struct __MEMORY_POOL {
    char *next;
    char *head;
    char *tail;
} m_pool;

entry *findName(char lastName[], entry *table[]);
void append(char lastName[], entry **table);
unsigned int BKDRHash(char *str);
unsigned int APHash(char *str);
unsigned int DJBHash(char *str);
unsigned int SDBMHash(char *str);
unsigned int ELFHash(char *str);
void init(entry * table[]);
void create_m_pool(int size);
void free_m_pool(void);

#endif

