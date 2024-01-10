#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BINARY_SEARCH (1)
#define AVERAGE (1)
int minimizeArrayValue(int *nums, int numsSize) {
    int retVal = 0;

#if (BINARY_SEARCH)
    printf("BINARY_SEARCH\n");

    int i;

    int maxValue = 0;
    for (i = 0; i < numsSize; ++i) {
        maxValue = fmax(maxValue, nums[i]);
    }

    bool operationFlag;
    /* use long to avoid signed integer overflow
     *  n == nums.length
     *  2 <= n <= 10^5
     *  0 <= nums[i] <= 10^9
     */
    long operation;
    int left = 0;
    int right = maxValue;
    int middle;
    while (left < right) {
        middle = left + (right - left) / 2;

        operationFlag = true;
        operation = 0;
        for (i = 0; i < numsSize; ++i) {
            if (nums[i] <= middle) {
                operation += (middle - nums[i]);
                continue;
            }

            if (operation < (nums[i] - middle)) {
                operationFlag = false;
                break;
            }

            operation -= (nums[i] - middle);
        }

        if (operationFlag == false) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left;

#elif (AVERAGE)
    printf("AVERAGE\n");

    // https://leetcode.com/problems/minimize-maximum-of-array/solutions/2706521/java-c-python-prefix-sum-average-o-n/
    int prefixSumSize = numsSize;
    /* use long to avoid signed integer overflow
     *  n == nums.length
     *  2 <= n <= 10^5
     *  0 <= nums[i] <= 10^9
     */
    long prefixSum[prefixSumSize];
    memset(prefixSum, 0, sizeof(prefixSum));
    prefixSum[0] = nums[0];

    int i;
    for (i = 1; i < prefixSumSize; ++i) {
        prefixSum[i] = nums[i] + prefixSum[i - 1];
    }

    for (i = 0; i < prefixSumSize; ++i) {
        retVal = fmax((long)retVal, ((prefixSum[i] + i) / (i + 1)));
    }
#endif

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{3, 7, 1, 6}, 4}, {{10, 1}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,7,1,6]
     *  Output: 5
     *
     *  Input: nums = [10,1]
     *  Output: 10
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minimizeArrayValue(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
