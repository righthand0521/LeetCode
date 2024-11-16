#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *resultsArray(int *nums, int numsSize, int k, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = numsSize - k + 1;
    pRetVal = (int *)malloc(((*returnSize) * sizeof(int)));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, -1, ((*returnSize) * sizeof(int)));

    int consecutiveCount = 0;
    for (int i = 0; i < numsSize; ++i) {
        if ((i != 0) && (nums[i - 1] + 1 == nums[i])) {
            consecutiveCount++;
        } else {
            consecutiveCount = 1;
        }

        if (consecutiveCount >= k) {
            pRetVal[i - k + 1] = nums[i];
        }
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
        int returnSize;
    } testCase[] = {{{1, 2, 3, 4, 3, 2, 5}, 7, 3, 0}, {{2, 2, 2, 2, 2}, 5, 4, 0}, {{3, 2, 3, 2, 3, 2}, 6, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3,4,3,2,5], k = 3
     *  Output: [3,4,-1,-1,-1]
     *
     *  Input: nums = [2,2,2,2,2], k = 4
     *  Output: [-1,-1]
     *
     *  Input: nums = [3,2,3,2,3,2], k = 2
     *  Output: [-1,3,-1,3,-1]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        pAnswer = resultsArray(testCase[i].nums, testCase[i].numsSize, testCase[i].k, &testCase[i].returnSize);
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
