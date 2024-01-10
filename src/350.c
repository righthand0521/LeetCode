#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE (1)
#define SORTING (1)
#if (HASH_TABLE)
#elif (SORTING)
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
#endif
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = (nums1Size > nums2Size) ? nums1Size : nums2Size;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, -1, ((*returnSize) * sizeof(int)));

#if (HASH_TABLE)
    printf("HASH_TABLE\n");

#define MAX_RECORD (1001)
    int RECORD[MAX_RECORD];
    memset(RECORD, 0, sizeof(RECORD));

    int i;
    for (i = 0; i < nums1Size; ++i) {
        RECORD[nums1[i]]++;
    }

    (*returnSize) = 0;
    for (i = 0; i < nums2Size; ++i) {
        if (RECORD[nums2[i]] != 0) {
            pRetVal[(*returnSize)++] = nums2[i];
            RECORD[nums2[i]]--;
        }
    }
#elif (SORTING)
    printf("SORTING\n");

    qsort(nums1, nums1Size, sizeof(int), compareInteger);
    qsort(nums2, nums2Size, sizeof(int), compareInteger);

    (*returnSize) = 0;
    int idx1 = 0;
    int idx2 = 0;
    while ((idx1 < nums1Size) && (idx2 < nums2Size)) {
        if (nums1[idx1] == nums2[idx2]) {
            pRetVal[(*returnSize)++] = nums1[idx1];
            idx1++;
            idx2++;
        } else if (nums1[idx1] > nums2[idx2]) {
            idx2++;
        } else if (nums1[idx1] < nums2[idx2]) {
            idx1++;
        }
    }
#endif

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