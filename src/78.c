#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Approach_1_Cascading (0)
#define Approach_3_Binary_Sorted (1)
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int** retVal = NULL;

    int i, j;

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

#if (Approach_1_Cascading)
    printf("Approach 1: Cascading\n");

    int count = 1;
    int index = 1;
    int k;
    for (i = 0; i < numsSize; ++i) {
        for (j = 0; j < count; ++j) {
            for (k = 0; k < (*returnColumnSizes)[j]; ++k) {
                retVal[index][k] = retVal[j][k];
            }
            retVal[index][k] = nums[i];
            (*returnColumnSizes)[index] = (*returnColumnSizes)[j] + 1;
            ++index;
        }
        count = index;
    }
#elif (Approach_3_Binary_Sorted)
    printf("Approach 3: Lexicographic (Binary Sorted) Subsets\n");

    //
    for (i = 0; i < (1 << numsSize); ++i) {
        for (j = 0; j < numsSize; ++j) {
            if (i >> j & 1) {
                retVal[i][(*returnColumnSizes)[i]] = nums[j];
                (*returnColumnSizes)[i]++;
            }
        }
    }
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
    } testCase[] = {{{1, 2, 3}, 3, 0, NULL}, {{0}, 1, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer =
            subsets(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize, &testCase[i].returnColumnSizes);
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
