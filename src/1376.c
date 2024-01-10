#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define DFS (1)
#define BFS (0)
typedef struct {
    int key;
    struct ListNode *list;
    UT_hash_handle hh;
} HashItem;
struct ListNode *listNodeCreat(int val) {
    struct ListNode *pRetVal = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->val = val;
    pRetVal->next = NULL;

    return pRetVal;
}
void listFree(struct ListNode *pHead) {
    struct ListNode *pFree = pHead;
    while (pHead) {
        pFree = pHead;
        pHead = pHead->next;
        free(pFree);
        pFree = NULL;
    }
}
HashItem *hashFindItem(HashItem **pObj, int key) {
    HashItem *pEntry = NULL;

    HASH_FIND_INT(*pObj, &key, pEntry);

    return pEntry;
}
void hashAddItem(HashItem **pObj, int key, int val) {
    HashItem *pEntry = hashFindItem(pObj, key);
    if (pEntry == NULL) {
        pEntry = (HashItem *)malloc(sizeof(HashItem));
        if (pEntry == NULL) {
            perror("malloc");
            return;
        }
        pEntry->key = key;
        pEntry->list = listNodeCreat(val);
        if (pEntry->list == NULL) {
            return;
        }
        HASH_ADD_INT(*pObj, key, pEntry);

        return;
    }

    struct ListNode *pListNode = listNodeCreat(val);
    if (pListNode == NULL) {
        return;
    }
    pListNode->next = pEntry->list;
    pEntry->list = pListNode;
}
struct ListNode *hashGetItem(HashItem **pObj, int key) {
    struct ListNode *pRetVal = NULL;

    HashItem *pEntry = hashFindItem(pObj, key);
    if (pEntry != NULL) {
        pRetVal = pEntry->list;
    }

    return pRetVal;
}
void hashFree(HashItem **pObj) {
    HashItem *pCurrent = NULL;
    HashItem *pTmp = NULL;
    HASH_ITER(hh, *pObj, pCurrent, pTmp) {
        HASH_DEL(*pObj, pCurrent);
        listFree(pCurrent->list);
        free(pCurrent);
        pCurrent = NULL;
    }
}
int dfs(int headID, int *informTime, HashItem **pAdjacent) {
    int retVal = 0;

    struct ListNode *pListNode = NULL;
    int neighbor;

    HashItem *pEntry = hashFindItem(pAdjacent, headID);
    if (pEntry != NULL) {
        for (pListNode = pEntry->list; pListNode; pListNode = pListNode->next) {
            neighbor = pListNode->val;
            retVal = fmax(retVal, dfs(neighbor, informTime, pAdjacent));
        }
    }
    retVal = informTime[headID] + retVal;

    return retVal;
}
int numOfMinutes(int n, int headID, int *manager, int managerSize, int *informTime, int informTimeSize) {
    int retVal = 0;

    //
    HashItem *pAdjacent = NULL;
    int employee;
    for (employee = 0; employee < n; ++employee) {
        hashAddItem(&pAdjacent, manager[employee], employee);
    }

    //
#if (DFS)
    retVal = dfs(headID, informTime, &pAdjacent);
#elif (BFS)
#endif

    //
    hashFree(&pAdjacent);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int n;
        int headID;
        int manager[MAX_SIZE];
        int managerSize;
        int informTime[MAX_SIZE];
        int informTimeSize;
    } testCase[] = {{1, 0, {-1}, 1, {0}, 1}, {6, 2, {2, 2, -1, 2, 2, 2}, 6, {0, 0, 1, 0, 0, 0}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 1, headID = 0, manager = [-1], informTime = [0]
     *  Output: 0
     *
     *  Input: n = 6, headID = 2, manager = [2,2,-1,2,2,2], informTime = [0,0,1,0,0,0]
     *  Output: 1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, headID = %d, manager = [", testCase[i].n, testCase[i].headID);
        for (j = 0; j < testCase[i].managerSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].manager[j]);
        }
        printf("], informTime = [");
        for (j = 0; j < testCase[i].informTimeSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].informTime[j]);
        }
        printf("]\n");

        answer = numOfMinutes(testCase[i].n, testCase[i].headID, testCase[i].manager, testCase[i].managerSize,
                              testCase[i].informTime, testCase[i].informTimeSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
