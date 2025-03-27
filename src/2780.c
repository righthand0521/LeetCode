#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumIndex(int* nums, int numsSize) {
    int retVal = -1;  // If no valid split exists, return -1.

    // Find the majority element
    int x = nums[0];
    int count = 0;
    for (int index = 0; index < numsSize; index++) {
        if (nums[index] == x) {
            count++;
        } else {
            count--;
        }

        if (count == 0) {
            x = nums[index];
            count = 1;
        }
    }

    // Count frequency of majority element
    int xCount = 0;
    for (int index = 0; index < numsSize; index++) {
        if (nums[index] == x) {
            xCount++;
        }
    }

    // Check if valid split is possible
    count = 0;
    for (int index = 0; index < numsSize; index++) {
        if (nums[index] == x) {
            count++;
        }

        int remainingCount = xCount - count;

        if ((count * 2 > index + 1) && (remainingCount * 2 > numsSize - index - 1)) {
            retVal = index;
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 2, 2}, 4}, {{2, 1, 3, 1, 1, 1, 7, 1, 2, 1}, 10}, {{3, 3, 3, 3, 7, 2, 2}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,2,2]
     *  Output: 2
     *
     *  Input: nums = [2,1,3,1,1,1,7,1,2,1]
     *  Output: 4
     *
     *  Input: nums = [3,3,3,3,7,2,2]
     *  Output: -1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minimumIndex(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
