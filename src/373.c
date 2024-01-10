#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** kSmallestPairs(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize,
                     int** returnColumnSizes) {
    int** pRetVal = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums1[MAX_SIZE];
        int nums1Size;
        int nums2[MAX_SIZE];
        int nums2Size;
        int k;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{1, 7, 11}, 3, {2, 4, 6}, 3, 3, 0, NULL},
                    {{1, 1, 2}, 3, {1, 2, 3}, 3, 2, 0, NULL},
                    {{1, 2}, 2, {3}, 1, 3, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
     *  Output: [[1,2],[1,4],[1,6]]
     *
     *  Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
     *  Output: [[1,1],[1,1]]
     *
     *  Input: nums1 = [1,2], nums2 = [3], k = 3
     *  Output: [[1,3],[2,3]]
     */

    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums1 = [");
        for (j = 0; j < testCase[i].nums1Size; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums1[j]);
        }
        printf("], nums2 = [");
        for (j = 0; j < testCase[i].nums2Size; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums2[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        pAnswer = kSmallestPairs(testCase[i].nums1, testCase[i].nums1Size, testCase[i].nums2, testCase[i].nums2Size,
                                 testCase[i].k, &testCase[i].returnSize, &testCase[i].returnColumnSizes);
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
