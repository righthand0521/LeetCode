#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
double largestSumOfAverages(int* nums, int numsSize, int k) {
    double retVal = 0.0;

    int i, j, x;

    double prefixSum[numsSize + 1];
    prefixSum[0] = 0.0;
    for (i = 0; i < numsSize; ++i) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    double dp[numsSize];
    for (i = 0; i < numsSize; ++i) {
        dp[i] = (prefixSum[numsSize] - prefixSum[i]) / (numsSize - i);
    }

    for (x = 0; x < k - 1; ++x) {
        for (i = 0; i < numsSize; ++i) {
            for (j = (i + 1); j < numsSize; ++j) {
                dp[i] = MAX(dp[i], (prefixSum[j] - prefixSum[i]) / (j - i) + dp[j]);
            }
        }
    }
    retVal = dp[0];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{9, 1, 2, 3, 9}, 5, 3}, {{1, 2, 3, 4, 5, 6, 7}, 7, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    double answer = 0.0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = largestSumOfAverages(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %f\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}