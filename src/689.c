#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *maxSumOfThreeSubarrays(int *nums, int numsSize, int k, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    // Variables to track the best indices for one, two, and three subarray configurations
    int bestSingleStart = 0;
    int bestDoubleStart[2] = {0, k};
    int bestTripleStart[3] = {0, k, k * 2};

    // Compute the initial sums for the first three subarrays
    int currentWindowSumSingle = 0;
    for (int i = 0; i < k; i++) {
        currentWindowSumSingle += nums[i];
    }
    int currentWindowSumDouble = 0;
    for (int i = k; i < k * 2; i++) {
        currentWindowSumDouble += nums[i];
    }
    int currentWindowSumTriple = 0;
    for (int i = k * 2; i < k * 3; i++) {
        currentWindowSumTriple += nums[i];
    }

    // Track the best sums found so far
    int bestSingleSum = currentWindowSumSingle;
    int bestDoubleSum = currentWindowSumSingle + currentWindowSumDouble;
    int bestTripleSum = currentWindowSumSingle + currentWindowSumDouble + currentWindowSumTriple;

    // Sliding window pointers for the subarrays
    int singleStartIndex = 1;
    int doubleStartIndex = k + 1;
    int tripleStartIndex = k * 2 + 1;

    while (tripleStartIndex <= numsSize - k) {
        // Update the sums using the sliding window technique
        currentWindowSumSingle = currentWindowSumSingle - nums[singleStartIndex - 1] + nums[singleStartIndex + k - 1];
        currentWindowSumDouble = currentWindowSumDouble - nums[doubleStartIndex - 1] + nums[doubleStartIndex + k - 1];
        currentWindowSumTriple = currentWindowSumTriple - nums[tripleStartIndex - 1] + nums[tripleStartIndex + k - 1];

        // Update the best single subarray start index if a better sum is found
        if (currentWindowSumSingle > bestSingleSum) {
            bestSingleStart = singleStartIndex;
            bestSingleSum = currentWindowSumSingle;
        }

        // Update the best double subarray start indices if a better sum is found
        if (currentWindowSumDouble + bestSingleSum > bestDoubleSum) {
            bestDoubleStart[0] = bestSingleStart;
            bestDoubleStart[1] = doubleStartIndex;
            bestDoubleSum = currentWindowSumDouble + bestSingleSum;
        }

        // Update the best triple subarray start indices if a better sum is found
        if (currentWindowSumTriple + bestDoubleSum > bestTripleSum) {
            bestTripleStart[0] = bestDoubleStart[0];
            bestTripleStart[1] = bestDoubleStart[1];
            bestTripleStart[2] = tripleStartIndex;
            bestTripleSum = currentWindowSumTriple + bestDoubleSum;
        }

        // Move the sliding windows forward
        singleStartIndex += 1;
        doubleStartIndex += 1;
        tripleStartIndex += 1;
    }

    // Return the starting indices of the three subarrays with the maximum sum
    pRetVal = (int *)calloc(3, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    memcpy(pRetVal, bestTripleStart, (3 * sizeof(int)));
    (*returnSize) = 3;

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(2 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
        int returnSize;
    } testCase[] = {{{1, 2, 1, 2, 6, 7, 5, 1}, 8, 2, 0}, {{1, 2, 1, 2, 1, 2, 1, 2, 1}, 9, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,1,2,6,7,5,1], k = 2
     *  Output: [0,3,5]
     *
     *  Input: nums = [1,2,1,2,1,2,1,2,1], k = 2
     *  Output: [0,2,4]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        pAnswer =
            maxSumOfThreeSubarrays(testCase[i].nums, testCase[i].numsSize, testCase[i].k, &testCase[i].returnSize);
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
