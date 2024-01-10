#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findNumberOfLIS(int* nums, int numsSize) {
    int retVal = 0;

    int dpLength[numsSize];
    memset(dpLength, 0, sizeof(dpLength));
    int dpCount[numsSize];
    memset(dpCount, 0, sizeof(dpCount));
    int longestLength = 1;
    int i, j;
    for (i = 0; i < numsSize; ++i) {
        dpLength[i] = 1;
        dpCount[i] = 1;

        for (j = 0; j < i; ++j) {
            if (nums[j] >= nums[i]) {
                continue;
            }

            if (dpLength[j] + 1 > dpLength[i]) {
                dpLength[i] = dpLength[j] + 1;
                dpCount[i] = 0;
            }
            if (dpLength[j] + 1 == dpLength[i]) {
                dpCount[i] += dpCount[j];
            }
        }

        longestLength = fmax(longestLength, dpLength[i]);
    }

    for (i = 0; i < numsSize; ++i) {
        if (dpLength[i] == longestLength) {
            retVal += dpCount[i];
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 3, 5, 4, 7}, 5}, {{2, 2, 2, 2, 2}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,3,5,4,7]
     *  Output: 2
     *
     *  Input: nums = [2,2,2,2,2]
     *  Output: 5
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = findNumberOfLIS(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
