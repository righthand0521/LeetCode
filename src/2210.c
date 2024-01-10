#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countHillValley(int* nums, int numsSize) {
    int retVal = 0;

    /* Example: Input: nums = [2,4,1,1,6,5]
     *  2   4   1   1   6   5
     *    2  -3   0   5  -1
     */
    int diff = 0;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i] > nums[i - 1]) {
            if (diff == -1) {
                ++retVal;
            }
            diff = 1;
        } else if (nums[i] < nums[i - 1]) {
            if (diff == 1) {
                ++retVal;
            }
            diff = -1;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 4, 1, 1, 6, 5}, 6}, {{6, 6, 5, 5, 4, 1}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,4,1,1,6,5]
     *  Output: 3
     *
     *  Input: nums = [6,6,5,5,4,1]
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

        answer = countHillValley(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
