#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    char* val;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* pCurrent;
    struct hashTable* pTmp;
    HASH_ITER(hh, pFree, pCurrent, pTmp) {
        // printf("%d: %s\n", pFree->key, pFree->val);
        HASH_DEL(pFree, pCurrent);
        free(pCurrent);
    }
}
bool wordPattern(char* pattern, char* s) {
    bool retVal = false;

    //
    struct hashTable* pHashTableKey = NULL;
    struct hashTable* pHashTableVal = NULL;
    struct hashTable* pTemp;
    int key;
    char* val;

#define SEPARATED " "  // All the words in s are separated by a single space.
    char* pStr = strtok(s, SEPARATED);
    while ((*pattern) && (pStr != NULL)) {
        key = (*pattern);
        val = pStr;

        //
        pTemp = NULL;
        HASH_FIND_INT(pHashTableKey, &key, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                goto exit;
            }
            pTemp->key = key;
            pTemp->val = val;
            HASH_ADD_INT(pHashTableKey, key, pTemp);
        } else {
            if (strcmp(val, pTemp->val) != 0) {
                goto exit;
            }
        }

        //
        pTemp = NULL;
        HASH_FIND_STR(pHashTableVal, val, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                goto exit;
            }
            pTemp->key = key;
            pTemp->val = val;
            HASH_ADD_STR(pHashTableVal, val, pTemp);
        } else {
            if (key != pTemp->key) {
                goto exit;
            }
        }

        ++pattern;
        pStr = strtok(NULL, SEPARATED);
    }
    if ((*pattern) || (pStr != NULL)) {
        goto exit;
    }
    retVal = true;

exit:
    //
    freeAll(pHashTableKey);
    pHashTableKey = NULL;
    freeAll(pHashTableVal);
    pHashTableVal = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_PATTERN_SIZE (300)
#define MAX_S_SIZE (3000)
    struct testCaseType {
        char pattern[MAX_PATTERN_SIZE];
        char s[MAX_S_SIZE];
    } testCase[] = {{"abba", "dog cat cat dog"},
                    {"abba", "dog cat cat fish"},
                    {"aaaa", "dog cat cat dog"},
                    {"abba", "dog dog dog dog"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: pattern = "abba", s = "dog cat cat dog"
     *  Output: true
     *
     *  Input: pattern = "abba", s = "dog cat cat fish"
     *  Output: false
     *
     *  Input: pattern = "aaaa", s = "dog cat cat dog"
     *  Output: false
     *
     *  Input: pattern = "abba", s = "dog dog dog dog"
     *  Output: false
     */

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: pattern = \"%s\", s = \"%s\"\n", testCase[i].pattern, testCase[i].s);

        answer = wordPattern(testCase[i].pattern, testCase[i].s);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
