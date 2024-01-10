#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findDifference(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 2;
    //
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        (*returnSize) = 0;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));
    //
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        (*returnSize) = 0;
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }
    pRetVal[0] = (int*)malloc(nums1Size * sizeof(int));
    if (pRetVal[0] == NULL) {
        (*returnSize) = 0;
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset(pRetVal[0], 0, (nums1Size * sizeof(int)));
    pRetVal[1] = (int*)malloc(nums2Size * sizeof(int));
    if (pRetVal[1] == NULL) {
        (*returnSize) = 0;
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        free(pRetVal[0]);
        pRetVal[0] = NULL;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset(pRetVal[1], 0, (nums2Size * sizeof(int)));

// -1000 <= nums1[i], nums2[i] <= 1000
#define SHIFT_HASHTABLE_IDX (1000)
#define MAX_HASHTABLE_SIZE ((SHIFT_HASHTABLE_IDX) + 1 + (SHIFT_HASHTABLE_IDX))
    int i;

    //
    int hashTable1[MAX_HASHTABLE_SIZE];
    memset(hashTable1, 0, sizeof(hashTable1));
    for (i = 0; i < nums1Size; ++i) {
        hashTable1[nums1[i] + SHIFT_HASHTABLE_IDX] = 1;
    }
    int hashTable2[MAX_HASHTABLE_SIZE];
    memset(hashTable2, 0, sizeof(hashTable2));
    for (i = 0; i < nums2Size; ++i) {
        hashTable2[nums2[i] + SHIFT_HASHTABLE_IDX] = 1;
    }

    //
    for (i = 0; i < nums1Size; ++i) {
        if (hashTable2[nums1[i] + SHIFT_HASHTABLE_IDX] == 0) {
            pRetVal[0][((*returnColumnSizes)[0])++] = nums1[i];
            hashTable2[nums1[i] + SHIFT_HASHTABLE_IDX] = 1;
        }
    }
    for (i = 0; i < nums2Size; ++i) {
        if (hashTable1[nums2[i] + SHIFT_HASHTABLE_IDX] == 0) {
            pRetVal[1][((*returnColumnSizes)[1])++] = nums2[i];
            hashTable1[nums2[i] + SHIFT_HASHTABLE_IDX] = 1;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums1[MAX_SIZE];
        int nums1Size;
        int nums2[MAX_SIZE];
        int nums2Size;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{1, 2, 3}, 3, {2, 4, 6}, 3, 0, NULL}, {{1, 2, 3, 3}, 4, {1, 1, 2, 2}, 4, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums1 = [1,2,3], nums2 = [2,4,6]
     *  Output: [[1,3],[4,6]]
     *
     *  Input: nums1 = [1,2,3,3], nums2 = [1,1,2,2]
     *  Output: [[3],[]]
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
        printf("]\n");

        pAnswer = findDifference(testCase[i].nums1, testCase[i].nums1Size, testCase[i].nums2, testCase[i].nums2Size,
                                 &testCase[i].returnSize, &testCase[i].returnColumnSizes);
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
