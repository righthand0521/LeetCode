#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 2;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    pRetVal[0] = -1;
    pRetVal[1] = -1;

    if (numsSize == 0) {
        return pRetVal;
    }
    int left, right, middle;

    left = 0;
    right = numsSize - 1;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (nums[middle] >= target) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    if (nums[right] != target) {
        return pRetVal;
    }
    pRetVal[0] = right;

    left = 0;
    right = numsSize - 1;
    while (left < right) {
        middle = right - (right - left) / 2;
        if (nums[middle] <= target) {
            left = middle;
        } else {
            right = middle - 1;
        }
    }
    if (nums[right] != target) {
        pRetVal[0] = -1;
        return pRetVal;
    }
    pRetVal[1] = left;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int target;
        int returnSize;
    } testCase[] = {{{5, 7, 7, 8, 8, 10}, 6, 8, 0},
                    {{5, 7, 7, 8, 8, 10}, 6, 6, 0},
                    {{}, 0, 0, 0},
                    {{1}, 1, 1, 0},
                    {{2, 2}, 2, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [5,7,7,8,8,10], target = 8
     *  Output: [3,4]
     *
     *  Input: nums = [5,7,7,8,8,10], target = 6
     *  Output: [-1,-1]
     *
     *  Input: nums = [], target = 0
     *  Output: [-1,-1]
     *
     *  Input: nums = [1], target = 1
     *  Output: [0,0]
     *
     *  Input: nums = [2,2], target = 2
     *  Output: [0,1]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], target = %d\n", testCase[i].target);

        pAnswer = searchRange(testCase[i].nums, testCase[i].numsSize, testCase[i].target, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", *(pAnswer + j));
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
