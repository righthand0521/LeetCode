#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int smallestRangeI(int* nums, int numsSize, int k) {
    int retVal = 0;

    /* https://leetcode.com/problems/smallest-range-i/solutions/173367/c-java-python-check-max-min/
     *  If min(nums) + k < max(nums) - k, then return max(nums) - min(nums) - 2 * k.
     *  If min(nums) + k >= max(nums) - k, then return 0.
     */
    int max = nums[0];
    int min = nums[0];
    int i;
    for (i = 1; i < numsSize; ++i) {
        max = fmax(max, nums[i]);
        min = fmin(min, nums[i]);
    }
    if ((min + k) < (max - k)) {
        retVal = max - min - 2 * k;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1}, 1, 0}, {{0, 10}, 2, 2}, {{1, 3, 6}, 3, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = smallestRangeI(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
