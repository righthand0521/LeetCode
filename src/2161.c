#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* pivotArray(int* nums, int numsSize, int pivot, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int less = 0;
    int equal = 0;
    int greater = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] < pivot) {
            equal++;
        } else if (nums[i] == pivot) {
            greater++;
        }
    }
    greater += equal;

    pRetVal = (int*)calloc(numsSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] < pivot) {
            pRetVal[less] = nums[i];
            less++;
        } else if (nums[i] > pivot) {
            pRetVal[greater] = nums[i];
            greater++;
        } else {
            pRetVal[equal] = nums[i];
            equal++;
        }
    }
    (*returnSize) = numsSize;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int pivot;
        int returnSize;
    } testCase[] = {{{9, 12, 5, 10, 14, 3, 10}, 7, 10}, {{-3, 4, 3, 2}, 4, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [9,12,5,10,14,3,10], pivot = 10
     *  Output: [9,5,3,10,10,12,14]
     *
     *  Input: nums = [-3,4,3,2], pivot = 2
     *  Output: [-3,2,4,3]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], pivot = %d\n", testCase[i].pivot);

        pAnswer = pivotArray(testCase[i].nums, testCase[i].numsSize, testCase[i].pivot, &testCase[i].returnSize);
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
