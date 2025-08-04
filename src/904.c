#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
bool addKey(struct hashTable **pObj, int key, int value) {
    bool retVal = true;

    struct hashTable *pTemp = NULL;
    HASH_FIND_INT(*pObj, &key, pTemp);
    if (pTemp != NULL) {
        pTemp->value += value;
        if (pTemp->value == 0) {
            HASH_DEL(*pObj, pTemp);
            free(pTemp);
        }

        return retVal;
    }

    pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pTemp == NULL) {
        perror("malloc");
        retVal = false;
    } else {
        pTemp->key = key;
        pTemp->value = value;
        HASH_ADD_INT(*pObj, key, pTemp);
    }

    return retVal;
}
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int totalFruit(int *fruits, int fruitsSize) {
    int retVal = 0;

    /* Example
     *          +--------------------------------------------+-----------------------------+
     *          | 3 | 3 | 3 | 1 | 2 | 1 | 1 | 2 | 3 | 3 | 4  |                             |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  | 0 > 1 > 2 > 3 > 4                          | size: 1 > 1 > 1 > 2 > 3 |   |
     *    head  | 0                                          |  max: 1 > 2 > 3 > 4     | 4 |
     *          +--------------------------------------------+-------------------------+---|
     *    tail  |                 4                          | size: 3 > 3 > 3 > 2     |   |
     *    head  | 0 > 1 > 2 > 3                              |  max: 4 > 2             | 4 |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  |                 4 > 5 > 6 > 7 > 8          | size: 2 > 2 > 2 > 2 > 3 |   |
     *    head  |             3                              |  max: 2 > 3 > 4 > 5     | 5 |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  |                                 8          | size: 3 > 3 > 3 > 3 > 2 |   |
     *    head  |             3 > 4 > 5 > 6 > 7              |  max: 5 > 2             | 5 |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  |                                 8 > 9 > 10 | size: 2 > 2 > 3         |   |
     *    head  |                             7              |  max: 2 > 3             | 5 |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  |                                         10 | size: 3 > 2             |   |
     *    head  |                             7 > 8          |  max: 3 > 3             | 5 |
     *          +--------------------------------------------+-------------------------+---+
     */
    struct hashTable *frequency = NULL;
    int frequencySize;
    int key;
    bool isValid = true;
    int head = 0;
    int tail = 0;
    while (tail < fruitsSize) {
        key = fruits[tail];
        isValid = addKey(&frequency, key, 1);
        if (isValid == false) {
            freeAll(frequency);
            return retVal;
        }
        frequencySize = HASH_COUNT(frequency);

        while (frequencySize > 2) {
            key = fruits[head];
            isValid = addKey(&frequency, key, -1);
            if (isValid == false) {
                freeAll(frequency);
                return retVal;
            }
            frequencySize = HASH_COUNT(frequency);

            head++;
        }
        retVal = fmax(retVal, tail - head + 1);

        ++tail;
    }

    //
    freeAll(frequency);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int fruits[MAX_SIZE];
        int fruitsSize;
    } testCase[] = {{{1, 2, 1}, 3}, {{0, 1, 2, 2}, 4}, {{1, 2, 3, 2, 2}, 5}, {{3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4}, 11}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: fruits = [1,2,1]
     *  Output: 3
     *
     *  Input: fruits = [0,1,2,2]
     *  Output: 3
     *
     *  Input: fruits = [1,2,3,2,2]
     *  Output: 4
     *
     *  Input: fruits = [3,3,3,1,2,1,1,2,3,3,4]
     *  Output: 5
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: fruits  = [");
        for (j = 0; j < testCase[i].fruitsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].fruits[j]);
        }
        printf("]\n");

        answer = totalFruit(testCase[i].fruits, testCase[i].fruitsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
