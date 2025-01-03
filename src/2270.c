#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int waysToSplitArray(int* nums, int numsSize) {
    int retVal = 0;

    long long leftSum = 0;
    long long rightSum = 0;
    for (int i = 0; i < numsSize; ++i) {
        rightSum += nums[i];
    }

    for (int i = 0; i < numsSize - 1; ++i) {
        leftSum += nums[i];
        rightSum -= nums[i];
        if (leftSum >= rightSum) {
            retVal++;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{10, 4, -8, 7}, 4}, {{2, 3, 1, 0}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [10,4,-8,7]
     *  Output: 2
     *
     *  Input: nums = [2,3,1,0]
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

        answer = waysToSplitArray(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
