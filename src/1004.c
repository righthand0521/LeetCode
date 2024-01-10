#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestOnes(int *nums, int numsSize, int k) {
    int retVal = 0;

    int flip = 0;
    int left = 0;
    int right = 0;
    for (right = 0; right < numsSize; ++right) {
        flip += (1 - nums[right]);
        while (flip > k) {
            flip -= (1 - nums[left]);
            left += 1;
        }

        retVal = fmax(retVal, right - left + 1);
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0}, 11, 2},
                    {{0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1}, 19, 3},
                    {{0, 0, 0, 0}, 4, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
     *  Output: 6
     *
     *  Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
     *  Output: 10
     *
     *  Input: nums = [0,0,0,0], k = 0
     *  Output: 0
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = longestOnes(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
