#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define DYNAMIC_PROGRAMMING_SUBSTR (1)
#if (DYNAMIC_PROGRAMMING_SUBSTR)
// 1 <= words[i].length <= 30
#define MAX_LENGTH (30 + 1)
struct hashStruct {
    char key[MAX_LENGTH];
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashStruct* pFree) {
    struct hashStruct* current;
    struct hashStruct* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        HASH_DEL(pFree, current);
        free(current);
    }
}
#endif
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findAllConcatenatedWordsInADict(char** words, int wordsSize, int* returnSize) {
    char** pRetVal = NULL;

    int i, j, k;

    //
    (*returnSize) = wordsSize;
    pRetVal = (char**)malloc((*returnSize) * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }

#if (DYNAMIC_PROGRAMMING_SUBSTR)
    //
    struct hashStruct* pWordsHashTable = NULL;
    struct hashStruct* pWord;
    for (i = 0; i < wordsSize; ++i) {
        pWord = NULL;
        HASH_FIND_STR(pWordsHashTable, words[i], pWord);
        pWord = (struct hashStruct*)malloc(sizeof(struct hashStruct));
        if (pWord == NULL) {
            perror("malloc");
            freeAll(pWordsHashTable);
            free(pRetVal);
            pRetVal = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        snprintf(pWord->key, MAX_LENGTH, "%s", words[i]);
        pWord->value = 1;
        HASH_ADD_STR(pWordsHashTable, key, pWord);
    }

    //
    int len;
    int* dp = NULL;
    char* buf = NULL;
    int bufSize = 0;
    int exist = 0;
    struct hashStruct* pFind;
    (*returnSize) = 0;
    for (i = 0; i < wordsSize; ++i) {
        len = strlen(words[i]);

        dp = (int*)malloc((len + 1) * sizeof(int));
        if (dp == NULL) {
            perror("malloc");
            freeAll(pWordsHashTable);
            free(pRetVal);
            pRetVal = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        memset(dp, 0, ((len + 1) * sizeof(int)));
        dp[0] = 1;

        for (j = 1; j <= len; ++j) {
            for (k = (j == len ? 1 : 0); k < j; ++k) {
                if (dp[j] == 1) {
                    break;
                }

                bufSize = j - k + 1;
                buf = (char*)malloc(bufSize * sizeof(char));
                if (buf == NULL) {
                    perror("malloc");
                    freeAll(pWordsHashTable);
                    free(dp);
                    dp = NULL;
                    free(pRetVal);
                    pRetVal = NULL;
                    (*returnSize) = 0;
                    return pRetVal;
                }
                memset(buf, 0, (bufSize * sizeof(char)));
                memcpy(buf, words[i] + k, ((bufSize - 1) * sizeof(char)));

                exist = 0;
                pFind = NULL;
                HASH_FIND_STR(pWordsHashTable, buf, pFind);
                if (pFind != NULL) {
                    exist = 1;
                }
                dp[j] = dp[k] & exist;

                free(buf);
                buf = NULL;
            }
        }

        if (dp[len] == 1) {
            pRetVal[(*returnSize)] = (char*)malloc((len + 1) * sizeof(char));
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                for (j = 0; j < (*returnSize); ++j) {
                    if (pRetVal[j]) {
                        free(pRetVal[j]);
                        pRetVal[j] = NULL;
                    }
                }
                freeAll(pWordsHashTable);
                free(dp);
                dp = NULL;
                free(pRetVal);
                pRetVal = NULL;
                (*returnSize) = 0;
                return pRetVal;
            }
            memset(pRetVal[(*returnSize)], 0, ((len + 1) * sizeof(char)));
            memcpy(pRetVal[(*returnSize)], words[i], ((len + 1) * sizeof(char)));
            (*returnSize)++;
        }

        free(dp);
        dp = NULL;
    }

    //
    freeAll(pWordsHashTable);
#else
    //
    int pWordLength;
    for (i = 0; i < (*returnSize); ++i) {
        pWordLength = strlen(words[i]) + 1;
        pRetVal[i] = (char*)malloc(pWordLength * sizeof(char));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                if (pRetVal[j]) {
                    free(pRetVal[j]);
                    pRetVal[j] = NULL;
                }
            }
            free(pRetVal);
            pRetVal = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        memset(pRetVal[i], 0, (pWordLength * sizeof(char)));
    }
#endif

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_WORDS_ROW (int)(1e4)
#define MAX_WORDS_COL (30)
    struct testCaseType {
        char words[MAX_WORDS_ROW][MAX_WORDS_COL];
        int wordsSize;
        int returnSize;
    } testCase[] = {
        {{"cat", "cats", "catsdogcats", "dog", "dogcatsdog", "hippopotamuses", "rat", "ratcatdogcat"}, 8, 0},
        {{"cat", "dog", "catdog"}, 3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char** pWords = NULL;
    int pWordLength;
    char** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("]\n");

        pWords = (char**)malloc(testCase[i].wordsSize * sizeof(char*));
        if (pWords == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            pWordLength = strlen(testCase[i].words[j]) + 1;
            pWords[j] = (char*)malloc(pWordLength * sizeof(char));
            if (pWords[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pWords[k]) {
                        free(pWords[k]);
                        pWords[k] = NULL;
                    }
                }
                free(pWords);
                pWords = NULL;
                return EXIT_FAILURE;
            }
            memset(pWords[j], 0, (pWordLength * sizeof(char)));
            memcpy(pWords[j], testCase[i].words[j], (pWordLength * sizeof(char)));
        }
        pAnswer = findAllConcatenatedWordsInADict(pWords, testCase[i].wordsSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].wordsSize; ++j) {
            if (pWords[j]) {
                free(pWords[j]);
            }
        }
        free(pWords);
        pWords = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            if (pAnswer[j]) {
                free(pAnswer[j]);
            }
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
