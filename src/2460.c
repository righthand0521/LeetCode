#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* applyOperations(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    int writeIndex = 0;  // Pointer to place non-zero elements
    for (int index = 0; index < numsSize; index++) {
        // Step 1: Merge adjacent equal elements if they are non-zero
        if ((index < numsSize - 1) && (nums[index] == nums[index + 1]) && (nums[index] != 0)) {
            nums[index] *= 2;
            nums[index + 1] = 0;
        }

        // Step 2: Shift non-zero elements to the front
        int tmp;
        if (nums[index] != 0) {
            if (index != writeIndex) {
                tmp = nums[index];
                nums[index] = nums[writeIndex];
                nums[writeIndex] = tmp;
            }
            writeIndex++;
        }
    }
    (*returnSize) = numsSize;
    pRetVal = nums;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{1, 2, 2, 1, 1, 0}, 6, 0}, {{0, 1}, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,2,1,1,0]
     *  Output: [1,4,2,0,0,0]
     *
     *  Input: nums = [0,1]
     *  Output: [1,0]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = applyOperations(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        // free(pAnswer);
        // pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
