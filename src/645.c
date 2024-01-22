#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findErrorNums(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    int hashTable[numsSize + 1];
    memset(hashTable, 0, sizeof(hashTable));
    int i;
    for (i = 0; i < numsSize; ++i) {
        hashTable[nums[i]]++;
    }

    (*returnSize) = 2;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, (*returnSize) * sizeof(int));
    for (i = 1; i <= numsSize; ++i) {
        if (hashTable[i] == 2) {
            pRetVal[0] = i;
        } else if (hashTable[i] == 0) {
            pRetVal[1] = i;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{1, 2, 2, 4}, 4, 0}, {{1, 1}, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,2,4]
     *  Output: [2,3]
     *
     *  Input: nums = [1,1]
     *  Output: [1,2]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = findErrorNums(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
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
