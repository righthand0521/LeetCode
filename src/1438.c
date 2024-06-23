#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestSubarray(int* nums, int numsSize, int limit) {
    int retVal = 0;

    int maxDequeLeft = 0;
    int maxDequeRight = 0;
    int maxDeque[numsSize];
    memset(maxDeque, 0, sizeof(maxDeque));

    int minDequeLeft = 0;
    int minDequeRight = 0;
    int minDeque[numsSize];
    memset(minDeque, 0, sizeof(minDeque));

    int left = 0;
    int right = 0;
    for (right = 0; right < numsSize; right++) {
        // Maintain the maxDeque in decreasing order
        while ((maxDequeLeft < maxDequeRight) && (maxDeque[maxDequeRight - 1] < nums[right])) {
            maxDequeRight--;
        }
        maxDeque[maxDequeRight++] = nums[right];

        // Maintain the minDeque in increasing order
        while ((minDequeLeft < minDequeRight) && (minDeque[minDequeRight - 1] > nums[right])) {
            minDequeRight--;
        }
        minDeque[minDequeRight++] = nums[right];

        // Check if the current window exceeds the limit
        while ((maxDequeLeft < maxDequeRight) && (minDequeLeft < minDequeRight) &&
               (maxDeque[maxDequeLeft] - minDeque[minDequeLeft] > limit)) {
            // Remove the elements that are out of the current window
            if (maxDeque[maxDequeLeft] == nums[left]) {
                maxDequeLeft++;
            }
            if (minDeque[minDequeLeft] == nums[left]) {
                minDequeLeft++;
            }

            left++;
        }
        retVal = fmax(retVal, right - left + 1);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int limit;
    } testCase[] = {{{8, 2, 4, 7}, 4, 4}, {{10, 1, 2, 4, 7, 2}, 6, 5}, {{4, 2, 2, 2, 4, 4, 2, 2}, 8, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [8,2,4,7], limit = 4
     *  Output: 2
     *
     *  Input: nums = [10,1,2,4,7,2], limit = 5
     *  Output: 4
     *
     *  Input: nums = [4,2,2,2,4,4,2,2], limit = 0
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], limit = %d\n", testCase[i].limit);

        answer = longestSubarray(testCase[i].nums, testCase[i].numsSize, testCase[i].limit);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
