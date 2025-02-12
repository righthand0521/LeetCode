#include <math.h>
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
int calculateDigitSum(int num) {
    int retVal = 0;

    while (num > 0) {
        retVal += num % 10;
        num /= 10;
    }

    return retVal;
}
int maximumSum(int* nums, int numsSize) {
    int retVal = -1;

    // Store numbers with their digit sums as pairs
    int digitSumPairsSize = numsSize;
    int digitSumPairs[digitSumPairsSize][2];
    memset(digitSumPairs, 0, sizeof(digitSumPairs));
    for (int i = 0; i < numsSize; ++i) {
        digitSumPairs[i][0] = calculateDigitSum(nums[i]);
        digitSumPairs[i][1] = nums[i];
    }
    // Sort based on digit sums, and if equal, by number value
    qsort(digitSumPairs, digitSumPairsSize, sizeof(digitSumPairs[0]), compareIntArray);

    // Iterate through the sorted array to find the maximum sum of pairs
    for (int index = 1; index < digitSumPairsSize; index++) {
        int currentDigitSum = digitSumPairs[index][0];
        int previousDigitSum = digitSumPairs[index - 1][0];
        // If two consecutive numbers have the same digit sum
        if (currentDigitSum == previousDigitSum) {
            int currentSum = digitSumPairs[index][1] + digitSumPairs[index - 1][1];
            retVal = fmax(retVal, currentSum);
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{18, 43, 36, 13, 7}, 5}, {{10, 12, 19, 14}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [18,43,36,13,7]
     *  Output: 54
     *
     *  Input: nums = [10,12,19,14]
     *  Output: -1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = maximumSum(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
