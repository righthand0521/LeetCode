#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

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
bool isHappy(int n) {
    bool retVal = false;

    struct hashTable* pMap = NULL;
    struct hashTable* pTmp;
    int square, digit;
    while (n != 1) {
        pTmp = NULL;
        HASH_FIND_INT(pMap, &n, pTmp);
        if (pTmp != NULL) {
            break;
        }
        pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTmp == NULL) {
            perror("malloc");
            goto exit;
        }
        pTmp->key = n;
        HASH_ADD_INT(pMap, key, pTmp);

        square = 0;
        while (n > 0) {
            digit = n % 10;
            square += (digit * digit);
            n /= 10;
        }
        n = square;
    }

    if (n == 1) {
        retVal = true;
    }

exit:
    //
    freeAll(pMap);
    pMap = NULL;

    return retVal;
}

int main(int argc, char** argv) {
    int testCase[] = {19, 2};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 19
     *  Output: true
     *
     *  Input: n = 2
     *  Output: false
     */

    bool answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i]);

        answer = isHappy(testCase[i]);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
