#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include IMPL

#ifdef OPT
#define OUT_FILE "opt.txt"
#elif HASH_OPT
#define OUT_FILE "hash_opt.txt"
#elif BST_OPT
#define OUT_FILE "bst_opt.txt"
#else
#define OUT_FILE "orig.txt"
#endif

#define DICT_FILE "./dictionary/words.txt"

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
    FILE *fp = NULL;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE] = {'\0'};
    struct timespec start, end;
    double cpu_time1 = 0;
    double cpu_time2 = 0;
#ifdef HASH_OPT
    static int slot[SIZE];
#endif

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

#ifdef HASH_OPT
    create_m_pool(sizeof(entry) * 350000);
#endif

    /* build the entry */
    entry *pHead = NULL;
    entry *e = NULL;

    pHead = (entry *) malloc(sizeof(entry));
    printf("size of entry : %zu bytes\n", sizeof(entry));
    e = pHead;
    e->pNext = NULL;

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif

#ifdef HASH_OPT
   entry* table[HASH_TABLE_LENGTH];

   init(table);

   clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
        append(line, table);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);
#else
   clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
        e = append(line, e);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);
#endif

    /* close file as soon as possible */
    fclose(fp);

#ifndef HASH_OPT
#ifndef BST_OPT
    e = pHead;
#else
    clock_gettime(CLOCK_REALTIME, &start);
    BSTNode *root = BST(&pHead, listLength(pHead));
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 += diff_in_second(start, end);
#endif
#endif

    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = "zyxel";
//    e = pHead;

#ifdef HASH_OPT
    assert(findName(input, table) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(input, table)->lastName, "zyxel"));
#elif BST_OPT
    assert(findName(input, root) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(input, root)->lastName, "zyxel"));
#else
    assert(findName(input, e) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(input, e)->lastName, "zyxel"));
#endif

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif

#ifdef HASH_OPT
    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    findName(input, table);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);
#elif BST_OPT
    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    findName(input, root);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);
#else    
    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    findName(input, e);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);
#endif
    
    FILE *output = fopen(OUT_FILE, "a");
    fprintf(output, "append() findName() %.8lf %.8lf\n", cpu_time1, cpu_time2);
    fclose(output);

    printf("execution time of append() : %.8lf sec\n", cpu_time1);
    printf("execution time of findName() : %.8lf sec\n", cpu_time2);

#ifndef HASH_OPT
#ifndef BST_OPT
    /* free linked list of entry */
    do {
        e = pHead;
        pHead = pHead->pNext;
        free(e);
        e = NULL;
    } while (pHead);
#else    
    /* free linked list of entry */
    binarySearch(root);
#endif
#endif

#ifdef HASH_OPT
    free_m_pool();
    free(pHead);
#endif

    return 0;
}
