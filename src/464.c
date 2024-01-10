#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

typedef struct HashItem {
    int key;
    bool value;
    UT_hash_handle hh;
} HashItem;
void freeAll(struct HashItem *pFree) {
    struct HashItem *pCurrent;
    struct HashItem *pTmp;
    HASH_ITER(hh, pFree, pCurrent, pTmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, pCurrent);
        free(pCurrent);
    }
}
bool dfs(int maxChoosableInteger, int usedNumbers, int desiredTotal, int currentTotal, HashItem **pMemo) {
    bool retVal = false;

    HashItem *pEntry = NULL;
    HASH_FIND_INT(*pMemo, &usedNumbers, pEntry);
    if (NULL != pEntry) {
        retVal = pEntry->value;
        return retVal;
    }

    int i;
    for (i = 0; i < maxChoosableInteger; i++) {
        if (((usedNumbers >> i) & 1) != 0) {
            continue;
        }

        if (i + 1 + currentTotal >= desiredTotal) {
            retVal = true;
            break;
        }

        if (dfs(maxChoosableInteger, usedNumbers | (1 << i), desiredTotal, currentTotal + i + 1, pMemo) == false) {
            retVal = true;
            break;
        }
    }
    pEntry = (HashItem *)malloc(sizeof(HashItem));
    if (pEntry == NULL) {
        perror("malloc");
        return retVal;
    }
    pEntry->key = usedNumbers;
    pEntry->value = retVal;
    HASH_ADD_INT(*pMemo, key, pEntry);

    return retVal;
}
bool canIWin(int maxChoosableInteger, int desiredTotal) {
    bool retVal = false;

    if ((1 + maxChoosableInteger) * (maxChoosableInteger) / 2 < desiredTotal) {
        return retVal;
    }

    HashItem *pMemo = NULL;
    retVal = dfs(maxChoosableInteger, 0, desiredTotal, 0, &pMemo);
    freeAll(pMemo);

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int maxChoosableInteger;
        int desiredTotal;
    } testCase[] = {{10, 11}, {10, 0}, {10, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: maxChoosableInteger = 10, desiredTotal = 11
     *  Output: false
     *
     *  Input: maxChoosableInteger = 10, desiredTotal = 0
     *  Output: true
     *
     *  Input: maxChoosableInteger = 10, desiredTotal = 1
     *  Output: true
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: maxChoosableInteger = %d, desiredTotal = %d\n", testCase[i].maxChoosableInteger,
               testCase[i].desiredTotal);

        answer = canIWin(testCase[i].maxChoosableInteger, testCase[i].desiredTotal);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
