#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxAdjacentDistance(int* nums, int numsSize) {
    int retVal = 0;

    retVal = fmax(retVal, abs(nums[0] - nums[numsSize - 1]));
    for (int i = 1; i < numsSize; ++i) {
        retVal = fmax(retVal, abs(nums[i] - nums[i - 1]));
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 4}, 3}, {{-5, -10, -5}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,4]
     *  Output: 3
     *
     *  Input: nums = [-5,-10,-5]
     *  Output: 5
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = maxAdjacentDistance(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
