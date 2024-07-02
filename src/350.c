#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int maxSize = (nums1Size > nums2Size) ? nums1Size : nums2Size;
    pRetVal = (int*)malloc(maxSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (maxSize * sizeof(int)));

#define MAX_RECORD (1001)  // 0 <= nums1[i], nums2[i] <= 1000
    int RECORD[MAX_RECORD];
    memset(RECORD, 0, sizeof(RECORD));
    int i;
    for (i = 0; i < nums1Size; ++i) {
        RECORD[nums1[i]]++;
    }
    for (i = 0; i < nums2Size; ++i) {
        if (RECORD[nums2[i]] != 0) {
            pRetVal[(*returnSize)++] = nums2[i];
            RECORD[nums2[i]]--;
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
    } testCase[] = {{{1, 2, 2, 1}, 4, {2, 2}, 2, 0}, {{4, 9, 5}, 3, {9, 4, 9, 8, 4}, 5, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums1 = [1,2,2,1], nums2 = [2,2]
     *  Output: [2,2]
     *
     *  Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
     *  Output: [4,9]
     */

    int* pAnswer = NULL;
    int i, j;
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

        pAnswer = intersect(testCase[i].nums1, testCase[i].nums1Size, testCase[i].nums2, testCase[i].nums2Size,
                            &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}