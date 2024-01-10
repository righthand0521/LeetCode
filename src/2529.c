#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maximumCount(int *nums, int numsSize) {
    int retVal = 0;

    int negative = 0;
    int zero = 0;
    int positive = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] < 0) {
            ++negative;
        } else if (nums[i] == 0) {
            ++zero;
        } else {
            break;
        }
    }
    positive = numsSize - negative - zero;

    retVal = fmax(negative, positive);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (8)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{-2, -1, -1, 1, 2, 3}, 6}, {{-3, -2, -1, 0, 0, 1, 2}, 7}, {{5, 20, 66, 1314}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [-2,-1,-1,1,2,3]
     *  Output: 3
     *
     *  Input: nums = [-3,-2,-1,0,0,1,2]
     *  Output: 3
     *
     *  Input: nums = [5,20,66,1314]
     *  Output: 4
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = maximumCount(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
