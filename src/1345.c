#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

// https://leetcode.cn/problems/jump-game-iv/solutions/1220752/tiao-yue-you-xi-iv-by-leetcode-solution-zsix/
typedef struct Pair {
    int idx;
    int step;
} Pair;
typedef struct IdxHashEntry {
    int key;
    struct ListNode *bfsQueueHead;
    UT_hash_handle hh;
} IdxHashEntry;
void hashAddIdxItem(struct IdxHashEntry **obj, int key, int val) {
    struct IdxHashEntry *pEntry = NULL;
    struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;

    HASH_FIND(hh, *obj, &key, sizeof(key), pEntry);
    if (NULL == pEntry) {
        pEntry = (struct IdxHashEntry *)malloc(sizeof(struct IdxHashEntry));
        pEntry->key = key;
        pEntry->bfsQueueHead = node;
        HASH_ADD(hh, *obj, key, sizeof(int), pEntry);
    } else {
        node->next = pEntry->bfsQueueHead;
        pEntry->bfsQueueHead = node;
    }
}
struct IdxHashEntry *hashFindIdxItem(struct IdxHashEntry **obj, int key) {
    struct IdxHashEntry *pEntry = NULL;
    HASH_FIND(hh, *obj, &key, sizeof(int), pEntry);
    return pEntry;
}
void hashFreeIdxAll(struct IdxHashEntry **obj) {
    struct IdxHashEntry *curr = NULL, *next = NULL;
    HASH_ITER(hh, *obj, curr, next) {
        HASH_DEL(*obj, curr);
        struct ListNode *pCurrent = NULL;
        while (curr->bfsQueueHead != NULL) {
            pCurrent = curr->bfsQueueHead;
            curr->bfsQueueHead = curr->bfsQueueHead->next;
            free(pCurrent);
            pCurrent = NULL;
        }
        free(curr);
    }
}
typedef struct SetHashEntry {
    int key;
    UT_hash_handle hh;
} SetHashEntry;
void hashAddSetItem(struct SetHashEntry **obj, int key) {
    struct SetHashEntry *pEntry = NULL;
    HASH_FIND(hh, *obj, &key, sizeof(key), pEntry);
    if (pEntry == NULL) {
        pEntry = malloc(sizeof(struct SetHashEntry));
        pEntry->key = key;
        HASH_ADD(hh, *obj, key, sizeof(int), pEntry);
    }
}
struct SetHashEntry *hashFindSetItem(struct SetHashEntry **obj, int key) {
    struct SetHashEntry *pEntry = NULL;
    HASH_FIND(hh, *obj, &key, sizeof(int), pEntry);
    return pEntry;
}
void hashFreeSetAll(struct SetHashEntry **obj) {
    struct SetHashEntry *curr = NULL, *next = NULL;
    HASH_ITER(hh, *obj, curr, next) {
        HASH_DEL(*obj, curr);
        free(curr);
    }
}
int minJumps(int *arr, int arrSize) {
    int retVal = -1;

    /* Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
     *  100: 0, 4
     *  -23: 1, 2
     *  404: 3, 9
     *   23: 5, 6, 7
     *    3: 8
     *
     *  (100) -> (-23) -> (-23) -> (404) -> (100) -> (23) -> (23) -> (23) -> (3) -> (404)
     *    |                          |        ^        |               ^              ^
     *    |                          |        |        +---------------+              |
     *    |                          +--------|---------------------------------------+
     *    +-----------------------------------+
     */
    struct IdxHashEntry *pAdjacent = NULL;
    for (int i = 0; i < arrSize; i++) {
        hashAddIdxItem(&pAdjacent, arr[i], i);
    }

    // Breadth-First Search
    struct Pair *bfsQueue = (struct Pair *)malloc(sizeof(struct Pair) * arrSize * 2);
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    bfsQueue[bfsQueueTail].idx = 0;
    bfsQueue[bfsQueueTail].step = 0;
    bfsQueueTail++;

    struct SetHashEntry *pVisit = NULL;
    hashAddSetItem(&pVisit, 0);

    while (bfsQueueHead != bfsQueueTail) {
        int idx = bfsQueue[bfsQueueHead].idx;
        int step = bfsQueue[bfsQueueHead].step;
        bfsQueueHead++;

        // Reached to last index
        if (idx + 1 == arrSize) {
            hashFreeIdxAll(&pAdjacent);
            hashFreeSetAll(&pVisit);
            free(bfsQueue);
            return step;
        }

        int v = arr[idx];
        step++;
        struct IdxHashEntry *pEntry = hashFindIdxItem(&pAdjacent, v);
        if (NULL != pEntry) {
            for (struct ListNode *node = pEntry->bfsQueueHead; node; node = node->next) {
                if (NULL == hashFindSetItem(&pVisit, node->val)) {
                    hashAddSetItem(&pVisit, node->val);
                    bfsQueue[bfsQueueTail].idx = node->val;
                    bfsQueue[bfsQueueTail].step = step;
                    bfsQueueTail++;
                }
            }
            HASH_DEL(pAdjacent, pEntry);
        }

        if (idx + 1 < arrSize && NULL == hashFindSetItem(&pVisit, idx + 1)) {
            hashAddSetItem(&pVisit, idx + 1);
            bfsQueue[bfsQueueTail].idx = idx + 1;
            bfsQueue[bfsQueueTail].step = step;
            bfsQueueTail++;
        }

        if (idx - 1 >= 0 && NULL == hashFindSetItem(&pVisit, idx - 1)) {
            hashAddSetItem(&pVisit, idx - 1);
            bfsQueue[bfsQueueTail].idx = idx - 1;
            bfsQueue[bfsQueueTail].step = step;
            bfsQueueTail++;
        }
    }

    hashFreeIdxAll(&pAdjacent);
    hashFreeSetAll(&pVisit);
    free(bfsQueue);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{100, -23, -23, 404, 100, 23, 23, 23, 3, 404}, 10}, {{7}, 1}, {{7, 6, 9, 6, 9, 6, 9, 7}, 8}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
     *  Output: 3
     *
     *  Input: arr = [7]
     *  Output: 0
     *
     *  Input: arr = [7,6,9,6,9,6,9,7]
     *  Output: 1
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].arr[j]);
        }
        printf("]\n");

        answer = minJumps(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
