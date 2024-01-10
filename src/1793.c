#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maximumScore(int* nums, int numsSize, int k) {
    int retVal = 0;

    retVal = nums[k];
    int minValue = nums[k];
    int leftValue, rightValue;
    int left = k;
    int right = k;
    while ((left > 0) || (right < numsSize - 1)) {
        // 1 <= nums[i] <= 2 * 10^4, 0 <= k < nums.length
        leftValue = ((left > 0) ? nums[left - 1] : 0);
        rightValue = ((right < numsSize - 1) ? nums[right + 1] : 0);
        if (leftValue < rightValue) {
            right++;
            minValue = fmin(minValue, nums[right]);
        } else {
            left--;
            minValue = fmin(minValue, nums[left]);
        }

        retVal = fmax(retVal, minValue * (right - left + 1));
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 4, 3, 7, 4, 5}, 6, 3}, {{5, 5, 4, 5, 4, 1, 1, 1}, 8, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,4,3,7,4,5], k = 3
     *  Output: 15
     *
     *  Input: nums = [5,5,4,5,4,1,1,1], k = 0
     *  Output: 20
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = maximumScore(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
