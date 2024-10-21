#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_KEY_SIZE (16 + 4)  // 1 <= s.length <= 16
struct hashTable {
    char key[MAX_KEY_SIZE];
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%s\n", pFree->key);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int backtrack(char* s, int start, struct hashTable** pSeen) {
    int retVal = 0;

    int sSize = strlen(s);

    // Base case: If we reach the end of the string, return 0 (no more substrings to add)
    if (start == sSize) {
        return retVal;
    }

    struct hashTable* pTmp;
    char substring[sSize + 1];
    int end;
    for (end = start + 1; end <= sSize; ++end) {
        // Try every possible substring starting from 'start'
        memset(substring, 0, sizeof(substring));
        snprintf(substring, end - start + 1, "%s", s + start);

        // If the substring is unique
        pTmp = NULL;
        HASH_FIND_STR(*pSeen, substring, pTmp);
        if (pTmp != NULL) {
            continue;
        }
        pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTmp == NULL) {
            perror("malloc");
            return retVal;
        }
        snprintf(pTmp->key, MAX_KEY_SIZE, "%s", substring);

        // Add the substring to the seen set
        HASH_ADD_STR(*pSeen, key, pTmp);

        // Recursively count unique substrings from the next position
        retVal = fmax(retVal, 1 + backtrack(s, end, pSeen));

        // Backtrack: remove the substring from the seen set
        pTmp = NULL;
        HASH_FIND_STR(*pSeen, substring, pTmp);
        if (pTmp == NULL) {
            continue;
        }
        HASH_DEL(*pSeen, pTmp);
        free(pTmp);
    }

    return retVal;
}
int maxUniqueSplit(char* s) {
    int retVal = 0;

    struct hashTable* pSeen = NULL;
    retVal = backtrack(s, 0, &pSeen);

    //
    freeAll(pSeen);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (16)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"ababccc"}, {"aba"}, {"aa"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "ababccc"
     *  Output: 5
     *
     *  Input: s = "aba"
     *  Output: 2
     *
     *  Input: s = "aa"
     *  Output: 1
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = maxUniqueSplit(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
