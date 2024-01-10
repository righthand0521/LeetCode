#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestSubarray(int* nums, int numsSize) {
    int retVal = 0;

    int i;
    int start = 0;
    int zeroCount = 0;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] == 0) {
            ++zeroCount;
        }

        while (zeroCount > 1) {
            if (nums[start] == 0) {
                --zeroCount;
            }
            ++start;
        }

        retVal = fmax(retVal, i - start);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 1, 0, 1}, 4}, {{0, 1, 1, 1, 0, 1, 1, 0, 1}, 9}, {{1, 1, 1}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,1,0,1]
     *  Output: 3
     *
     *  Input: nums = [0,1,1,1,0,1,1,0,1]
     *  Output: 5
     *
     *  Input: nums = [1,1,1]
     *  Output: 2
     */

    int i, j;
    int answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = longestSubarray(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
