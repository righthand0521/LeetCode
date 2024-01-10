#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH (100 + 4)
int compareChar(const void* c1, const void* c2) {
    // ascending order
    return (*(char*)c1 - *(char*)c2);
}
bool isAnagrams(char* pSrc, char* pDst) {
    int retVal = false;

    char sortSrc[MAX_LENGTH];
    memset(sortSrc, 0, sizeof(sortSrc));
    snprintf(sortSrc, sizeof(sortSrc), "%s", pSrc);
    qsort(sortSrc, strlen(sortSrc), sizeof(char), compareChar);

    char sortDst[MAX_LENGTH];
    memset(sortDst, 0, sizeof(sortDst));
    snprintf(sortDst, sizeof(sortDst), "%s", pDst);
    qsort(sortDst, strlen(sortDst), sizeof(char), compareChar);

    if (strcmp(sortSrc, sortDst) == 0) {
        retVal = true;
    }

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** removeAnagrams(char** words, int wordsSize, int* returnSize) {
    (*returnSize) = 1;

    int len;
    int i;
    for (i = 1; i < wordsSize; ++i) {
        if (isAnagrams(words[(*returnSize) - 1], words[i]) == true) {
            continue;
        }

        if ((*returnSize) != i) {
            free(words[(*returnSize)]);
            words[(*returnSize)] = NULL;

            len = strlen(words[i]) + 1;
            words[(*returnSize)] = (char*)malloc(len * sizeof(char));
            if (words[(*returnSize)] == NULL) {
                perror("malloc");
                return words;
            }
            memset(words[(*returnSize)], 0, len * sizeof(char));
            snprintf(words[(*returnSize)], len * sizeof(char), "%s", words[i]);
        }

        (*returnSize)++;
    }

    return words;
}

int main(int argc, char** argv) {
#define MAX_WORDS_SIZE (100)
#define MAX_WORDS_LENGTH (10)
    struct testCaseType {
        char words[MAX_WORDS_SIZE][MAX_WORDS_LENGTH];
        int wordsSize;
        int returnSize;
    } testCase[] = {{{"abba", "baba", "bbaa", "cd", "cd"}, 5, 0},
                    {{"a", "b", "c", "d", "e"}, 5, 0},
                    {{"z", "z", "z", "gsw", "wsg", "gsw", "krptu"}, 7, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["abba","baba","bbaa","cd","cd"]
     *  Output: ["abba","cd"]
     *
     *  Input: words = ["a","b","c","d","e"]
     *  Output: ["a","b","c","d","e"]
     *
     *  Input: words = ["z", "z", "z", "gsw", "wsg", "gsw", "krptu"]
     *  Output: ["z","gsw","krptu"]
     */

    char** pWords = NULL;
    char** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words =  [");
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
            pWords[j] = (char*)malloc((strlen(testCase[i].words[j]) + 1) * sizeof(char));
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
            memset(pWords[j], 0, (strlen(testCase[i].words[j]) + 1) * sizeof(char));
            memcpy(pWords[j], testCase[i].words[j], (strlen(testCase[i].words[j]) + 1) * sizeof(char));
        }
        pAnswer = removeAnagrams(pWords, testCase[i].wordsSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].wordsSize; ++j) {
            if (pWords[j]) {
                free(pWords[j]);
                pWords[j] = NULL;
            }
        }
        free(pWords);
        pWords = NULL;
    }

    return EXIT_SUCCESS;
}
