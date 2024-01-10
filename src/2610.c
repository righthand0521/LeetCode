#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findMatrix(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    //
    pRetVal = (int**)malloc(numsSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    //
    (*returnColumnSizes) = (int*)malloc(numsSize * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (numsSize * sizeof(int)));

    // 1 <= nums.length <= 200, 1 <= nums[i] <= nums.length.
#define MAX_NUMS_SIZE (200 + 4)
    int hashTable[MAX_NUMS_SIZE];
    memset(hashTable, 0, sizeof(hashTable));

    int i;
    for (i = 0; i < numsSize; ++i) {
        hashTable[nums[i]] += 1;
    }

    int count = numsSize;
    while (count > 0) {
        pRetVal[(*returnSize)] = (int*)malloc(numsSize * sizeof(int));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (i = 0; i < (*returnSize); ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[(*returnSize)], 0, (numsSize * sizeof(int)));
        for (i = 1; i < MAX_NUMS_SIZE; ++i) {
            if (hashTable[i] == 0) {
                continue;
            }
            pRetVal[(*returnSize)][(*returnColumnSizes)[(*returnSize)]] = i;
            (*returnColumnSizes)[(*returnSize)] += 1;

            hashTable[i] -= 1;
            count -= 1;
        }
        (*returnSize) += 1;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{1, 3, 4, 1, 2, 3, 1}, 7, 0, NULL}, {{1, 2, 3, 4}, 4, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,3,4,1,2,3,1]
     *  Output: [[1,3,4,2],[1,3],[1]]
     *
     *  Input: nums = [1,2,3,4]
     *  Output: [[4,3,2,1]]
     */

    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer =
            findMatrix(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize, &testCase[i].returnColumnSizes);
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

        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
    }

    return EXIT_SUCCESS;
}
