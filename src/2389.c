#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BINARY_SEARCH (1)
#define SORTING (1)
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* answerQueries(int* nums, int numsSize, int* queries, int queriesSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = queriesSize;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    qsort(nums, numsSize, sizeof(int), compareInteger);

#if (BINARY_SEARCH)
    printf("BINARY_SEARCH\n");

    int i;

    int prefixSum[numsSize];
    memset(prefixSum, 0, sizeof(prefixSum));
    prefixSum[0] = nums[0];
    for (i = 1; i < numsSize; ++i) {
        prefixSum[i] = nums[i] + prefixSum[i - 1];
    }

    int left, right, middle;
    for (i = 0; i < queriesSize; ++i) {
        left = 0;
        right = numsSize;
        while (left < right) {
            middle = left + (right - left) / 2;
            if (prefixSum[middle] <= queries[i]) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }

        pRetVal[i] = right;
    }

#elif (SORTING)
    printf("SORTING\n");

    int i, j;
    for (i = 0; i < queriesSize; ++i) {
        for (j = 0; j < numsSize; ++j) {
            if (queries[i] < nums[j]) {
                break;
            }
            queries[i] -= nums[j];
            ++pRetVal[i];
        }
    }
#endif

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int queries[MAX_SIZE];
        int queriesSize;
        int returnSize;
    } testCase[] = {{{4, 5, 2, 1}, 4, {3, 10, 21}, 3, 0}, {{2, 3, 4, 5}, 4, {1}, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [4,5,2,1], queries = [3,10,21]
     *  Output: [2,3,4]
     *
     *  Input: nums = [2,3,4,5], queries = [1]
     *  Output: [0]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums =  [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], queries =  [");
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].queries[j]);
        }
        printf("]\n");

        pAnswer = answerQueries(testCase[i].nums, testCase[i].numsSize, testCase[i].queries, testCase[i].queriesSize,
                                &testCase[i].returnSize);
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
