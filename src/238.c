#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *productExceptSelf(int *nums, int numsSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int *)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));
    pRetVal[0] = 1;

    /*
     *   1  2  3  4
     *  x1 24 12  4 => 1 x 24 = 24
     *   1 x1 12  4 => 1 x 12 = 12
     *   1  2 x1  4 => 2 x  4 =  8
     *   1  2  6 x1 => 6 x  1 =  6
     */
    int i;
    for (i = 1; i < numsSize; ++i) {
        pRetVal[i] = pRetVal[i - 1] * nums[i - 1];
    }
    int tmp = 1;
    for (i = numsSize - 2; i >= 0; --i) {
        tmp *= nums[i + 1];
        pRetVal[i] *= tmp;
    }
    (*returnSize) = numsSize;

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{1, 2, 3, 4}, 4, 0}, {{-1, 1, 0, -3, 3}, 5, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3,4]
     *  Output: [24,12,8,6]
     *
     *  Input: nums = [-1,1,0,-3,3]
     *  Output: [0,0,9,0,0]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = productExceptSelf(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
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
