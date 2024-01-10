#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isMonotonic(int* nums, int numsSize) {
    bool retVal = true;

    if (numsSize == 1) {  // 1 <= nums.length <= 10^5
        return retVal;
    }

    int diff = 1;
    int previous = 0;
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] == nums[i - 1]) {
            continue;
        } else if (nums[i] > nums[i - 1]) {
            diff = 1;
        } else if (nums[i] < nums[i - 1]) {
            diff = -1;
        }

        if (previous != 0) {
            if (previous != diff) {
                retVal = false;
                break;
            }
        }
        previous = diff;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 2, 3}, 4}, {{6, 5, 4, 4}, 4}, {{1, 3, 2}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,2,3]
     *  Output: true
     *
     *  Input: nums = [6,5,4,4]
     *  Output: true
     *
     *  Input: nums = [1,3,2]
     *  Output: false
     */

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = isMonotonic(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
