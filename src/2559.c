#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* vowelStrings(char** words, int wordsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)calloc(queriesSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    (*returnSize) = queriesSize;

    int prefixSum[wordsSize];
    memset(prefixSum, 0, sizeof(prefixSum));

    char start, end;
    int vowelCount = 0;
    for (int i = 0; i < wordsSize; i++) {
        start = words[i][0];
        end = words[i][strlen(words[i]) - 1];
        if ((start == 'a') || (start == 'e') || (start == 'i') || (start == 'o') || (start == 'u')) {
            if ((end == 'a') || (end == 'e') || (end == 'i') || (end == 'o') || (end == 'u')) {
                vowelCount++;
            }
        }
        prefixSum[i] = vowelCount;
    }

    for (int i = 0; i < queriesSize; i++) {
        pRetVal[i] = prefixSum[queries[i][1]];
        if (queries[i][0] != 0) {
            pRetVal[i] -= prefixSum[queries[i][0] - 1];
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char* words[MAX_SIZE];
        int wordsSize;
        int queries[MAX_SIZE][2];
        int queriesSize;
        int queriesColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{{"aba", "bcb", "ece", "aa", "e"}, 5, {{0, 2}, {1, 4}, {1, 1}}, 3, {2, 2, 2}, 0},
                    {{"a", "e", "i"}, 3, {{0, 2}, {0, 1}, {2, 2}}, 3, {2, 2, 2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["aba","bcb","ece","aa","e"], queries = [[0,2],[1,4],[1,1]]
     *  Output: [2,3,0]
     *
     *  Input: words = ["a","e","i"], queries = [[0,2],[0,1],[2,2]]
     *  Output: [3,2,1]
     */

    int** pQueries = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("], queries =  [");
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].queriesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].queries[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pQueries = (int**)malloc(testCase[i].queriesSize * sizeof(int*));
        if (pQueries == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            pQueries[j] = (int*)malloc(testCase[i].queriesColSize[j] * sizeof(int));
            if (pQueries[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pQueries[k]) {
                        free(pQueries[k]);
                        pQueries[k] = NULL;
                    }
                }
                free(pQueries);
                pQueries = NULL;
                return EXIT_FAILURE;
            }
            memset(pQueries[j], 0, testCase[i].queriesColSize[j] * sizeof(int));
            memcpy(pQueries[j], testCase[i].queries[j], testCase[i].queriesColSize[j] * sizeof(int));
        }
        pAnswer = vowelStrings(testCase[i].words, testCase[i].wordsSize, pQueries, testCase[i].queriesSize,
                               testCase[i].queriesColSize, &testCase[i].returnSize);
        printf("Output:[");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            if (pQueries[j]) {
                free(pQueries[j]);
                pQueries[j] = NULL;
            }
        }
        free(pQueries);
        pQueries = NULL;
    }

    return EXIT_SUCCESS;
}
