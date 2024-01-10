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
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    if (numsSize < 3) {
        return pRetVal;
    }

#define MAX_ROW (numsSize * numsSize)
#define MAX_COLUMN (3)
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

    int first, second, third, target;
    for (first = 0; first < numsSize - 2; ++first) {
        if (nums[first] > 0) {
            break;
        }

        // Notice that the order of the output and the order of the triplets does not matter.
        if ((first > 0) && (nums[first - 1] == nums[first])) {
            continue;
        }

        second = first + 1;
        third = numsSize - 1;
        while (second < third) {
            target = nums[first] + nums[second] + nums[third];
            if (target == 0) {
                // Notice that the order of the output and the order of the triplets does not matter.
                if ((second > first + 1) && (nums[second - 1] == nums[second])) {
                    second += 1;
                    continue;
                }

                (*returnColumnSizes)[(*returnSize)] = MAX_COLUMN;
                pRetVal[(*returnSize)] = (int*)malloc(((*returnColumnSizes)[(*returnSize)]) * sizeof(int));
                if (pRetVal[(*returnSize)] == NULL) {
                    perror("malloc");
                    return pRetVal;
                }
                pRetVal[(*returnSize)][0] = nums[first];
                pRetVal[(*returnSize)][1] = nums[second];
                pRetVal[(*returnSize)][2] = nums[third];
                (*returnSize) += 1;

                second += 1;
                third -= 1;
            } else if (target < 0) {
                second += 1;
            } else if (target > 0) {
                third -= 1;
            }
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{-1, 0, 1, 2, -1, -4}, 6, 0, NULL},
                    {{0, 1, 1}, 3, 0, NULL},
                    {{0, 0, 0}, 3, 0, NULL},
                    {{-2, 0, 1, 1, 2}, 5, 0, NULL},
                    {{-2, 0, 0, 2, 2}, 5, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [-1,0,1,2,-1,-4]
     *  Output: [[-1,-1,2],[-1,0,1]]
     *
     *  Input: nums = [0,1,1]
     *  Output: []
     *
     *  Input: nums = [0,0,0]
     *  Output: [[0,0,0]]
     *
     *  Input: nums = [-2,0,1,1,2]
     *  Output: [[-2,0,2],[-2,1,1]]
     *
     *  Input: nums = [-2,0,0,2,2]
     *  Output: [[-2,0,2]]
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
            threeSum(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize, &testCase[i].returnColumnSizes);
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
