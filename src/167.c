#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 2;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    int left = 0;
    int right = numbersSize - 1;
    int sum = numbers[left] + numbers[right];
    while (sum != target) {
        if (sum > target) {
            --right;
        } else if (sum < target) {
            ++left;
        }
        sum = numbers[left] + numbers[right];
    }
    pRetVal[0] = left + 1;
    pRetVal[1] = right + 1;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3 * 10000)
    struct testCaseType {
        int numbers[MAX_SIZE];
        int numbersSize;
        int target;
        int returnSize;
    } testCase[] = {{{2, 7, 11, 15}, 4, 9, 0}, {{2, 3, 4}, 3, 6, 0}, {{-1, 0}, 2, -1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,7,11,15], target = 9
     *  Output: [1,2]
     *
     *  Input: numbers = [2,3,4], target = 6
     *  Output: [1,3]
     *
     *  Input: nums = [-1,0], target = -1
     *  Output: [1,2]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: numbers = [");
        for (j = 0; j < testCase[i].numbersSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].numbers[j]);
        }
        printf("], target = %d\n", testCase[i].target);

        pAnswer = twoSum(testCase[i].numbers, testCase[i].numbersSize, testCase[i].target, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", *(pAnswer + j));
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}