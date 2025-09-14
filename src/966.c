#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_LENGTH (7 + 1)  // 1 <= wordlist[i].length, queries[i].length <= 7
struct hashStruct {
    char key[MAX_LENGTH];
    char value[MAX_LENGTH];
    UT_hash_handle hh;
};
void insertIfAbsent(struct hashStruct** map, const char* key, const char* value) {
    struct hashStruct* pTmp;
    HASH_FIND_STR(*map, key, pTmp);
    if (pTmp != NULL) {
        return;
    }
    pTmp = (struct hashStruct*)malloc(sizeof(struct hashStruct));
    if (pTmp == NULL) {
        perror("malloc");
        return;
    }
    snprintf(pTmp->key, sizeof(pTmp->key), "%s", key);
    snprintf(pTmp->value, sizeof(pTmp->value), "%s", value);
    HASH_ADD_STR(*map, key, pTmp);
}
void freeAll(struct hashStruct* pFree) {
    struct hashStruct* current;
    struct hashStruct* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%s: %s\n", current->key, current->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int isVowel(char c) {
    int retVal = 0;

    c = tolower((unsigned char)c);
    if ((c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u')) {
        retVal = 1;
    }

    return retVal;
}
void toLowerStr(const char* src, char* dst) {
    int i;
    for (i = 0; src[i]; i++) {
        dst[i] = tolower((unsigned char)src[i]);
    }
    dst[i] = '\0';
}
void devowel(const char* src, char* dst) {
    int i;
    for (i = 0; src[i]; i++) {
        char c = tolower((unsigned char)src[i]);
        dst[i] = isVowel(c) ? '*' : c;
    }
    dst[i] = '\0';
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** spellchecker(char** wordlist, int wordlistSize, char** queries, int queriesSize, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (char**)malloc(queriesSize * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    struct hashStruct* exactSet = NULL;
    struct hashStruct* caseMap = NULL;
    struct hashStruct* vowelMap = NULL;

    char lower[MAX_LENGTH];
    char vowelKey[MAX_LENGTH];
    for (int i = 0; i < wordlistSize; ++i) {
        memset(lower, 0, sizeof(lower));
        toLowerStr(wordlist[i], lower);

        memset(vowelKey, 0, sizeof(vowelKey));
        devowel(wordlist[i], vowelKey);

        insertIfAbsent(&exactSet, wordlist[i], wordlist[i]);
        insertIfAbsent(&caseMap, lower, wordlist[i]);
        insertIfAbsent(&vowelMap, vowelKey, wordlist[i]);
    }

    struct hashStruct* pTmp;
    for (int i = 0; i < queriesSize; ++i) {
        pTmp = NULL;
        HASH_FIND_STR(exactSet, queries[i], pTmp);
        if (pTmp != NULL) {
            pRetVal[i] = strdup(queries[i]);
            if (pRetVal[i] == NULL) {
                perror("strdup");
            }
            continue;
        }

        memset(lower, 0, sizeof(lower));
        toLowerStr(queries[i], lower);
        pTmp = NULL;
        HASH_FIND_STR(caseMap, lower, pTmp);
        if (pTmp != NULL) {
            pRetVal[i] = strdup(pTmp->value);
            if (pRetVal[i] == NULL) {
                perror("strdup");
            }
            continue;
        }

        memset(vowelKey, 0, sizeof(vowelKey));
        devowel(queries[i], vowelKey);
        pTmp = NULL;
        HASH_FIND_STR(vowelMap, vowelKey, pTmp);
        if (pTmp != NULL) {
            pRetVal[i] = strdup(pTmp->value);
            if (pRetVal[i] == NULL) {
                perror("strdup");
            }
        } else {
            pRetVal[i] = strdup("");
            if (pRetVal[i] == NULL) {
                perror("strdup");
            }
        }
    }
    (*returnSize) = queriesSize;

    //
    freeAll(exactSet);
    freeAll(caseMap);
    freeAll(vowelMap);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_LIST_SIZE (5000)
#define MAX_WORD_SIZE (int)(7 + 1)
    struct testCaseType {
        char wordlist[MAX_LIST_SIZE][MAX_WORD_SIZE];
        int wordlistSize;
        char queries[MAX_LIST_SIZE][MAX_WORD_SIZE];
        int queriesSize;
        int returnSize;
    } testCase[] = {{{"KiTe", "kite", "hare", "Hare"},
                     4,
                     {"kite", "Kite", "KiTe", "Hare", "HARE", "Hear", "hear", "keti", "keet", "keto"},
                     10,
                     0},
                    {{"yellow"}, 1, {"YellOw"}, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: wordlist = ["KiTe","kite","hare","Hare"],
     *  queries = ["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"]
     *  Output: ["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]
     *
     *  Input: wordlist = ["yellow"], queries = ["YellOw"]
     *  Output: ["yellow"]
     */

    char** pWordlist = NULL;
    char** pQueries = NULL;
    char** pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: wordlist = [");
        for (j = 0; j < testCase[i].wordlistSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].wordlist[j]);
        }
        printf("], queries =  [");
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].queries[j]);
        }
        printf("]\n");

        pWordlist = (char**)malloc(testCase[i].wordlistSize * sizeof(char*));
        if (pWordlist == NULL) {
            perror("malloc");
            goto exit_pWordlist;
        }
        for (j = 0; j < testCase[i].wordlistSize; ++j) {
            pWordlist[j] = strdup(testCase[i].wordlist[j]);
            if (pWordlist[j] == NULL) {
                perror("strdup");
                goto exit_pWordlist_loop;
            }
        }
        pQueries = (char**)malloc(testCase[i].queriesSize * sizeof(char*));
        if (pQueries == NULL) {
            perror("malloc");
            goto exit_pQueries;
        }
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            pQueries[j] = strdup(testCase[i].queries[j]);
            if (pQueries[j] == NULL) {
                perror("strdup");
                goto exit_pQueries_loop;
            }
        }

        pAnswer = spellchecker(pWordlist, testCase[i].wordlistSize, pQueries, testCase[i].queriesSize,
                               &testCase[i].returnSize);
        printf("Output:[");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].returnSize; ++j) {
            if (pAnswer[j]) {
                free(pAnswer[j]);
                pAnswer[j] = NULL;
            }
        }
        free(pAnswer);
        pAnswer = NULL;

    exit_pQueries_loop:
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            if (pQueries[j]) {
                free(pQueries[j]);
                pQueries[j] = NULL;
            }
        }
        free(pQueries);
    exit_pQueries:
        pQueries = NULL;

    exit_pWordlist_loop:
        for (j = 0; j < testCase[i].wordlistSize; ++j) {
            if (pWordlist[j]) {
                free(pWordlist[j]);
                pWordlist[j] = NULL;
            }
        }
        free(pWordlist);
    exit_pWordlist:
        pWordlist = NULL;
    }

    return EXIT_SUCCESS;
}
