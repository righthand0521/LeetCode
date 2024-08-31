#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    UT_hash_handle hh;
};
struct hashTable* find(struct hashTable** pObj, int key) {
    struct hashTable* pRetVal = NULL;

    HASH_FIND_INT((*pObj), &key, pRetVal);

    return pRetVal;
}
void insert(struct hashTable** pObj, int key) {
    struct hashTable* pTmp = NULL;
    HASH_FIND_INT((*pObj), &key, pTmp);
    if (pTmp == NULL) {
        pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTmp == NULL) {
            perror("malloc");
            return;
        }
        pTmp->key = key;
        HASH_ADD_INT((*pObj), key, pTmp);
    }
}
void erase(struct hashTable** pObj, int key) {
    struct hashTable* pTmp = NULL;
    HASH_FIND_INT((*pObj), &key, pTmp);
    if (pTmp != NULL) {
        HASH_DEL((*pObj), pTmp);
        free(pTmp);
        pTmp = NULL;
    }
}
int backtrack(int n, int row, struct hashTable** columns, struct hashTable** diagonals1,
              struct hashTable** diagonals2) {
    int retVal = 0;

    if (row == n) {
        retVal = 1;
        return retVal;
    }

    int diagonal1, diagonal2;
    int i;
    for (i = 0; i < n; i++) {
        if (find(columns, i) != NULL) {
            continue;
        }

        diagonal1 = row - i;
        if (find(diagonals1, diagonal1) != NULL) {
            continue;
        }

        diagonal2 = row + i;
        if (find(diagonals2, diagonal2) != NULL) {
            continue;
        }

        insert(columns, i);
        insert(diagonals1, diagonal1);
        insert(diagonals2, diagonal2);
        retVal += backtrack(n, row + 1, columns, diagonals1, diagonals2);
        erase(columns, i);
        erase(diagonals1, diagonal1);
        erase(diagonals2, diagonal2);
    }

    return retVal;
}
int totalNQueens(int n) {
    int retVal = 0;

    struct hashTable* columns = NULL;
    struct hashTable* diagonals1 = NULL;
    struct hashTable* diagonals2 = NULL;
    retVal = backtrack(n, 0, &columns, &diagonals1, &diagonals2);

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{4}, {1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 4
     *  Output: 2
     *
     *  Input: n = 1
     *  Output: 1
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = totalNQueens(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
