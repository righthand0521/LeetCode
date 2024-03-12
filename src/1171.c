#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    struct ListNode *val;
    UT_hash_handle hh;
};
struct hashTable *hashFindItem(struct hashTable **obj, int key) {
    struct hashTable *pRetVal = NULL;

    HASH_FIND_INT(*obj, &key, pRetVal);

    return pRetVal;
}
bool hashAddItem(struct hashTable **obj, int key, struct ListNode *val) {
    bool retVal = false;

    if (hashFindItem(obj, key)) {
        return retVal;
    }

    struct hashTable *pEntry = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pEntry == NULL) {
        perror("malloc");
        return retVal;
    }
    pEntry->key = key;
    pEntry->val = val;
    HASH_ADD_INT(*obj, key, pEntry);
    retVal = true;

    return retVal;
}
void hashSetItem(struct hashTable **obj, int key, struct ListNode *val) {
    struct hashTable *pEntry = hashFindItem(obj, key);
    if (pEntry == NULL) {
        hashAddItem(obj, key, val);
    } else {
        pEntry->val = val;
    }
}
struct ListNode *hashGetItem(struct hashTable **obj, int key) {
    struct ListNode *pRetVal = NULL;

    struct hashTable *pEntry = hashFindItem(obj, key);
    if (pEntry != NULL) {
        pRetVal = pEntry->val;
    }

    return pRetVal;
}
void hashFree(struct hashTable **pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, *pFree, current, tmp) {
        HASH_DEL(*pFree, current);
        free(current);
    }
}
struct ListNode *createNode(int val) {
    struct ListNode *pRetVal = NULL;

    pRetVal = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->val = val;
    pRetVal->next = NULL;

    return pRetVal;
}
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *removeZeroSumSublists(struct ListNode *head) {
    struct ListNode *pRetVal = NULL;

    pRetVal = createNode(0);
    if (pRetVal == NULL) {
        return pRetVal;
    }
    pRetVal->next = head;

    struct ListNode *pCurrent = NULL;
    struct hashTable *pHashTable = NULL;
    int prefixSum = 0;
    for (pCurrent = pRetVal; pCurrent; pCurrent = pCurrent->next) {
        prefixSum += pCurrent->val;
        hashSetItem(&pHashTable, prefixSum, pCurrent);
    }

    struct ListNode *pGet;
    prefixSum = 0;
    for (pCurrent = pRetVal; pCurrent; pCurrent = pCurrent->next) {
        prefixSum += pCurrent->val;
        pGet = hashGetItem(&pHashTable, prefixSum);
        /* valgrind -s --tool=memcheck --leak-check=full --max-stackframe=5000000 1171.c
            ==27242== HEAP SUMMARY:
            ==27242==     in use at exit: 96 bytes in 6 blocks
            ==27242==   total heap usage: 38 allocs, 32 frees, 3,976 bytes allocated
            ==27242==
            ==27242== 96 (32 direct, 64 indirect) bytes in 2 blocks are definitely lost in loss record 2 of 2
            ==27242==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
            ==27242==    by 0x1092AC: main (in /root/WorkingSpace/1171-c)
            ==27242==
            ==27242== LEAK SUMMARY:
            ==27242==    definitely lost: 32 bytes in 2 blocks
            ==27242==    indirectly lost: 64 bytes in 4 blocks
            ==27242==      possibly lost: 0 bytes in 0 blocks
            ==27242==    still reachable: 0 bytes in 0 blocks
            ==27242==         suppressed: 0 bytes in 0 blocks
            ==27242==
            ==27242== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
         */
        if (pGet != NULL) {
            pCurrent->next = pGet->next;
        }
    }

    hashFree(&pHashTable);
    pCurrent = pRetVal;
    pRetVal = pRetVal->next;
    free(pCurrent);
    pCurrent = NULL;

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
    } testCase[] = {{{1, 2, -3, 3, 1}, 5}, {{1, 2, 3, -3, 4}, 5}, {{1, 2, 3, -3, -2}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,2,-3,3,1]
     *  Output: [3,1]
     *
     *  Input: head = [1,2,3,-3,4]
     *  Output: [1,2,4]
     *
     *  Input: head = [1,2,3,-3,-2]
     *  Output: [1]
     */

    struct ListNode *pHead = NULL;
    struct ListNode *pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].node, testCase[i].nodeSize);
        printf("Input: ");
        printf("head = [");
        printList(pHead);
        printf("]\n");

        pAnswer = removeZeroSumSublists(pHead);
        printf("Output: [");
        printList(pAnswer);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
        // freeListNode(pAnswer);
        // pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
