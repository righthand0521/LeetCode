#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void* a1, const void* a2) {
    int* p1 = (int*)a1;
    int* p2 = (int*)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }

    return (p1[0] > p2[0]);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* smallestRange(int** nums, int numsSize, int* numsColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int i, j;

    // Merge all lists with their list index
    int mergedIndex = 0;
    int mergedSize = 0;
    for (i = 0; i < numsSize; ++i) {
        mergedSize += numsColSize[i];
    }
    int merged[mergedSize][2];
    memset(merged, 0, sizeof(merged));
    for (i = 0; i < numsSize; ++i) {
        for (j = 0; j < numsColSize[i]; ++j) {
            merged[mergedIndex][0] = nums[i][j];
            merged[mergedIndex][1] = i;
            mergedIndex++;
        }
    }
    qsort(merged, mergedSize, sizeof(merged[0]), compareIntArray);

    // Two pointers to track the smallest range
    int freq[numsSize];
    memset(freq, 0, sizeof(freq));
    int rangeStart = 0;
    int rangeEnd = INT_MAX;
    int curRange;
    int count = 0;
    int left = 0;
    int right = 0;
    for (right = 0; right < mergedSize; right++) {
        freq[merged[right][1]]++;
        if (freq[merged[right][1]] == 1) {
            count++;
        }

        // When all lists are represented, try to shrink the window
        while (count == numsSize) {
            curRange = merged[right][0] - merged[left][0];
            if (curRange < rangeEnd - rangeStart) {
                rangeStart = merged[left][0];
                rangeEnd = merged[right][0];
            }

            freq[merged[left][1]]--;
            if (freq[merged[left][1]] == 0) {
                count--;
            }

            left++;
        }
    }

    pRetVal = (int*)calloc(2, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    pRetVal[0] = rangeStart;
    pRetVal[1] = rangeEnd;
    (*returnSize) = 2;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (3500)
#define MAX_COLUMN (50)
    struct testCaseType {
        int nums[MAX_ROW][MAX_COLUMN];
        int numsSize;
        int numsColSize[MAX_ROW];
        int returnSize;
    } testCase[] = {{{{4, 10, 15, 24, 26}, {0, 9, 12, 20}, {5, 18, 22, 30}}, 3, {5, 4, 4}, 0},
                    {{{1, 2, 3}, {1, 2, 3}, {1, 2, 3}}, 3, {3, 3, 3}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
     *  Output: [20,24]
     *
     *  Input: nums = [[1,2,3],[1,2,3],[1,2,3]]
     *  Output: [1,1]
     */

    int** pNums = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].numsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].nums[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pNums = (int**)malloc(testCase[i].numsSize * sizeof(int*));
        if (pNums == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].numsSize; ++j) {
            pNums[j] = (int*)malloc(testCase[i].numsColSize[j] * sizeof(int));
            if (pNums[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pNums[k]);
                }
                free(pNums);
                return EXIT_FAILURE;
            }
            memset(pNums[j], 0, (testCase[i].numsColSize[j] * sizeof(int)));
            memcpy(pNums[j], testCase[i].nums[j], (testCase[i].numsColSize[j] * sizeof(int)));
        }
        pAnswer = smallestRange(pNums, testCase[i].numsSize, testCase[i].numsColSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].numsSize; ++j) {
            free(pNums[j]);
        }
        free(pNums);
        pNums = NULL;
    }

    return EXIT_SUCCESS;
}
