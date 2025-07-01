#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    char *key;
    UT_hash_handle hh;
};
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%s\n", pFree->key);
        HASH_DEL(pFree, current);
        free(current->key);
        free(current);
    }
}
int numDifferentIntegers(char *word) {
    int retVal = 0;

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    char *pKey;

    int wordSize = strlen(word);
    int left = 0, right;
    while (1) {
        while ((left < wordSize) && (isdigit(word[left]) == 0)) {
            left++;
        }
        if (left == wordSize) {
            break;
        }

        right = left;
        while ((right < wordSize) && (isdigit(word[right]) != 0)) {
            right++;
        }

        while ((right - left > 1) && (word[left] == '0')) {
            left++;
        }
        pKey = (char *)malloc((right - left + 1) * sizeof(char));
        if (pKey == NULL) {
            perror("malloc");
            break;
        }
        strncpy(pKey, word + left, right - left);
        pKey[right - left] = '\0';
        pTemp = NULL;
        HASH_FIND_STR(pHashTable, pKey, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                break;
            }
            pTemp->key = pKey;
            HASH_ADD_STR(pHashTable, key, pTemp);
        } else {
            free(pKey);
            pKey = NULL;
        }

        left = right;
    }

    retVal = HASH_COUNT(pHashTable);
    freeAll(pHashTable);

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        char *word;
    } testCase[] = {{"a123bc34d8ef34"}, {"leet1234code234"}, {"a1b01c001"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: word = "a123bc34d8ef34"
     *  Output: 3
     *
     *  Input: word = "leet1234code234"
     *  Output: 2
     *
     *  Input: word = "a1b01c001"
     *  Output: 1
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: word = \"%s\"\n", testCase[i].word);

        answer = numDifferentIntegers(testCase[i].word);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
