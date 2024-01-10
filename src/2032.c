#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoOutOfThree(int* nums1, int nums1Size, int* nums2, int nums2Size, int* nums3, int nums3Size, int* returnSize) {
    int* pRetVal = NULL;

// 1 <= nums1.length, nums2.length, nums3.length <= 100
#define MAX_HASH_TABLE_SIZE (100 + 4)
    int HashTable[MAX_HASH_TABLE_SIZE];
    memset(HashTable, 0, sizeof(HashTable));

    (*returnSize) = MAX_HASH_TABLE_SIZE;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    int i;
    for (i = 0; i < nums1Size; ++i) {
        HashTable[nums1[i]] |= (1 << 0);
    }
    for (i = 0; i < nums2Size; ++i) {
        HashTable[nums2[i]] |= (1 << 1);
    }
    for (i = 0; i < nums3Size; ++i) {
        HashTable[nums3[i]] |= (1 << 2);
    }

    (*returnSize) = 0;
    for (i = 0; i < MAX_HASH_TABLE_SIZE; ++i) {
        if (HashTable[i] & (HashTable[i] - 1)) {
            pRetVal[(*returnSize)] = i;
            ++(*returnSize);
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums1[MAX_SIZE];
        int nums1Size;
        int nums2[MAX_SIZE];
        int nums2Size;
        int nums3[MAX_SIZE];
        int nums3Size;
        int returnSize;
    } testCase[] = {{{1, 1, 3, 2}, 4, {2, 3}, 2, {3}, 1, 0},
                    {{3, 1}, 2, {2, 3}, 2, {1, 2}, 2, 0},
                    {{1, 2, 2}, 3, {4, 3, 3}, 3, {5}, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums1 = [");
        for (j = 0; j < testCase[i].nums1Size; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums1[j]);
        }
        printf("], nums2 = [");
        for (j = 0; j < testCase[i].nums2Size; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums2[j]);
        }
        printf("], nums3 = [");
        for (j = 0; j < testCase[i].nums3Size; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums3[j]);
        }
        printf("]\n");

        pAnswer = twoOutOfThree(testCase[i].nums1, testCase[i].nums1Size, testCase[i].nums2, testCase[i].nums2Size,
                                testCase[i].nums3, testCase[i].nums3Size, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
