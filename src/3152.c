#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* isArraySpecial(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    bool* pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (bool*)malloc(queriesSize * sizeof(bool));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (queriesSize) * sizeof(bool));

    int prefix[numsSize];
    memset(prefix, 0, sizeof(prefix));
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] % 2 == nums[i - 1] % 2) {
            prefix[i] = prefix[i - 1] + 1;  // new violative index found
        } else {
            prefix[i] = prefix[i - 1];
        }
    }

    bool value;
    int start, end;
    for (int i = 0; i < queriesSize; ++i) {
        start = queries[i][0];
        end = queries[i][1];
        value = (prefix[end] - prefix[start] == 0);
        pRetVal[(*returnSize)] = value;
        (*returnSize) += 1;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int queries[MAX_SIZE][2];
        int queriesSize;
        int queriesColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{{3, 4, 1, 2, 6}, 5, {{0, 4}}, 1, {2}, 0}, {{4, 3, 1, 6}, 4, {{0, 2}, {2, 3}}, 2, {2, 2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,4,1,2,6], queries = [[0,4]]
     *  Output: [false]
     *
     *  Input: nums = [4,3,1,6], queries = [[0,2],[2,3]]
     *  Output: [false,true]
     */

    int** pQueries = NULL;
    bool* pAnswer = NULL;
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
        pAnswer = isArraySpecial(testCase[i].nums, testCase[i].numsSize, pQueries, testCase[i].queriesSize,
                                 testCase[i].queriesColSize, &testCase[i].returnSize);
        printf("Output:[");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", (pAnswer[j] == true ? "true" : "false"));
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
