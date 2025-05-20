#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isZeroArray(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    bool retVal = true;

    int deltaArray[numsSize + 1];
    memset(deltaArray, 0, sizeof(deltaArray));
    int left, right;
    for (int i = 0; i < queriesSize; i++) {
        left = queries[i][0];
        right = queries[i][1];
        deltaArray[left] += 1;
        deltaArray[right + 1] -= 1;
    }

    int operationCounts[numsSize + 1];
    memset(operationCounts, 0, sizeof(operationCounts));
    int currentOperations = 0;
    for (int i = 0; i < numsSize + 1; i++) {
        currentOperations += deltaArray[i];
        operationCounts[i] = currentOperations;
    }

    for (int i = 0; i < numsSize; i++) {
        if (operationCounts[i] < nums[i]) {
            retVal = false;
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int queries[MAX_SIZE][2];
        int queriesSize;
        int queriesColSize[MAX_SIZE];
    } testCase[] = {{{1, 0, 1}, 3, {{1, 3}, {0, 2}}, 2, {2, 2}}, {{4, 3, 2, 1}, 4, {{1, 3}, {0, 2}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,0,1], queries = [[0,2]]
     *  Output: true
     *
     *  Input: nums = [4,3,2,1], queries = [[1,3],[0,2]]
     *  Output: false
     */

    int** pQueries = NULL;
    bool answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
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
        answer = isZeroArray(testCase[i].nums, testCase[i].numsSize, pQueries, testCase[i].queriesSize,
                             testCase[i].queriesColSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

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
