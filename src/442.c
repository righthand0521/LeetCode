#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findDuplicates(int *nums, int numsSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int *)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));

    int idx;
    int i;
    for (i = 0; i < numsSize; ++i) {
        idx = abs(nums[i]);
        if (nums[idx - 1] > 0) {
            // in the range [1, n]
            nums[idx - 1] *= (-1);
        } else {
            // each integer appears once or twice
            pRetVal[(*returnSize)++] = idx;
        }
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{4, 3, 2, 7, 8, 2, 3, 1}, 8, 0}, {{1, 1, 2}, 3, 0}, {{1}, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [4,3,2,7,8,2,3,1]
     *  Output: [2,3]
     *
     *  Input: nums = [1,1,2]
     *  Output: [1]
     *
     *  Input: nums = [1]
     *  Output: []
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = findDuplicates(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
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
