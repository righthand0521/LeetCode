#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sumEvenAfterQueries(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize,
                         int* returnSize) {
    int* pRetVal;
    *returnSize = queriesSize;
    pRetVal = (int*)malloc(*returnSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        *returnSize = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, *returnSize * sizeof(int));

    int i;
#if 1
    int sum = 0;
    for (i = 0; i < numsSize; ++i) {
        sum += (nums[i] % 2 == 0) ? nums[i] : 0;
    }

    int index;
    int value;
    for (i = 0; i < queriesSize; ++i) {
        index = queries[i][1];
        value = queries[i][0];
        if (nums[index] % 2 == 0) {
            if (value % 2 == 0) {
                sum += value;
            } else {
                sum -= nums[index];
            }
        } else {
            if (value % 2 == 0) {
                ;
            } else {
                sum += (nums[index] + value);
            }
        }
        nums[index] += value;
        pRetVal[i] = sum;
    }
#else
    int j;
    for (i = 0; i < queriesSize; ++i) {
        nums[queries[i][1]] += queries[i][0];
        for (j = 0; j < numsSize; ++j) {
            pRetVal[i] += (nums[j] % 2 == 0) ? nums[j] : 0;
        }
    }
#endif

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int queries[MAX_SIZE][2];
        int queriesSize;
        int queriesColSize;
        int returnSize;
    } testCase[] = {{{1, 2, 3, 4}, 4, {{1, 0}, {-3, 1}, {-4, 0}, {2, 3}}, 4, 2, 0}, {{1}, 1, {{4, 0}}, 1, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int* pAnswer = NULL;
    int** pQueries = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], ");
        printf("queries = [");
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            printf("[");
            for (k = 0; k < testCase[i].queriesColSize; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].queries[j][k]);
            }
            printf("]%s", (j == (testCase[i].queriesSize - 1)) ? "" : ",");
        }
        printf("]\n");

        pQueries = (int**)malloc(testCase[i].queriesSize * sizeof(int*));
        if (pQueries == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (k = 0; k < testCase[i].queriesSize; ++k) {
            pQueries[k] = (int*)malloc(testCase[i].queriesColSize * sizeof(int));
            if (pQueries[k] == NULL) {
                perror("malloc");
                for (k = 0; k < testCase[i].queriesSize; ++k) {
                    if (pQueries[k]) {
                        free(pQueries[k]);
                    }
                }
                free(pQueries);
                pQueries = NULL;
                return EXIT_FAILURE;
            }
            memset(pQueries[k], 0, testCase[i].queriesColSize * sizeof(int));
            memcpy(pQueries[k], testCase[i].queries[k], testCase[i].queriesColSize * sizeof(int));
        }
        pAnswer = sumEvenAfterQueries(testCase[i].nums, testCase[i].numsSize, pQueries, testCase[i].queriesSize,
                                      &testCase[i].queriesColSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        for (k = 0; k < testCase[i].queriesSize; ++k) {
            if (pQueries[k]) {
                free(pQueries[k]);
            }
        }
        free(pQueries);
        pQueries = NULL;

        if (pAnswer == NULL) {
            continue;
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
