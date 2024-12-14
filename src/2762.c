#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long continuousSubarrays(int* nums, int numsSize) {
    long long retVal = 0;

    int right = 0;
    int left = 0;
    int curMin = nums[right];
    int curMax = nums[right];
    long long windowLen = 0;
    for (right = 0; right < numsSize; right++) {
        curMin = fmin(curMin, nums[right]);
        curMax = fmax(curMax, nums[right]);
        if (curMax - curMin <= 2) {
            continue;
        }

        // Add subarrays from the previous valid window
        windowLen = (right - left);
        retVal += (windowLen * (windowLen + 1) / 2);
        // Start a new window at the current position
        left = right;
        curMin = curMax = nums[right];
        // Expand left boundary while maintaining the condition
        while ((left > 0) && (abs(nums[right] - nums[left - 1]) <= 2)) {
            left--;
            curMin = fmin(curMin, nums[left]);
            curMax = fmax(curMax, nums[left]);
        }
        // Remove overcounted subarrays if left boundary expanded
        if (left < right) {
            windowLen = right - left;
            retVal -= (windowLen * (windowLen + 1) / 2);
        }
    }

    // Add subarrays from the final window
    windowLen = right - left;
    retVal += (windowLen * (windowLen + 1) / 2);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{5, 4, 2, 4}, 4}, {{1, 2, 3}, 3}, {{65, 66, 67, 66, 66, 65, 64, 65, 65, 64}, 10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [5,4,2,4]
     *  Output: 8
     *
     *  Input: nums = [1,2,3]
     *  Output: 6
     *
     *  Input: nums = [65,66,67,66,66,65,64,65,65,64]
     *  Output: 43
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = continuousSubarrays(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
