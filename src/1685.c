#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *getSumAbsoluteDifferences(int *nums, int numsSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    int i;

    pRetVal = (int *)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));

    int prefixSum[numsSize];
    memset(prefixSum, 0, sizeof(prefixSum));
    prefixSum[0] = nums[0];
    for (i = 1; i < numsSize; ++i) {
        prefixSum[i] = prefixSum[i - 1] + nums[i];
    }

    int left, right;
    for (i = 0; i < numsSize; ++i) {
        left = (nums[i] * i) - (prefixSum[i] - nums[i]);
        right = (prefixSum[numsSize - 1] - prefixSum[i]) - (nums[i] * (numsSize - 1 - i));
        pRetVal[(*returnSize)++] = left + right;
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{2, 3, 5}, 3, 0}, {{1, 4, 6, 8, 10}, 5, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,3,5]
     *  Output: [4,3,5]
     *
     *  Input: nums = [1,4,6,8,10]
     *  Output: [24,15,13,15,21]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = getSumAbsoluteDifferences(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
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
