#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_WORD_SIZE (200 + 4)  // 1 <= s1.length, s2.length <= 200
struct hashTable {
    char key[MAX_WORD_SIZE];
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%s: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **uncommonFromSentences(char *s1, char *s2, int *returnSize) {
    char **pRetVal = NULL;

    (*returnSize) = 0;
    int mallocSize = 0;

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;

#define SEPARATED (" ")
    char *pStr = NULL;
    pStr = strtok(s1, SEPARATED);
    while (pStr != NULL) {
        pTemp = NULL;
        HASH_FIND_STR(pHashTable, pStr, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                pHashTable = NULL;
                return pRetVal;
            }
            strcpy(pTemp->key, pStr);
            pTemp->value = 1;
            HASH_ADD_STR(pHashTable, key, pTemp);
            mallocSize++;
        } else {
            pTemp->value += 1;
        }

        pStr = strtok(NULL, SEPARATED);
    }
    pStr = strtok(s2, SEPARATED);
    while (pStr != NULL) {
        pTemp = NULL;
        HASH_FIND_STR(pHashTable, pStr, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                pHashTable = NULL;
                return pRetVal;
            }
            strcpy(pTemp->key, pStr);
            pTemp->value = 1;
            HASH_ADD_STR(pHashTable, key, pTemp);
            mallocSize++;
        } else {
            pTemp->value += 1;
        }

        pStr = strtok(NULL, SEPARATED);
    }

    pRetVal = (char **)malloc(mallocSize * sizeof(char *));
    if (pRetVal == NULL) {
        perror("malloc");
        freeAll(pHashTable);
        pHashTable = NULL;
        return pRetVal;
    }

    int i;
    pTemp = NULL;
    struct hashTable *pCurrent = NULL;
    HASH_ITER(hh, pHashTable, pCurrent, pTemp) {
        if (pHashTable->value == 1) {
            pRetVal[(*returnSize)] = (char *)malloc(MAX_WORD_SIZE * sizeof(char));
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                for (i = 0; i < (*returnSize); ++i) {
                    free(pRetVal[i]);
                    pRetVal[i] = NULL;
                }
                free(pRetVal);
                pRetVal = NULL;
                (*returnSize) = 0;
                freeAll(pHashTable);
                pHashTable = NULL;
                return pRetVal;
            }
            memset(pRetVal[(*returnSize)], 0, (MAX_WORD_SIZE * sizeof(char)));
            strcpy(pRetVal[(*returnSize)], pHashTable->key);
            (*returnSize)++;
        }

        HASH_DEL(pHashTable, pCurrent);
        free(pCurrent);
        pCurrent = NULL;
    }
    pHashTable = NULL;

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        char s1[MAX_SIZE];
        char s2[MAX_SIZE];
        int returnSize;
    } testCase[] = {{"this apple is sweet", "this apple is sour", 0}, {"apple apple", "banana", 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s1 = "this apple is sweet", s2 = "this apple is sour"
     *  Output: ["sweet","sour"]
     *
     *  Input: s1 = "apple apple", s2 = "banana"
     *  Output: ["banana"]
     */

    char **pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s1 = \"%s\", s2 = \"%s\"\n", testCase[i].s1, testCase[i].s2);

        pAnswer = uncommonFromSentences(testCase[i].s1, testCase[i].s2, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
