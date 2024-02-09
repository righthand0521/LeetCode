#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void *n1, const void *n2) {
    // ascending order
    return (*(int *)n1 > *(int *)n2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *largestDivisibleSubset(int *nums, int numsSize, int *returnSize) {
    int *pRetVal = NULL;

    //
    (*returnSize) = 0;

    //
    qsort(nums, numsSize, sizeof(int), &compareInteger);

    //
    int i, j;
    struct dpType {
        int subset[numsSize];
        int subsetSize;
    } dp[numsSize];
    memset(dp, 0, sizeof(dp));
    for (i = 0; i < numsSize; ++i) {
        dp[i].subset[dp[i].subsetSize++] = nums[i];
    }

    //
    int idx = 0;
    int tmp[numsSize];
    for (i = 0; i < numsSize; ++i) {
        for (j = 0; j < i; ++j) {
            if ((nums[i] % nums[j] == 0) && (dp[j].subsetSize >= dp[i].subsetSize)) {
                memcpy(dp[i].subset, dp[j].subset, sizeof(dp[i].subset));
                dp[i].subsetSize = dp[j].subsetSize;
                dp[i].subset[dp[i].subsetSize++] = nums[i];
            }
        }

        if ((*returnSize) < dp[i].subsetSize) {
            memset(tmp, 0, sizeof(tmp));
            memcpy(tmp, dp[i].subset, sizeof(tmp));
            (*returnSize) = dp[i].subsetSize;
            idx = i;
        }
    }

    //
    pRetVal = (int *)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));
    memcpy(pRetVal, dp[idx].subset, ((*returnSize) * sizeof(int)));

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{1, 2, 3}, 3, 0}, {{1, 2, 4, 8}, 4, 0}, {{4, 8, 10, 240}, 4, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3]
     *  Output: [1,2]
     *
     *  Input: nums = [1,2,4,8]
     *  Output: [1,2,4,8]
     *
     *  Input: nums = [4, 8, 10, 240]
     *  Output: [4,8,240]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = largestDivisibleSubset(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
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
