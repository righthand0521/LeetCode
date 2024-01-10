#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BITMASKS (1)  // Time Limit Exceeded    // https://leetcode.com/problems/subsets/
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findSubsequences(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int** retVal = NULL;

    int i, j, k;

    //
    (*returnSize) = 1 << numsSize;

    //
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return retVal;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));
    //
    retVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (retVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return retVal;
    }
#if 0
    for (i = 0; i < (*returnSize); ++i) {
        retVal[i] = (int*)malloc(numsSize * sizeof(int));
        if (retVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(retVal[j]);
                retVal[j] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return retVal;
        }
        memset(retVal[i], 0, (numsSize * sizeof(int)));
    }
#endif

#if (BITMASKS)
    printf("BITMASKS\n");

    //
    int idx = 0;
    for (i = 1; i < (1 << numsSize); ++i) {
        retVal[idx] = (int*)malloc(numsSize * sizeof(int));
        if (retVal[idx] == NULL) {
            perror("malloc");
            for (j = 0; j < idx; ++j) {
                free(retVal[j]);
                retVal[j] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return retVal;
        }
        memset(retVal[idx], 0, (numsSize * sizeof(int)));

        for (j = 0; j < numsSize; ++j) {
            if (i >> j & 1) {
                retVal[idx][(*returnColumnSizes)[idx]] = nums[j];
                (*returnColumnSizes)[idx]++;
            }
        }

        if ((*returnColumnSizes)[idx] < 2) {
            (*returnColumnSizes)[idx] = 0;
            free(retVal[idx]);
            retVal[idx] = NULL;
            continue;
        }

        for (j = 1; j < (*returnColumnSizes)[idx]; ++j) {
            if (retVal[idx][j - 1] > retVal[idx][j]) {
                break;
            }
        }
        if (j != (*returnColumnSizes)[idx]) {
            (*returnColumnSizes)[idx] = 0;
            free(retVal[idx]);
            retVal[idx] = NULL;
            continue;
        }

        for (j = 0; j < idx; ++j) {
            if ((*returnColumnSizes)[idx] != (*returnColumnSizes)[j]) {
                continue;
            }

            for (k = 0; k < (*returnColumnSizes)[j]; ++k) {
                if (retVal[idx][k] != retVal[j][k]) {
                    break;
                }
            }
            if (k == (*returnColumnSizes)[j]) {
                break;
            }
        }
        if (j != idx) {
            (*returnColumnSizes)[idx] = 0;
            free(retVal[idx]);
            retVal[idx] = NULL;
            continue;
        }

        ++idx;
    }
    (*returnSize) = idx;
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{4, 6, 7, 7}, 4, 0, NULL}, {{4, 4, 3, 2, 1}, 5, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = findSubsequences(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize,
                                   &testCase[i].returnColumnSizes);
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
