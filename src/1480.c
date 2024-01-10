#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* runningSum(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    *returnSize = numsSize;
    pRetVal = (int*)malloc(*returnSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int i = 0;
    pRetVal[i] = nums[i];
    for (i = 1; i < numsSize; ++i) {
        pRetVal[i] = pRetVal[i - 1] + nums[i];
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{1, 2, 3, 4}, 4, 0}, {{1, 1, 1, 1, 1}, 5, 0}, {{3, 1, 2, 10, 1}, 5, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3,4]
     *  Output: [1,3,6,10]
     *
     *  Input: nums = [1,1,1,1,1]
     *  Output: [1,2,3,4,5]
     *
     *  Input: nums = [3,1,2,10,1]
     *  Output: [3,4,6,16,17]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = runningSum(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
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
