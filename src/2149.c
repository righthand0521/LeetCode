#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *rearrangeArray(int *nums, int numsSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int *)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));

    int positive = 0;
    int negative = 1;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] > 0) {
            pRetVal[positive] = nums[i];
            positive += 2;
        } else {
            pRetVal[negative] = nums[i];
            negative += 2;
        }
        (*returnSize)++;
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(2 * 100000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{3, 1, -2, -5, 2, -4}, 6, 0}, {{-1, 1}, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,1,-2,-5,2,-4]
     *  Output: [3,-2,1,-5,2,-4]
     *
     *  Input: nums = [-1,1]
     *  Output: [1,-1]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = rearrangeArray(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
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
