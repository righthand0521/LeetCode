#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxIncreasingSubarrays(int* nums, int numsSize) {
    int retVal = 0;

    int current = 1;
    int previous = 0;
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] > nums[i - 1]) {
            current += 1;
        } else {
            previous = current;
            current = 1;
        }
        retVal = fmax(retVal, fmin(previous, current));
        retVal = fmax(retVal, current / 2);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(2 * 100000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 5, 7, 8, 9, 2, 3, 4, 3, 1}, 10}, {{1, 2, 3, 4, 4, 4, 4, 5, 6, 7}, 10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,5,7,8,9,2,3,4,3,1]
     *  Output: 3
     *
     *  Input: nums = [1,2,3,4,4,4,4,5,6,7]
     *  Output: 2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = maxIncreasingSubarrays(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
