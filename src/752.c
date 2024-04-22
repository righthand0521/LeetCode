#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_WHEELS (4 + 1)
struct hashTable {
    char str[MAX_WHEELS];
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%s\n", pFree->str);
        HASH_DEL(pFree, current);
        free(current);
    }
}
struct Node {
    char str[MAX_WHEELS];
    int val;
};
char nextSlot(char x) {
    char retVal = '0';

    if (x != '9') {
        retVal = x + 1;
    }

    return retVal;
}
char prevSlot(char x) {
    char retVal = '9';

    if (x != '0') {
        retVal = x - 1;
    }

    return retVal;
}
char** getNextStatus(char* status, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (char**)malloc(sizeof(char*) * 8);
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    char num;
    int i;
    for (i = 0; i < 4; ++i) {
        num = status[i];

        status[i] = prevSlot(num);
        pRetVal[(*returnSize)] = (char*)malloc(MAX_WHEELS * sizeof(char));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            return pRetVal;
        }
        memset(pRetVal[(*returnSize)], 0, (MAX_WHEELS * sizeof(char)));
        snprintf(pRetVal[(*returnSize)], (MAX_WHEELS * sizeof(char)), "%s", status);
        (*returnSize)++;

        status[i] = nextSlot(num);
        pRetVal[(*returnSize)] = (char*)malloc(MAX_WHEELS * sizeof(char));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            return pRetVal;
        }
        memset(pRetVal[(*returnSize)], 0, (MAX_WHEELS * sizeof(char)));
        snprintf(pRetVal[(*returnSize)], (MAX_WHEELS * sizeof(char)), "%s", status);
        (*returnSize)++;

        status[i] = num;
    }

    return pRetVal;
}
int openLock(char** deadends, int deadendsSize, char* target) {
    int retVal = -1;

    char initiallyStarts[MAX_WHEELS] = "0000";
    if (strcmp(target, initiallyStarts) == 0) {
        retVal = 0;
        return retVal;
    }

    struct hashTable* pHashTable = NULL;
    struct hashTable* pTmp = NULL;
    int i;
    for (i = 0; i < deadendsSize; i++) {
        HASH_FIND(hh, pHashTable, deadends[i], MAX_WHEELS * sizeof(char), pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                goto exit2;
            }
            memset(pTmp->str, 0, MAX_WHEELS);
            snprintf(pTmp->str, MAX_WHEELS, "%s", deadends[i]);
            HASH_ADD(hh, pHashTable, str, MAX_WHEELS * sizeof(char), pTmp);
        }
    }

    pTmp = NULL;
    HASH_FIND(hh, pHashTable, initiallyStarts, MAX_WHEELS * sizeof(char), pTmp);
    if (pTmp != NULL) {
        retVal = -1;
        goto exit2;
    }

    pTmp = NULL;
    struct hashTable* pSeen = NULL;
    pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
    if (pTmp == NULL) {
        perror("malloc");
        goto exit2;
    }
    memset(pTmp->str, 0, MAX_WHEELS);
    snprintf(pTmp->str, MAX_WHEELS, "%s", initiallyStarts);
    HASH_ADD(hh, pSeen, str, MAX_WHEELS * sizeof(char), pTmp);

    struct Node bfsQueue[10001];
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    snprintf(bfsQueue[bfsQueueTail].str, MAX_WHEELS, "%s", initiallyStarts);
    bfsQueue[bfsQueueTail++].val = 0;
    char* status;
    char** nextStatus;
    int step, nextStatusSize;
    struct hashTable* pTmp1;
    struct hashTable* pTmp2;
    while (bfsQueueHead < bfsQueueTail) {
        status = bfsQueue[bfsQueueHead].str;
        nextStatusSize = 0;
        nextStatus = getNextStatus(status, &nextStatusSize);

        step = bfsQueue[bfsQueueHead++].val;
        for (i = 0; i < nextStatusSize; i++) {
            pTmp1 = NULL;
            pTmp2 = NULL;

            HASH_FIND(hh, pHashTable, nextStatus[i], MAX_WHEELS * sizeof(char), pTmp1);
            HASH_FIND(hh, pSeen, nextStatus[i], MAX_WHEELS * sizeof(char), pTmp2);
            if ((pTmp1 == NULL) && (pTmp2 == NULL)) {
                if (strcmp(nextStatus[i], target) == 0) {
                    retVal = step + 1;
                    for (i = 0; i < 8; ++i) {
                        free(nextStatus[i]);
                        nextStatus[i] = NULL;
                    }
                    free(nextStatus);
                    nextStatus = NULL;
                    goto exit1;
                }
                strcpy(bfsQueue[bfsQueueTail].str, nextStatus[i]);
                bfsQueue[bfsQueueTail++].val = step + 1;
                pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
                if (pTmp == NULL) {
                    perror("malloc");
                    for (i = 0; i < 8; ++i) {
                        free(nextStatus[i]);
                        nextStatus[i] = NULL;
                    }
                    free(nextStatus);
                    nextStatus = NULL;
                    goto exit1;
                }
                memset(pTmp->str, 0, MAX_WHEELS);
                snprintf(pTmp->str, MAX_WHEELS, "%s", nextStatus[i]);
                HASH_ADD(hh, pSeen, str, MAX_WHEELS * sizeof(char), pTmp);
            }
        }

        for (i = 0; i < 8; ++i) {
            free(nextStatus[i]);
            nextStatus[i] = NULL;
        }
        free(nextStatus);
        nextStatus = NULL;
    }
    retVal = -1;

exit1:
    freeAll(pSeen);
    pSeen = NULL;
exit2:
    freeAll(pHashTable);
    pHashTable = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
#define MAX_LENGTH (4 + 4)
    struct testCaseType {
        char* deadends[MAX_SIZE];
        int deadendsSize;
        char target[MAX_LENGTH];
    } testCase[] = {{{"0201", "0101", "0102", "1212", "2002"}, 5, "0202"},
                    {{"8888"}, 1, "0009"},
                    {{"8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888"}, 8, "8888"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
     *  Output: 6
     *
     *  Input: deadends = ["8888"], target = "0009"
     *  Output: 1
     *
     *  Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
     *  Output: -1
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: deadends = [");
        for (j = 0; j < testCase[i].deadendsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].deadends[j]);
        }
        printf("], target = \"%s\"\n", testCase[i].target);

        answer = openLock(testCase[i].deadends, testCase[i].deadendsSize, testCase[i].target);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
