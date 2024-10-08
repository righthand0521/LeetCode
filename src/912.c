#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int* nums, int left, int middle, int right) {
    // copy left subarray
    int leftIdx = 0;
    int leftSize = middle - left + 1;
    int leftTmp[leftSize];
    memset(leftTmp, 0, sizeof(leftTmp));
    memcpy(leftTmp, &nums[left], sizeof(leftTmp));

    // copy right subarray
    int rightIdx = 0;
    int rightSize = right - middle;
    int rightTmp[rightSize];
    memset(rightTmp, 0, sizeof(rightTmp));
    memcpy(rightTmp, &nums[middle + 1], sizeof(rightTmp));

    // merge left and right subarray in ascending order
    int mergeIdx = left;
    while ((leftIdx < leftSize) && (rightIdx < rightSize)) {
        if (leftTmp[leftIdx] <= rightTmp[rightIdx]) {
            nums[mergeIdx++] = leftTmp[leftIdx++];
        } else {
            nums[mergeIdx++] = rightTmp[rightIdx++];
        }
    }

    // merge remaining left subarray
    while (leftIdx < leftSize) {
        nums[mergeIdx++] = leftTmp[leftIdx++];
    }

    // merge remaining right subarray
    while (rightIdx < rightSize) {
        nums[mergeIdx++] = rightTmp[rightIdx++];
    }
}
void mergeSort(int* nums, int left, int right) {
    if (left >= right) {
        return;
    }

    int middle = left + (right - left) / 2;
    mergeSort(nums, left, middle);
    mergeSort(nums, middle + 1, right);
    merge(nums, left, middle, right);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArray(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));
    memcpy(pRetVal, nums, (numsSize * sizeof(int)));
    (*returnSize) = numsSize;

    mergeSort(pRetVal, 0, numsSize - 1);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{5, 2, 3, 1}, 4, 0}, {{5, 1, 1, 2, 0, 0}, 6, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [5,2,3,1]
     *  Output: [1,2,3,5]
     *
     *  Input: nums = [5,1,1,2,0,0]
     *  Output: [0,0,1,1,2,5]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = sortArray(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
        printf("[");
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
