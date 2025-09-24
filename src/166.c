#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
char* fractionToDecimal(int numerator, int denominator) {
    char* pRetVal = NULL;

#define MAX_BUF_SIZE (1024)
    pRetVal = (char*)malloc(MAX_BUF_SIZE * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (MAX_BUF_SIZE * sizeof(char)));
    int returnSize = 0;

    long numeratorLong = numerator;
    long denominatorLong = denominator;

    //
    if (numeratorLong % denominatorLong == 0) {
        returnSize += snprintf(pRetVal + returnSize, MAX_BUF_SIZE - returnSize, "%ld", numeratorLong / denominatorLong);
        return pRetVal;
    }

    //
    if ((numeratorLong < 0) ^ (denominatorLong < 0)) {
        pRetVal[returnSize++] = '-';
    }

    //
    numeratorLong = labs(numeratorLong);
    denominatorLong = labs(denominatorLong);
    long integerPart = numeratorLong / denominatorLong;
    returnSize += snprintf(pRetVal + returnSize, MAX_BUF_SIZE - returnSize, "%ld", integerPart);
    pRetVal[returnSize++] = '.';

    //
    char fractionPart[MAX_BUF_SIZE];
    memset(fractionPart, 0, sizeof(fractionPart));
    int fractionPartSize = 0;

    struct hashTable* remainderIndexMap = NULL;
    struct hashTable* pTemp;

    long remainder = numeratorLong % denominatorLong;
    int index = 0;
    while (remainder != 0) {
        pTemp = NULL;
        HASH_FIND_INT(remainderIndexMap, &remainder, pTemp);
        if (pTemp != NULL) {
            break;
        }

        pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTemp == NULL) {
            perror("malloc");
            freeAll(remainderIndexMap);
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        pTemp->key = remainder;
        pTemp->value = index;
        HASH_ADD_INT(remainderIndexMap, key, pTemp);

        remainder *= 10;
        fractionPartSize += snprintf(fractionPart + fractionPartSize, MAX_BUF_SIZE - fractionPartSize, "%ld",
                                     remainder / denominatorLong);
        remainder %= denominatorLong;
        index++;
    }

    //
    if (remainder != 0) {
        pTemp = NULL;
        HASH_FIND_INT(remainderIndexMap, &remainder, pTemp);
        int insertIndex = pTemp->value;

        for (int i = 0; i < insertIndex; ++i) {
            pRetVal[returnSize++] = fractionPart[i];
        }
        pRetVal[returnSize++] = '(';
        for (int i = insertIndex; i < fractionPartSize; ++i) {
            pRetVal[returnSize++] = fractionPart[i];
        }
        pRetVal[returnSize++] = ')';
    } else {
        returnSize += snprintf(pRetVal + returnSize, MAX_BUF_SIZE - returnSize, "%s", fractionPart);
    }

    //
    freeAll(remainderIndexMap);

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int numerator;
        int denominator;
    } testCase[] = {{1, 2}, {2, 1}, {4, 333}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: numerator = 1, denominator = 2
     *  Output: "0.5"
     *
     *  Input: numerator = 2, denominator = 1
     *  Output: "2"
     *
     *  Input: numerator = 4, denominator = 333
     *  Output: "0.(012)"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: numerator = %d, denominator = %d\n", testCase[i].numerator, testCase[i].denominator);

        pAnswer = fractionToDecimal(testCase[i].numerator, testCase[i].denominator);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
