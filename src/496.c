#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* nextGreaterElement(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int* pRetVal = NULL;
    (*returnSize) = nums1Size;

    // prepare return array
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    // record the next greater element of nums2 array
#define RECORD_SIZE (10000)
    int Record[RECORD_SIZE];
    memset(Record, -1, sizeof(Record));
    int i, j;
    for (i = 0; i < nums2Size; ++i) {
        for (j = i; j < nums2Size; ++j) {
            if (nums2[i] < nums2[j]) {
                Record[nums2[i]] = nums2[j];
                break;
            }
        }
    }

    // nums1 array map to nums2 record of the next greater element
    for (i = 0; i < nums1Size; ++i) {
        pRetVal[i] = Record[nums1[i]];
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
    } testCase[] = {{{4, 1, 2}, 3, {1, 3, 4, 2}, 4, 0}, {{2, 4}, 2, {1, 2, 3, 4}, 4, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

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

        pAnswer = nextGreaterElement(testCase[i].nums1, testCase[i].nums1Size, testCase[i].nums2, testCase[i].nums2Size,
                                     &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        if (pAnswer) {
            free(pAnswer);
            pAnswer = NULL;
        }
    }

    return EXIT_SUCCESS;
}
