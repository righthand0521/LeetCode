#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool find132pattern(int* nums, int numsSize) {
    bool retVal = false;

    if (numsSize < 3) {
        return retVal;
    }

    int i;

    int minStack[numsSize];
    memset(minStack, 0, sizeof(minStack));
    minStack[0] = nums[0];
    for (i = 1; i < numsSize; ++i) {
        minStack[i] = fmin(minStack[i - 1], nums[i]);
    }

    int middleStack[numsSize];
    memset(middleStack, 0, sizeof(middleStack));
    int middleStackSize = 0;
    for (i = numsSize - 1; i > -1; --i) {
        if (nums[i] <= minStack[i]) {
            continue;
        }

        while ((middleStackSize > 0) && (middleStack[middleStackSize - 1] <= minStack[i])) {
            middleStack[middleStackSize - 1] = 0;
            --middleStackSize;
        }

        if ((middleStackSize > 0) && (middleStack[middleStackSize - 1] < nums[i])) {
            retVal = true;
            break;
        }

        middleStack[middleStackSize] = nums[i];
        ++middleStackSize;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2 * 100000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 3, 4}, 4},    {{3, 1, 4, 2}, 4},    {{-1, 3, 2, 0}, 4},
                    {{1, 2, 3, 4, 0}, 5}, {{3, 5, 0, 3, 4}, 5}, {{2, 3, 1, 2}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3,4]
     *  Output: false
     *
     *  Input: nums = [3,1,4,2]
     *  Output: true
     *
     *  Input: nums = [-1,3,2,0]
     *  Output: true
     *
     *  Input: nums = [1,2,3,4,0]
     *  Output: false
     *
     *  Input: nums = [3,5,0,3,4]
     *  Output: true
     *
     *  Input: nums = [2,3,1,2]
     *  Output: false
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = find132pattern(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
