#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* nums, int indexA, int indexB) {
    int temp = nums[indexA];
    nums[indexA] = nums[indexB];
    nums[indexB] = temp;
}
void backtracking(int* nums, int numsSize, int* returnSize, int** returnColumnSizes, int** pRetVal, int offset) {
    if (offset == numsSize) {
        pRetVal[(*returnSize)] = (int*)malloc(numsSize * sizeof(int));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            return;
        }
        memset(pRetVal[(*returnSize)], 0, (numsSize * sizeof(int)));
        memcpy(pRetVal[(*returnSize)], nums, (numsSize * sizeof(int)));
        (*returnColumnSizes)[(*returnSize)++] = numsSize;
        return;
    }

    int i;
    for (i = offset; i < numsSize; i++) {
        swap(nums, i, offset);
        backtracking(nums, numsSize, returnSize, returnColumnSizes, pRetVal, offset + 1);
        swap(nums, i, offset);
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

#define MAX_RETURN_SIZE (6 * 5 * 4 * 3 * 2 * 1 + 1)

    (*returnSize) = 0;

    (*returnColumnSizes) = (int*)malloc(MAX_RETURN_SIZE * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }

    pRetVal = (int**)malloc(MAX_RETURN_SIZE * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }

    backtracking(nums, numsSize, returnSize, returnColumnSizes, pRetVal, 0);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (6)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{1, 2, 3}, 3, 0, NULL}, {{0, 1}, 2, 0, NULL}, {{1}, 1, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3]
     *  Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
     *
     *  Input: nums = [0,1]
     *  Output: [[0,1],[1,0]]
     *
     *  Input: nums = [1]
     *  Output: [[1]]
     */

    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer =
            permute(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize, &testCase[i].returnColumnSizes);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
