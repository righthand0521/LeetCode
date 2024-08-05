#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_LENGTH (8)  // 1 <= arr[i].length <= 5
struct hashTable {
    char key[MAX_LENGTH];
    int count;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%s: %d\n", pFree->key, pFree->count);
        HASH_DEL(pFree, current);
        free(current);
    }
}
char* kthDistinct(char** arr, int arrSize, int k) {
    char* pRetVal = "";

    struct hashTable* pHashTable = NULL;

    char pStr[MAX_LENGTH];
    struct hashTable* pTmp;
    int i;
    for (i = 0; i < arrSize; ++i) {
        memset(pStr, 0, sizeof(pStr));
        snprintf(pStr, sizeof(pStr), "%s", arr[i]);

        pTmp = NULL;
        HASH_FIND_STR(pHashTable, pStr, pTmp);
        if (pTmp != NULL) {
            pTmp->count++;
            continue;
        }

        pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTmp == NULL) {
            perror("malloc");
            goto exit;
        }
        snprintf(pTmp->key, MAX_LENGTH, "%s", pStr);
        pTmp->count = 1;
        HASH_ADD_STR(pHashTable, key, pTmp);
    }

    for (i = 0; i < arrSize; ++i) {
        memset(pStr, 0, sizeof(pStr));
        snprintf(pStr, sizeof(pStr), "%s", arr[i]);

        pTmp = NULL;
        HASH_FIND_STR(pHashTable, pStr, pTmp);
        if (pTmp == NULL) {
            continue;
        }

        if (pTmp->count != 1) {
            continue;
        }

        k--;
        if (k == 0) {
            pRetVal = arr[i];
            break;
        }
    }

exit:
    //
    freeAll(pHashTable);
    pHashTable = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* arr[MAX_SIZE];
        int arrSize;
        int k;
    } testCase[] = {{{"d", "b", "c", "b", "c", "a"}, 6, 2}, {{"aaa", "aa", "a"}, 3, 1}, {{"a", "b", "a"}, 3, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = ["d","b","c","b","c","a"], k = 2
     *  Output: "a"
     *
     *  Input: arr = ["aaa","aa","a"], k = 1
     *  Output: "aaa"
     *
     *  Input: arr = ["a","b","a"], k = 3
     *  Output: ""
     */

    char* answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s\"%s\"", (j == 0 ? "" : ","), testCase[i].arr[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = kthDistinct(testCase[i].arr, testCase[i].arrSize, testCase[i].k);
        printf("Output: \"%s\"\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
