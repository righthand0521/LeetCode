#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#ifndef HASH_H
#define HASH_H

typedef struct {
    char *key;
    int value;
    UT_hash_handle hh;
} HashItem;
void freeAll(HashItem *pFree) {
    HashItem *pCurrent;
    HashItem *pTmp;
    HASH_ITER(hh, pFree, pCurrent, pTmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, pCurrent);
        free(pCurrent);
    }
}
#endif  // HASH_H
static int compareStringLength(const void *pa, const void *pb) {
    // ascending order
    return strlen(*(char **)pa) - strlen(*(char **)pb);
}
int longestStrChain(char **words, int wordsSize) {
    int retVal = 0;

    HashItem *pCount = NULL;

    qsort(words, wordsSize, sizeof(char *), compareStringLength);

    int wordLength;
    int previousValue, wordValue;
    char previous[32];  // 1 <= words[i].length <= 16
    HashItem *pTemp;
    int i, j;
    for (i = 0; i < wordsSize; i++) {
        pTemp = NULL;
        HASH_FIND_STR(pCount, words[i], pTemp);
        if (pTemp == NULL) {
            pTemp = (HashItem *)malloc(sizeof(HashItem));
            if (pTemp == NULL) {
                perror("malloc");
                goto _exit;
            }
            pTemp->key = words[i];
            pTemp->value = 1;
            HASH_ADD_STR(pCount, key, pTemp);
        }

        memset(previous, 0, sizeof(previous));
        wordLength = strlen(words[i]);
        for (j = 0; j < wordLength; j++) {
            strcpy(previous + j, words[i] + j + 1);

            pTemp = NULL;
            HASH_FIND_STR(pCount, previous, pTemp);
            if (pTemp != NULL) {
                previousValue = pTemp->value + 1;

                wordValue = 0;
                pTemp = NULL;
                HASH_FIND_STR(pCount, words[i], pTemp);
                if (pTemp != NULL) {
                    wordValue = pTemp->value;
                }

                if (previousValue > wordValue) {
                    pTemp = NULL;
                    HASH_FIND_STR(pCount, words[i], pTemp);
                    if (pTemp == NULL) {
                        pTemp = (HashItem *)malloc(sizeof(HashItem));
                        if (pTemp == NULL) {
                            perror("malloc");
                            goto _exit;
                        }
                        pTemp->key = words[i];
                        pTemp->value = previousValue;
                        HASH_ADD_STR(pCount, key, pTemp);
                    } else {
                        pTemp->value = previousValue;
                    }
                }
            }

            previous[j] = words[i][j];
        }

        pTemp = NULL;
        HASH_FIND_STR(pCount, words[i], pTemp);
        if (pTemp != NULL) {
            if (pTemp->value > retVal) {
                retVal = pTemp->value;
            }
        }
    }

_exit:
    freeAll(pCount);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char *words[MAX_SIZE];
        int wordsSize;
    } testCase[] = {{{"a", "b", "ba", "bca", "bda", "bdca"}, 6},
                    {{"xbc", "pcxbcf", "xb", "cxbc", "pcxbc"}, 5},
                    {{"abcd", "dbqca"}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["a","b","ba","bca","bda","bdca"]
     *  Output: 4
     *
     *  Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
     *  Output: 5
     *
     *  Input: words = ["abcd","dbqca"]
     *  Output: 1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("]\n");

        answer = longestStrChain(testCase[i].words, testCase[i].wordsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
