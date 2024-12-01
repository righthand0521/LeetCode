#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int value;
    int count;
    UT_hash_handle hh;
};
void freeAll(struct hashTable *pFree) {
    struct hashTable *pCurrent;
    struct hashTable *pTemp;
    HASH_ITER(hh, pFree, pCurrent, pTemp) {
        // printf("%d: %d\n", pFree->value, pFree->count);
        HASH_DEL(pFree, pCurrent);
        free(pCurrent);
    }
}
bool checkIfExist(int *arr, int arrSize) {
    bool retVal = false;

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int value;
    int i;
    for (i = 0; i < arrSize; ++i) {
        value = arr[i];

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &value, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                goto _exit;
            }
            pTemp->value = value;
            pTemp->count = 1;
            HASH_ADD_INT(pHashTable, value, pTemp);
        } else {
            pTemp->count += 1;
        }
    }

    for (i = 0; i < arrSize; ++i) {
        value = arr[i];

        pTemp = NULL;
        if (value == 0) {
            HASH_FIND_INT(pHashTable, &value, pTemp);
            if (pTemp == NULL) {
                break;
            }

            if (pTemp->count > 1) {
                retVal = true;
                break;
            }
        } else if (value != 0) {
            value *= 2;

            HASH_FIND_INT(pHashTable, &value, pTemp);
            if (pTemp != NULL) {
                retVal = true;
                break;
            }
        }
    }

_exit:
    freeAll(pHashTable);
    pHashTable = NULL;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{10, 2, 5, 3}, 4},
                    {{3, 1, 7, 11}, 4},
                    {{-2, 0, 10, -19, 4, 6, -8}, 7},
                    {{0, 0}, 2},
                    {{-10, 12, -20, -8, 15}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [10,2,5,3]
     *  Output: true
     *
     *  Input: arr = [3,1,7,11]
     *  Output: false
     *
     *  Input: arr = [-2, 0, 10, -19, 4, 6, -8]
     *  Output: false
     *
     *  Input: arr = [0, 0]
     *  Output: true
     *
     *  Input: arr = [-10, 12, -20, -8, 15]
     *  Output: true
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        answer = checkIfExist(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
