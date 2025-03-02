#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** mergeArrays(int** nums1, int nums1Size, int* nums1ColSize, int** nums2, int nums2Size, int* nums2ColSize,
                  int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = nums1Size + nums2Size;
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }

    (*returnSize) = 0;
    int idx1 = 0;
    int idx2 = 0;
    while ((idx1 < nums1Size) && (idx2 < nums2Size)) {
        (*returnColumnSizes)[(*returnSize)] = 2;
        pRetVal[(*returnSize)] = (int*)malloc(((*returnColumnSizes)[(*returnSize)]) * sizeof(int));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            for (int i = 0; i < (*returnSize); ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }

        if (nums1[idx1][0] == nums2[idx2][0]) {
            pRetVal[(*returnSize)][0] = nums1[idx1][0];
            pRetVal[(*returnSize)][1] = nums1[idx1][1] + nums2[idx2][1];
            ++idx1;
            ++idx2;
        } else if (nums1[idx1][0] < nums2[idx2][0]) {
            pRetVal[(*returnSize)][0] = nums1[idx1][0];
            pRetVal[(*returnSize)][1] = nums1[idx1][1];
            ++idx1;
        } else if (nums1[idx1][0] > nums2[idx2][0]) {
            pRetVal[(*returnSize)][0] = nums2[idx2][0];
            pRetVal[(*returnSize)][1] = nums2[idx2][1];
            ++idx2;
        }

        ++(*returnSize);
    }

    while (idx1 < nums1Size) {
        (*returnColumnSizes)[(*returnSize)] = 2;
        pRetVal[(*returnSize)] = (int*)malloc(((*returnColumnSizes)[(*returnSize)]) * sizeof(int));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            for (int i = 0; i < (*returnSize); ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        pRetVal[(*returnSize)][0] = nums1[idx1][0];
        pRetVal[(*returnSize)][1] = nums1[idx1][1];
        ++idx1;

        ++(*returnSize);
    }
    while (idx2 < nums2Size) {
        (*returnColumnSizes)[(*returnSize)] = 2;
        pRetVal[(*returnSize)] = (int*)malloc(((*returnColumnSizes)[(*returnSize)]) * sizeof(int));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            for (int i = 0; i < (*returnSize); ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        pRetVal[(*returnSize)][0] = nums2[idx2][0];
        pRetVal[(*returnSize)][1] = nums2[idx2][1];
        ++idx2;

        ++(*returnSize);
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        int nums1[MAX_SIZE][2];
        int nums1Size;
        int nums1ColSize[MAX_SIZE];
        int nums2[MAX_SIZE][2];
        int nums2Size;
        int nums2ColSize[MAX_SIZE];
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{{1, 1}, {2, 3}, {4, 5}}, 3, {2, 2, 2}, {{1, 4}, {3, 2}, {4, 1}}, 3, {2, 2, 2}, 0, NULL},
                    {{{2, 4}, {3, 6}, {5, 5}}, 3, {2, 2, 2}, {{1, 3}, {4, 3}}, 2, {2, 2}, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums1 = [[1,2],[2,3],[4,5]], nums2 = [[1,4],[3,2],[4,1]]
     *  Output: [[1,6],[2,3],[3,2],[4,6]]
     *
     *  Input: nums1 = [[2,4],[3,6],[5,5]], nums2 = [[1,3],[4,3]]
     *  Output: [[1,3],[2,4],[3,6],[4,3],[5,5]]
     */

    int** pNums1 = NULL;
    int** pNums2 = NULL;
    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums1 = [");
        for (j = 0; j < testCase[i].nums1Size; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].nums1ColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].nums1[j][k]);
            }
            printf("]");
        }
        printf("], nums2 = [");
        for (j = 0; j < testCase[i].nums2Size; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].nums2ColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].nums2[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pNums1 = (int**)malloc(testCase[i].nums1Size * sizeof(int*));
        if (pNums1 == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].nums1Size; ++j) {
            pNums1[j] = (int*)malloc(testCase[i].nums1ColSize[j] * sizeof(int));
            if (pNums1[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pNums1[k]) {
                        free(pNums1[k]);
                    }
                }
                free(pNums1);
                pNums1 = NULL;
                return EXIT_FAILURE;
            }
            memset(pNums1[j], 0, testCase[i].nums1ColSize[j] * sizeof(int));
            memcpy(pNums1[j], testCase[i].nums1[j], testCase[i].nums1ColSize[j] * sizeof(int));
        }
        pNums2 = (int**)malloc(testCase[i].nums2Size * sizeof(int*));
        if (pNums2 == NULL) {
            perror("malloc");
            for (j = 0; j < testCase[i].nums1Size; ++j) {
                if (pNums1[j]) {
                    free(pNums1[j]);
                    pNums1[j] = NULL;
                }
            }
            free(pNums1);
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].nums2Size; ++j) {
            pNums2[j] = (int*)malloc(testCase[i].nums2ColSize[j] * sizeof(int));
            if (pNums2[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pNums2[k]) {
                        free(pNums2[k]);
                    }
                }
                free(pNums2);
                pNums2 = NULL;
                for (j = 0; j < testCase[i].nums1Size; ++j) {
                    if (pNums1[j]) {
                        free(pNums1[j]);
                        pNums1[j] = NULL;
                    }
                }
                free(pNums1);
                return EXIT_FAILURE;
            }
            memset(pNums2[j], 0, testCase[i].nums2ColSize[j] * sizeof(int));
            memcpy(pNums2[j], testCase[i].nums2[j], testCase[i].nums2ColSize[j] * sizeof(int));
        }

        pAnswer = mergeArrays(pNums1, testCase[i].nums1Size, testCase[i].nums1ColSize, pNums2, testCase[i].nums2Size,
                              testCase[i].nums2ColSize, &testCase[i].returnSize, &testCase[i].returnColumnSizes);
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

        for (j = 0; j < testCase[i].nums1Size; ++j) {
            if (pNums1[j]) {
                free(pNums1[j]);
                pNums1[j] = NULL;
            }
        }
        free(pNums1);
        pNums1 = NULL;
        for (j = 0; j < testCase[i].nums2Size; ++j) {
            if (pNums2[j]) {
                free(pNums2[j]);
                pNums2[j] = NULL;
            }
        }
        free(pNums2);
        pNums2 = NULL;
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
