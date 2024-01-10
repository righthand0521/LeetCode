#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *majorityElement(int *nums, int numsSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    int i;

    /* Boyer–Moore majority vote algorithm
     *  https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm
     */
    int candidate1 = 0;
    int count1 = 0;
    int candidate2 = 0;
    int count2 = 0;
    for (i = 0; i < numsSize; ++i) {
        if ((count1 > 0) && (candidate1 == nums[i])) {
            ++count1;
        } else if ((count2 > 0) && (candidate2 == nums[i])) {
            ++count2;
        } else if (count1 == 0) {
            candidate1 = nums[i];
            ++count1;
        } else if (count2 == 0) {
            candidate2 = nums[i];
            ++count2;
        } else {
            --count1;
            --count2;
        }
    }

    int check1 = 0;
    int check2 = 0;
    for (i = 0; i < numsSize; ++i) {
        if ((nums[i] == candidate1) && (count1 > 0)) {
            ++check1;
        } else if ((nums[i] == candidate2) && (count2 > 0)) {
            ++check2;
        }
    }

    pRetVal = (int *)malloc(2 * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (2 * sizeof(int)));
    if (check1 > numsSize / 3) {
        pRetVal[(*returnSize)++] = candidate1;
    }
    if (check2 > numsSize / 3) {
        pRetVal[(*returnSize)++] = candidate2;
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{3, 2, 3}, 3, 0}, {{1}, 1, 0}, {{1, 2}, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,2,3]
     *  Output: [3]
     *
     *  Input: nums = [1]
     *  Output: [1]
     *
     *  Input: nums = [1,2]
     *  Output: [1,2]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = majorityElement(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
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
