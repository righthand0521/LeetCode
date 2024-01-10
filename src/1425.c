#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int constrainedSubsetSum(int* nums, int numsSize, int k) {
    int retVal = 0;

    struct deque {
        int value;
        int index;
    } monotonicDeque[numsSize];
    int monotonicDequeHead = 0;
    int monotonicDequeTail = 0;
    monotonicDeque[monotonicDequeTail].value = nums[0];
    monotonicDeque[monotonicDequeTail].index = 0;
    monotonicDequeTail++;

    int dp[numsSize];
    memset(dp, 0, sizeof(dp));
    dp[0] = nums[0];

    retVal += nums[0];

    int i;
    for (i = 1; i < numsSize; i++) {
        dp[i] = fmax(0, dp[monotonicDeque[monotonicDequeHead].index]) + nums[i];
        retVal = fmax(retVal, dp[i]);

        while ((monotonicDequeHead < monotonicDequeTail) &&
               (dp[i] >= dp[monotonicDeque[monotonicDequeTail - 1].index])) {
            monotonicDequeTail--;
        }
        monotonicDeque[monotonicDequeTail].value = nums[i];
        monotonicDeque[monotonicDequeTail].index = i;
        monotonicDequeTail++;
        if ((i - monotonicDeque[monotonicDequeHead].index) >= k) {
            monotonicDequeHead++;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{10, 2, -10, 5, 20}, 5, 2}, {{-1, -2, -3}, 3, 1}, {{10, -2, -10, -5, 20}, 5, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [10,2,-10,5,20], k = 2
     *  Output: 37
     *
     *  Input: nums = [-1,-2,-3], k = 1
     *  Output: -1
     *
     *  Input: nums = [10,-2,-10,-5,20], k = 2
     *  Output: 23
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = constrainedSubsetSum(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
