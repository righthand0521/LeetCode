#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void moveZeroes(int* nums, int numsSize) {
    int lastNonZeroFoundAt = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] != 0) {
            nums[lastNonZeroFoundAt++] = nums[i];
        }
    }
    for (i = lastNonZeroFoundAt; i < numsSize; ++i) {
        nums[i] = 0;
    }
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{0, 1, 0, 3, 12}, 5}, {{0}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [0,1,0,3,12]
     *  Output: [1,3,12,0,0]
     *
     *  Input: nums = [0]
     *  Output: [0]
     */

    int* pInput = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pInput = (int*)malloc(testCase[i].numsSize * sizeof(int));
        if (pInput == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        memset(pInput, 0, testCase[i].numsSize * sizeof(int));
        memcpy(pInput, testCase[i].nums, testCase[i].numsSize * sizeof(int));
        moveZeroes(pInput, testCase[i].numsSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pInput[j]);
        }
        printf("]\n");

        printf("\n");

        if (pInput) {
            free(pInput);
            pInput = NULL;
        }
    }

    return EXIT_SUCCESS;
}
