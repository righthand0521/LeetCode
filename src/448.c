#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

#if 1
    *returnSize = numsSize;

    int idx;
    int i;
    for (i = 0; i < numsSize; ++i) {
        idx = abs(nums[i]) - 1;
        if (nums[idx] > 0) {
            nums[idx] = 0 - nums[idx];
            (*returnSize)--;
        }
    }
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    idx = 0;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] > 0) {
            pRetVal[idx++] = i + 1;
        }
    }
#else
    *returnSize = numsSize;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int i;
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = i + 1;
    }

    for (i = 0; i < numsSize; ++i) {
        pRetVal[nums[i] - 1] = 0;
    }

    *returnSize = 0;
    for (i = 0; i < numsSize; ++i) {
        if (pRetVal[i] != 0) {
            pRetVal[*returnSize] = pRetVal[i];
            (*returnSize)++;
        }
    }
#endif

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{4, 3, 2, 7, 8, 2, 3, 1}, 8, 0}, {{1, 1}, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = findDisappearedNumbers(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
        printf("Output = [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        if (pAnswer != NULL) {
            free(pAnswer);
            pAnswer = NULL;
        }
    }

    return EXIT_SUCCESS;
}
