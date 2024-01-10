#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArrayByParity(int* nums, int numsSize, int* returnSize) {
    int* pRetVal;

    (*returnSize) = numsSize;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, (*returnSize) * sizeof(int));

    int head = 0;
    int tail = numsSize - 1;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if ((nums[i] % 2) == 0) {
            pRetVal[head++] = nums[i];
        } else {
            pRetVal[tail--] = nums[i];
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{3, 1, 2, 4}, 4, 0},    {{0}, 1, 0},          {{1, 5, 3, 7}, 4, 0},
                    {{1, 5, 9, 3, 7}, 5, 0}, {{2, 8, 4, 6}, 4, 0}, {{2, 8, 0, 4, 6}, 5, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,1,2,4]
     *  Output: [2,4,3,1]
     *
     *  Input: nums = [0]
     *  Output: [0]
     *
     *  Input: nums = [1,5,3,7]
     *  Output: [1,5,3,7]
     *
     *  Input: nums = [1,5,9,3,7]
     *  Output: [1,5,9,3,7]
     *
     *  Input: nums = [2,8,4,6]
     *  Output: [2, 8,4,6]
     *
     *  Input: nums = [2,8,0,4,6]
     *  Output: [2,8,0,4,6]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = sortArrayByParity(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
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
