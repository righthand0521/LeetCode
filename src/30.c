#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_WORD_SIZE (32)  // 1 <= words[i].length <= 30
struct hashTable {
    char key[MAX_WORD_SIZE];
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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int wordLength = strlen(words[0]);
    int sLength = strlen(s);

    pRetVal = (int*)malloc(sLength * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (sLength * sizeof(int)));

    struct hashTable* pDiff = NULL;
    struct hashTable* pEntry = NULL;
    char word[MAX_WORD_SIZE];
    int pos = 0;
    int i, j, start;
    for (i = 0; i < wordLength; i++) {
        if (i + wordsSize * wordLength > sLength) {
            break;
        }

        memset(word, 0, sizeof(word));
        for (j = 0; j < wordsSize; j++) {
            snprintf(word, wordLength + 1, "%s", s + i + j * wordLength);

            pEntry = NULL;
            HASH_FIND_STR(pDiff, word, pEntry);
            if (pEntry == NULL) {
                pEntry = (struct hashTable*)malloc(sizeof(struct hashTable));
                if (pEntry == NULL) {
                    perror("malloc");
                    freeAll(pDiff);
                    pDiff = NULL;
                    return pRetVal;
                }
                strcpy(pEntry->key, word);
                pEntry->value = 0;
                HASH_ADD_STR(pDiff, key, pEntry);
            }
            pEntry->value++;
        }

        for (j = 0; j < wordsSize; j++) {
            pEntry = NULL;
            HASH_FIND_STR(pDiff, words[j], pEntry);
            if (pEntry == NULL) {
                pEntry = (struct hashTable*)malloc(sizeof(struct hashTable));
                if (pEntry == NULL) {
                    perror("malloc");
                    freeAll(pDiff);
                    pDiff = NULL;
                    return pRetVal;
                }
                strcpy(pEntry->key, words[j]);
                pEntry->value = 0;
                HASH_ADD_STR(pDiff, key, pEntry);
            }
            pEntry->value--;

            if (pEntry->value == 0) {
                HASH_DEL(pDiff, pEntry);
                free(pEntry);
            }
        }

        for (start = i; start < sLength - wordsSize * wordLength + 1; start += wordLength) {
            if (start != i) {
                memset(word, 0, sizeof(word));
                snprintf(word, wordLength + 1, "%s", s + start + (wordsSize - 1) * wordLength);

                pEntry = NULL;
                HASH_FIND_STR(pDiff, word, pEntry);
                if (NULL == pEntry) {
                    pEntry = (struct hashTable*)malloc(sizeof(struct hashTable));
                    if (pEntry == NULL) {
                        perror("malloc");
                        freeAll(pDiff);
                        pDiff = NULL;
                        return pRetVal;
                    }
                    strcpy(pEntry->key, word);
                    pEntry->value = 0;
                    HASH_ADD_STR(pDiff, key, pEntry);
                }
                pEntry->value++;

                if (pEntry->value == 0) {
                    HASH_DEL(pDiff, pEntry);
                    free(pEntry);
                }

                snprintf(word, wordLength + 1, "%s", s + start - wordLength);

                pEntry = NULL;
                HASH_FIND_STR(pDiff, word, pEntry);
                if (NULL == pEntry) {
                    pEntry = (struct hashTable*)malloc(sizeof(struct hashTable));
                    if (pEntry == NULL) {
                        perror("malloc");
                        freeAll(pDiff);
                        pDiff = NULL;
                        return pRetVal;
                    }
                    strcpy(pEntry->key, word);
                    pEntry->value = 0;
                    HASH_ADD_STR(pDiff, key, pEntry);
                }
                pEntry->value--;

                if (pEntry->value == 0) {
                    HASH_DEL(pDiff, pEntry);
                    free(pEntry);
                }
            }

            if (HASH_COUNT(pDiff) == 0) {
                pRetVal[pos++] = start;
            }
        }

        freeAll(pDiff);
        pDiff = NULL;
    }
    (*returnSize) = pos;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5000)
    struct testCaseType {
        char* s;
        char* words[MAX_SIZE];
        int wordsSize;
        int returnSize;
    } testCase[] = {{"barfoothefoobarman", {"foo", "bar"}, 2, 0},
                    {"wordgoodgoodgoodbestword", {"word", "good", "best", "word"}, 4, 0},
                    {"barfoofoobarthefoobarman", {"bar", "foo", "the"}, 3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "barfoothefoobarman", words = ["foo","bar"]
     *  Output: [0,9]
     *
     *  Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
     *  Output: []
     *
     *  Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
     *  Output: [6,9,12]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", words = [", testCase[i].s);
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("]\n");

        pAnswer = findSubstring(testCase[i].s, testCase[i].words, testCase[i].wordsSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
