#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    // int value;
    UT_hash_handle hh;
};
bool addKey(struct hashTable **pObj, int key) {
    bool retVal = true;

    struct hashTable *pTemp = NULL;
    HASH_FIND_INT(*pObj, &key, pTemp);
    if (pTemp != NULL) {
        return retVal;
    }

    pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pTemp == NULL) {
        perror("malloc");
        retVal = false;
    } else {
        pTemp->key = key;
        HASH_ADD_INT(*pObj, key, pTemp);
    }

    return retVal;
}
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d\n", pFree->key);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int subarrayBitwiseORs(int *arr, int arrSize) {
    int retVal = 0;

    if (arrSize < 2) {
        return arrSize;
    }

    struct hashTable *result = NULL;
    int key;
    bool isValid = true;
    for (int i = 0; i < arrSize; i++) {
        key = arr[i];
        isValid = addKey(&result, key);
        if (isValid == false) {
            goto exit;
        }

        for (int j = i - 1; j >= 0; j--) {
            if ((arr[j] & arr[i]) == arr[i]) {
                break;
            }
            arr[j] |= arr[i];

            key = arr[j];
            isValid = addKey(&result, key);
            if (isValid == false) {
                goto exit;
            }
        }
    }
    retVal = HASH_COUNT(result);

exit:
    freeAll(result);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{0}, 1}, {{1, 1, 2}, 3}, {{1, 2, 4}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [0]
     *  Output: 1
     *
     *  Input: arr = [1,1,2]
     *  Output: 3
     *
     *  Input: arr = [1,2,4]
     *  Output: 6
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        answer = subarrayBitwiseORs(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
