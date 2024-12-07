#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isPossible(int maxBallsInBag, int* nums, int numsSize, int maxOperations) {
    bool retVal = true;  // We can split the balls within the allowed operations, return true

    int operations;
    int totalOperations = 0;
    for (int i = 0; i < numsSize; ++i) {
        // Calculate the number of operations needed to split this bag
        operations = ceil(nums[i] / (double)maxBallsInBag) - 1;
        totalOperations += operations;

        // Total operations exceed maxOperations, return false
        if (totalOperations > maxOperations) {
            retVal = false;
            break;
        }
    }

    return retVal;
}
int minimumSize(int* nums, int numsSize, int maxOperations) {
    int retVal = 0;

    // Perform binary search to find the optimal maxBallsInBag
    int left = 1;
    int right = 0;
    for (int i = 0; i < numsSize; ++i) {
        right = fmax(right, nums[i]);
    }
    int middle;
    while (left < right) {
        middle = (left + right) / 2;

        // Check if a valid distribution is possible with the current middle value
        if (isPossible(middle, nums, numsSize, maxOperations)) {
            right = middle;  // If possible, try a smaller value (shift right to middle)
        } else {
            left = middle + 1;  // If not possible, try a larger value (shift left to middle + 1)
        }
    }
    retVal = left;  // Return the smallest possible value for maxBallsInBag

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int maxOperations;
    } testCase[] = {{{9}, 1, 2}, {{2, 4, 8, 2}, 4, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [9], maxOperations = 2
     *  Output: 3
     *
     *  Input: nums = [2,4,8,2], maxOperations = 4
     *  Output: 2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], maxOperations = %d\n", testCase[i].maxOperations);

        answer = minimumSize(testCase[i].nums, testCase[i].numsSize, testCase[i].maxOperations);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
