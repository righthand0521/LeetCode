#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool hasIncreasingSubarrays(int* nums, int numsSize, int k) {
    bool retVal = false;

    int current = 1;
    int previous = 0;
    int answer = 0;
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] > nums[i - 1]) {
            ++current;
        } else {
            previous = current;
            current = 1;
        }

        answer = fmax(answer, fmin(previous, current));
        answer = fmax(answer, current / 2);
    }

    retVal = (answer >= k);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{2, 5, 7, 8, 9, 2, 3, 4, 3, 1}, 10, 3}, {{1, 2, 3, 4, 4, 4, 4, 5, 6, 7}, 10, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example:
     *  Input: nums = [2,5,7,8,9,2,3,4,3,1], k = 3
     *  Output: true
     *
     *  Input: nums = [1,2,3,4,4,4,4,5,6,7], k = 5
     *  Output: false
     */

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = hasIncreasingSubarrays(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
