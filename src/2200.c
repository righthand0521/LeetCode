#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findKDistantIndices(int* nums, int numsSize, int key, int k, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));

    int right = 0;
    int left = 0;
    for (int j = 0; j < numsSize; ++j) {
        if (nums[j] != key) {
            continue;
        }

        right = fmax(left, j - k);
        left = fmin(numsSize - 1, j + k) + 1;
        for (int i = right; i < left; ++i) {
            pRetVal[(*returnSize)++] = i;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int key;
        int k;
        int returnSize;
    } testCase[] = {{{3, 4, 9, 1, 3, 9, 5}, 7, 9, 1, 0}, {{2, 2, 2, 2, 2}, 5, 2, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,4,9,1,3,9,5], key = 9, k = 1
     *  Output: [1,2,3,4,5,6]
     *
     *  Input: nums = [2,2,2,2,2], key = 2, k = 2
     *  Output: [0,1,2,3,4]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], key = %d, k = %d\n", testCase[i].key, testCase[i].k);

        pAnswer = findKDistantIndices(testCase[i].nums, testCase[i].numsSize, testCase[i].key, testCase[i].k,
                                      &testCase[i].returnSize);
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
