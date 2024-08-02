#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to calculate the minimum swaps required to group all value together
int minSwapsHelper(int* nums, int numsSize, int value) {
    int retVal = 0;

    // Count the total number of value in the array
    int totalValCount = 0;
    int i;
    for (i = numsSize - 1; i >= 0; i--) {
        if (nums[i] == value) {
            totalValCount++;
        }
    }
    // If there is no value or the array is full of value, no swaps are needed
    if ((totalValCount == 0) || (totalValCount == numsSize)) {
        return retVal;
    }

    int start = 0;
    int end = 0;
    int maxValInWindow = 0;
    int currentValInWindow = 0;

    // Initial window setup: count the number of value in the first window of size `totalValCount`
    while (end < totalValCount) {
        if (nums[end++] == value) {
            currentValInWindow++;
        }
    }
    maxValInWindow = fmax(maxValInWindow, currentValInWindow);

    // Slide the window across the array to find the maximum number of value in any window
    while (end < numsSize) {
        if (nums[start++] == value) {
            currentValInWindow--;
        }

        if (nums[end++] == value) {
            currentValInWindow++;
        }

        maxValInWindow = fmax(maxValInWindow, currentValInWindow);
    }

    // Minimum swaps are the total value minus the maximum found in any window
    retVal = totalValCount - maxValInWindow;

    return retVal;
}
int minSwaps(int* nums, int numsSize) {
    int retVal = 0;

    // Calculate the minimum swaps needed to group all 1s or all 0s together
    int op0 = minSwapsHelper(nums, numsSize, 0);  // Grouping all 0s together
    int op1 = minSwapsHelper(nums, numsSize, 1);  // Grouping all 1s together
    retVal = fmin(op0, op1);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{0, 1, 0, 1, 1, 0, 0}, 7}, {{0, 1, 1, 1, 0, 0, 1, 1, 0}, 9}, {{1, 1, 0, 0, 1}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [0,1,0,1,1,0,0]
     *  Output: 1
     *
     *  Input: nums = [0,1,1,1,0,0,1,1,0]
     *  Output: 2
     *
     *  Input: nums = [1,1,0,0,1]
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minSwaps(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
