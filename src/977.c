#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortedSquares(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int left = 0;
    int right = numsSize - 1;
    int i;
    for (i = (numsSize - 1); i >= 0; --i) {
        if (abs(nums[left]) > abs(nums[right])) {
            pRetVal[i] = nums[left] * nums[left];
            ++left;
        } else {
            pRetVal[i] = nums[right] * nums[right];
            --right;
        }
    }
    (*returnSize) = numsSize;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{-4, -1, 0, 3, 10}, 5, 0}, {{-7, -3, 2, 3, 11}, 5, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [-4,-1,0,3,10]
     *  Output: [0,1,9,16,100]
     *
     *  Input: nums = [-7,-3,2,3,11]
     *  Output: [4,9,9,49,121]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = sortedSquares(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
        printf("[");
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
