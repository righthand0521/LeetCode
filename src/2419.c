#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestSubarray(int* nums, int numsSize) {
    int retVal = 0;

    // The maximum possible bitwise AND should not be less than a largest element.
    // Therefore, the subarray must only include one or more largest elements.
    int maxNum = nums[0];  // 1 <= nums.length <= 10^5
    int count = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] == maxNum) {
            count++;
            retVal = (retVal > count) ? (retVal) : (count);
        } else if (nums[i] > maxNum) {
            maxNum = nums[i];
            count = 1;
            retVal = 1;
        } else if (nums[i] < maxNum) {
            count = 0;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 3, 3, 2, 2}, 6},
                    {{1, 2, 3, 4}, 4},
                    {{96317, 96317, 96317, 96317, 96317, 96317, 96317, 96317, 96317, 279979}, 10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3,3,2,2]
     *  Output: 2
     *
     *  Input: nums = [1,2,3,4]
     *  Output: 1
     *
     *  Input: nums = [96317,96317,96317,96317,96317,96317,96317,96317,96317,279979]
     *  Output: 1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = longestSubarray(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
