#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* prefixesDivBy5(int* nums, int numsSize, int* returnSize) {
    bool* pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (bool*)malloc(numsSize * sizeof(bool));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, false, (numsSize) * sizeof(bool));

    int prefix = 0;
    for (int i = 0; i < numsSize; ++i) {
        prefix = ((prefix << 1) + nums[i]) % 5;
        if (prefix == 0) {
            pRetVal[(*returnSize)++] = true;
        } else {
            pRetVal[(*returnSize)++] = false;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{0, 1, 1}, 3, 0}, {{1, 1, 1}, 3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [0,1,1]
     *  Output: [true,false,false]
     *
     *  Input: nums = [1,1,1]
     *  Output: [false,false,false]
     */

    bool* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = prefixesDivBy5(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);

        printf("Output:[");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", (pAnswer[j] == true ? "true" : "false"));
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
