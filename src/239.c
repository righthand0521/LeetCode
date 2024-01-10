#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *maxSlidingWindow(int *nums, int numsSize, int k, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int *)malloc((numsSize - k + 1) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((numsSize - k + 1) * sizeof(int)));

    int doubleEndedQueue[numsSize];
    memset(doubleEndedQueue, 0, sizeof(doubleEndedQueue));
    int doubleEndedQueueLeft = 0;
    int doubleEndedQueueRight = 0;

    int i;
    for (i = 0; i < k; ++i) {
        while ((doubleEndedQueueLeft < doubleEndedQueueRight) &&
               (nums[i] >= nums[doubleEndedQueue[doubleEndedQueueRight - 1]])) {
            doubleEndedQueueRight--;
        }
        doubleEndedQueue[doubleEndedQueueRight++] = i;
    }
    pRetVal[(*returnSize)++] = nums[doubleEndedQueue[doubleEndedQueueLeft]];

    for (i = k; i < numsSize; ++i) {
        while ((doubleEndedQueueLeft < doubleEndedQueueRight) &&
               (nums[i] >= nums[doubleEndedQueue[doubleEndedQueueRight - 1]])) {
            doubleEndedQueueRight--;
        }
        doubleEndedQueue[doubleEndedQueueRight++] = i;

        while (doubleEndedQueue[doubleEndedQueueLeft] <= i - k) {
            doubleEndedQueueLeft++;
        }
        pRetVal[(*returnSize)++] = nums[doubleEndedQueue[doubleEndedQueueLeft]];
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
        int returnSize;
    } testCase[] = {{{1, 3, -1, -3, 5, 3, 6, 7}, 8, 3, 0}, {{1}, 1, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
     *  Output: [3,3,5,5,6,7]
     *
     *  Input: nums = [1], k = 1
     *  Output: [1]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        pAnswer = maxSlidingWindow(testCase[i].nums, testCase[i].numsSize, testCase[i].k, &testCase[i].returnSize);
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
