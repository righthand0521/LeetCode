#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
struct hashTable {
    int key;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d\n", pFree->key);
        HASH_DEL(pFree, current);
        free(current);
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findEvenNumbers(int* digits, int digitsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    struct hashTable* pHashTable = NULL;
    struct hashTable* pTemp;
    int num;
    for (int i = 0; i < digitsSize; ++i) {
        for (int j = 0; j < digitsSize; ++j) {
            for (int k = 0; k < digitsSize; ++k) {
                if (i == j || j == k || i == k) {
                    continue;
                }
                num = digits[i] * 100 + digits[j] * 10 + digits[k];
                if ((num < 100) || (num % 2 != 0)) {
                    continue;
                }

                pTemp = NULL;
                HASH_FIND_INT(pHashTable, &num, pTemp);
                if (pTemp == NULL) {
                    pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
                    if (pTemp == NULL) {
                        perror("malloc");
                        freeAll(pHashTable);
                        return pRetVal;
                    }
                    pTemp->key = num;
                    HASH_ADD_INT(pHashTable, key, pTemp);
                }
            }
        }
    }

    pRetVal = (int*)calloc(HASH_COUNT(pHashTable), sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        freeAll(pHashTable);
        return pRetVal;
    }
    struct hashTable* pCurrent;
    pTemp = NULL;
    HASH_ITER(hh, pHashTable, pCurrent, pTemp) {
        pRetVal[(*returnSize)++] = pHashTable->key;
        HASH_DEL(pHashTable, pCurrent);
        free(pCurrent);
    }
    qsort(pRetVal, (*returnSize), sizeof(int), compareInteger);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int digits[MAX_SIZE];
        int digitsSize;
        int returnSize;
    } testCase[] = {{{2, 1, 3, 0}, 4, 0}, {{2, 2, 8, 8, 2}, 5, 0}, {{3, 7, 5}, 3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: digits = [2,1,3,0]
     *  Output: [102,120,130,132,210,230,302,310,312,320]
     *
     *  Input: digits = [2,2,8,8,2]
     *  Output: [222,228,282,288,822,828,882]
     *
     *  Input: digits = [3,7,5]
     *  Output: []
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: digits = [");
        for (j = 0; j < testCase[i].digitsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].digits[j]);
        }
        printf("]\n");

        pAnswer = findEvenNumbers(testCase[i].digits, testCase[i].digitsSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", *(pAnswer + j));
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
