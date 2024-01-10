#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** summaryRanges(int* nums, int numsSize, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (char**)malloc(numsSize * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

#define MAX_RETURN_SIZE (32)  // -2^31 <= nums[i] <= 2^31 - 1
    char buf[MAX_RETURN_SIZE];
    int tmp;
    int idx = 0;
    while (idx < numsSize) {
        tmp = nums[idx];
        while ((idx + 1 < numsSize) && (nums[idx] + 1 == nums[idx + 1])) {
            ++idx;
        }

        memset(buf, 0, sizeof(buf));
        if (tmp == nums[idx]) {
            snprintf(buf, sizeof(buf), "%d", tmp);
        } else {
            snprintf(buf, sizeof(buf), "%d->%d", tmp, nums[idx]);
        }
        pRetVal[(*returnSize)] = (char*)malloc(MAX_RETURN_SIZE * sizeof(char));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            return pRetVal;
        }
        memset(pRetVal[(*returnSize)], 0, (MAX_RETURN_SIZE * sizeof(char)));
        memcpy(pRetVal[(*returnSize)], buf, (MAX_RETURN_SIZE * sizeof(char)));
        (*returnSize)++;

        ++idx;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (20)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{0, 1, 2, 4, 5, 7}, 6, 0}, {{0, 2, 3, 4, 6, 8, 9}, 7, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [0,1,2,4,5,7]
     *  Output: ["0->2","4->5","7"]
     *
     *  Input: nums = [0,2,3,4,6,8,9]
     *  Output: ["0","2->4","6","8->9"]
     */

    char** pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = summaryRanges(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
