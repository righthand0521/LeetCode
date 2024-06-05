#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTERS (26)  // words[i] consists of lowercase English letters.
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** commonChars(char** words, int wordsSize, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    int i, j;

    int minFrequency[MAX_LETTERS];
    memset(minFrequency, 0, sizeof(minFrequency));
    for (i = 0; i < MAX_LETTERS; ++i) {
        minFrequency[i] = INT_MAX;
    }
    int frequency[MAX_LETTERS];
    int wordSize, idx;
    for (i = 0; i < wordsSize; ++i) {
        memset(frequency, 0, sizeof(frequency));
        wordSize = strlen(words[i]);
        for (j = 0; j < wordSize; ++j) {
            idx = words[i][j] - 'a';
            frequency[idx] += 1;
        }

        for (j = 0; j < MAX_LETTERS; ++j) {
            minFrequency[j] = fmin(minFrequency[j], frequency[j]);
        }
    }

    for (i = 0; i < MAX_LETTERS; ++i) {
        (*returnSize) += minFrequency[i];
    }
    pRetVal = (char**)malloc((*returnSize) * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    (*returnSize) = 0;
    for (i = 0; i < MAX_LETTERS; ++i) {
        for (j = 0; j < minFrequency[i]; ++j) {
            pRetVal[(*returnSize)] = (char*)malloc(2 * sizeof(char));
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                return pRetVal;
            }
            memset(pRetVal[(*returnSize)], 0, (2 * sizeof(char)));
            pRetVal[(*returnSize)][0] = i + 'a';
            (*returnSize) += 1;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* words[MAX_SIZE];
        int wordsSize;
        int returnSize;
    } testCase[] = {{{"bella", "label", "roller"}, 3, 0}, {{"cool", "lock", "cook"}, 3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["bella","label","roller"]
     *  Output: ["e","l","l"]
     *
     *  Input: words = ["cool","lock","cook"]
     *  Output: ["c","o"]
     */

    char** pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        //
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("]\n");

        pAnswer = commonChars(testCase[i].words, testCase[i].wordsSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        //
        printf("\n");

        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
