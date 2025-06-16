#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maximumDifference(int* nums, int numsSize) {
    int retVal = -1;  // If no such i and j exists, return -1.

    int minNum = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] > minNum) {
            retVal = fmax(retVal, nums[i] - minNum);
        } else {
            minNum = nums[i];
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{7, 1, 5, 4}, 4}, {{9, 4, 3, 2}, 4}, {{1, 5, 2, 10}, 4}, {{9, 4, 4}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [7,1,5,4]
     *  Output: 4
     *
     *  Input: nums = [9,4,3,2]
     *  Output: -1
     *
     *  Input: nums = [1,5,2,10]
     *  Output: 9
     *
     *  Input: nums = [9,4,4]
     *  Output: -1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", j == 0 ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = maximumDifference(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
