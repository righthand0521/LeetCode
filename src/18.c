#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    if (numsSize < 4) {
        return pRetVal;
    }

#define MAX_ROW (numsSize * numsSize)
#define MAX_COLUMN (4)
    (*returnColumnSizes) = (int*)malloc(MAX_ROW * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (MAX_ROW * sizeof(int)));
    pRetVal = (int**)malloc(MAX_ROW * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }

    qsort(nums, numsSize, sizeof(int), compareInteger);

    long compare;
    int a, b, c, d;
    for (a = 0; a < numsSize - 3; ++a) {
        // Notice that the order of the output and the order of the triplets does not matter.
        if ((a > 0) && (nums[a - 1] == nums[a])) {
            continue;
        }

        for (b = a + 1; b < numsSize - 2; ++b) {
            // Notice that the order of the output and the order of the triplets does not matter.
            if ((b > a + 1) && (nums[b - 1] == nums[b])) {
                continue;
            }

            c = b + 1;
            d = numsSize - 1;
            while (c < d) {
                compare = (long)(nums[a]) + (long)(nums[b]) + (long)(nums[c]) + (long)(nums[d]);
                if (compare < target) {
                    c += 1;
                } else if (compare > target) {
                    d -= 1;
                } else {
                    // Notice that the order of the output and the order of the triplets does not matter.
                    if ((c > b + 1) && (nums[c - 1] == nums[c])) {
                        c += 1;
                        continue;
                    }

                    (*returnColumnSizes)[(*returnSize)] = MAX_COLUMN;
                    pRetVal[(*returnSize)] = (int*)malloc(((*returnColumnSizes)[(*returnSize)]) * sizeof(int));
                    if (pRetVal[(*returnSize)] == NULL) {
                        perror("malloc");
                        return pRetVal;
                    }
                    pRetVal[(*returnSize)][0] = nums[a];
                    pRetVal[(*returnSize)][1] = nums[b];
                    pRetVal[(*returnSize)][2] = nums[c];
                    pRetVal[(*returnSize)][3] = nums[d];
                    (*returnSize) += 1;

                    c += 1;
                    d -= 1;
                }
            }
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int target;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{1, 0, -1, 0, -2, 2}, 6, 0, 0, NULL},
                    {{2, 2, 2, 2, 2}, 5, 8, 0, NULL},
                    {{1000000000, 1000000000, 1000000000, 1000000000}, 4, 0, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,0,-1,0,-2,2], target = 0
     *  Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
     *
     *  Input: nums = [2,2,2,2,2], target = 8
     *  Output: [[2,2,2,2]]
     *
     *  Input: nums = [1000000000,1000000000,1000000000,1000000000], target = 0
     *  Output: []
     */

    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], target = %d\n", testCase[i].target);

        pAnswer = fourSum(testCase[i].nums, testCase[i].numsSize, testCase[i].target, &testCase[i].returnSize,
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
