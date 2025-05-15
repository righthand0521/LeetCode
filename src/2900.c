#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** getLongestSubsequence(char** words, int wordsSize, int* groups, int groupsSize, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (char**)malloc(groupsSize * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int returnColSize = strlen(words[0]) + 1;
    pRetVal[(*returnSize)] = (char*)malloc(returnColSize * sizeof(char));
    if (pRetVal[(*returnSize)] == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset(pRetVal[(*returnSize)], 0, (returnColSize * sizeof(char)));
    snprintf(pRetVal[(*returnSize)++], returnColSize, "%s", words[0]);

    for (int i = 1; i < groupsSize; ++i) {
        if (groups[i] == groups[i - 1]) {
            continue;
        }

        returnColSize = strlen(words[i]) + 1;
        pRetVal[(*returnSize)] = (char*)malloc(returnColSize * sizeof(char));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            for (int j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        memset(pRetVal[(*returnSize)], 0, (returnColSize * sizeof(char)));
        snprintf(pRetVal[(*returnSize)++], returnColSize, "%s", words[i]);
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* words[MAX_SIZE];
        int wordsSize;
        int groups[MAX_SIZE];
        int groupsSize;
        int returnSize;
    } testCase[] = {{{"e", "a", "b"}, 3, {0, 0, 1}, 3, 0}, {{"a", "b", "c", "d"}, 4, {1, 0, 1, 1}, 4, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["e","a","b"], groups = [0,0,1]
     *  Output: ["e","b"]
     *
     *  Input: words = ["a","b","c","d"], groups = [1,0,1,1]
     *  Output: ["a","b","c"]
     */

    char** pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("], groups = [");
        for (j = 0; j < testCase[i].groupsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].groups[j]);
        }
        printf("]\n");

        pAnswer = getLongestSubsequence(testCase[i].words, testCase[i].wordsSize, testCase[i].groups,
                                        testCase[i].groupsSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

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
