#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool increasingTriplet(int* nums, int numsSize) {
    bool retVal = false;

    int first = INT_MAX;
    int second = INT_MAX;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] <= first) {
            first = nums[i];
        } else if (nums[i] <= second) {
            second = nums[i];
        } else {
            retVal = true;
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 3, 4, 5}, 5}, {{5, 4, 3, 2, 1}, 5}, {{2, 1, 5, 0, 4, 6}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3,4,5]
     *  Output: true
     *
     *  Input: nums = [5,4,3,2,1]
     *  Output: false
     *
     *  Input: nums = [2,1,5,0,4,6]
     *  Output: true
     */

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = increasingTriplet(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
