#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getAverages(int* nums, int numsSize, int k, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = numsSize;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, -1, ((*returnSize) * sizeof(int)));

    int i;

    // n == nums.length, 1 <= n <= 10^5, 0 <= nums[i], k <= 10^5
    long long prefixSum[numsSize + 1];
    memset(prefixSum, 0, sizeof(prefixSum));
    for (i = 0; i < numsSize; ++i) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    for (i = k; i < numsSize - k; ++i) {
        pRetVal[i] = (prefixSum[i + k + 1] - prefixSum[i - k]) / (2 * k + 1);
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
        int returnSize;
    } testCase[] = {{{7, 4, 3, 9, 1, 8, 5, 2, 6}, 9, 3, 0}, {{100000}, 1, 0, 0}, {{8}, 1, 100000, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [7,4,3,9,1,8,5,2,6], k = 3
     *  Output: [-1,-1,-1,5,4,4,-1,-1,-1]
     *
     *  Input: nums = [100000], k = 0
     *  Output: [100000]
     *
     *  Input: nums = [8], k = 100000
     *  Output: [-1]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        pAnswer = getAverages(testCase[i].nums, testCase[i].numsSize, testCase[i].k, &testCase[i].returnSize);
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
