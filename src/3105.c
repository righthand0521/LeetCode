#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestMonotonicSubarray(int* nums, int numsSize) {
    int retVal = 1;

    int increasing = 1;
    int decreasing = 1;
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i - 1] < nums[i]) {
            increasing += 1;
            decreasing = 1;
        } else if (nums[i - 1] > nums[i]) {
            decreasing += 1;
            increasing = 1;
        } else {
            increasing = 1;
            decreasing = 1;
        }
        retVal = fmax(retVal, fmax(increasing, decreasing));
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 4, 3, 3, 2}, 5}, {{3, 3, 3, 3}, 4}, {{3, 2, 1}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,4,3,3,2]
     *  Output: 2
     *
     *  Input: nums = [3,3,3,3]
     *  Output: 1
     *
     *  Input: nums = [3,2,1]
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = longestMonotonicSubarray(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
