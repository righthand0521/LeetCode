#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* shuffle(int* nums, int numsSize, int n, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = numsSize;
    pRetVal = (int*)calloc((*returnSize), sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        (*returnSize) = 0;
        return pRetVal;
    }

    int i;
    for (i = 0; i < n; ++i) {
        pRetVal[2 * i] = nums[i];
        pRetVal[2 * i + 1] = nums[i + n];
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_NUMSSIZE (500)
    struct testCaseType {
        int nums[MAX_NUMSSIZE];
        int numsSize;
        int n;
        int returnSize;
    } testCase[] = {{{2, 5, 1, 3, 4, 7}, 6, 3, 0}, {{1, 2, 3, 4, 4, 3, 2, 1}, 8, 4, 0}, {{1, 1, 2, 2}, 4, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int* pAnswer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], , n = %d\n", testCase[i].n);

        pAnswer = shuffle(testCase[i].nums, testCase[i].numsSize, testCase[i].n, &testCase[i].returnSize);
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
