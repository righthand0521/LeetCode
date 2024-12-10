#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_KEY_SIZE (32)  // 3 <= s.length <= 50
struct hashTable {
    char key[MAX_KEY_SIZE];
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%s: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int maximumLength(char* s) {
    int retVal = 0;

    struct hashTable* pHashTable = NULL;
    char character;
    int substringLength;
    int count;

    struct hashTable* pTmp;
    char key[MAX_KEY_SIZE];
    int sSize = strlen(s);
    int start, end;
    for (start = 0; start < sSize; ++start) {
        character = s[start];
        substringLength = 0;
        for (end = start; end < sSize; ++end) {
            // If the string is empty, or the current character is equal to the previously added character,
            // then add it to the map. Otherwise, break the iteration.
            if (character != s[end]) {
                break;
            }
            substringLength++;

            // s consists of only lowercase English letters.
            memset(key, 0, sizeof(key));
            snprintf(key, sizeof(key), "%c%d", character, substringLength);

            pTmp = NULL;
            HASH_FIND_STR(pHashTable, key, pTmp);
            if (pTmp == NULL) {
                pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
                if (pTmp == NULL) {
                    perror("malloc");
                    freeAll(pHashTable);
                    pHashTable = NULL;
                    return retVal;
                }
                strcpy(pTmp->key, key);
                pTmp->value = 0;
                HASH_ADD_STR(pHashTable, key, pTmp);
            }
            pTmp->value++;
        }
    }

    struct hashTable* pCurrent = NULL;
    pTmp = NULL;
    HASH_ITER(hh, pHashTable, pCurrent, pTmp) {
        sscanf(pHashTable->key, "%c%d", &character, &substringLength);
        count = pHashTable->value;
        if ((count >= 3) && (substringLength > retVal)) {
            retVal = substringLength;
        }

        HASH_DEL(pHashTable, pCurrent);
        free(pCurrent);
        pCurrent = NULL;
    }
    pHashTable = NULL;
    if (retVal == 0) {
        retVal = -1;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"aaaa"}, {"abcdef"}, {"abcaba"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "aaaa"
     *  Output: 2
     *
     *  Input: s = "abcdef"
     *  Output: -1
     *
     *  Input: s = "abcaba"
     *  Output: 1
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = maximumLength(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
