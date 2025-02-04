#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxAscendingSum(int* nums, int numsSize) {
    int retVal = 0;

    int sum = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i - 1] >= nums[i]) {
            retVal = fmax(retVal, sum);
            sum = 0;
        }
        sum += nums[i];
    }
    retVal = fmax(retVal, sum);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{10, 20, 30, 5, 10, 50}, 6}, {{10, 20, 30, 40, 50}, 5}, {{12, 17, 15, 13, 10, 11, 12}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [10,20,30,5,10,50]
     *  Output: 65
     *
     *  Input: nums = [10,20,30,40,50]
     *  Output: 150
     *
     *  Input: nums = [12,17,15,13,10,11,12]
     *  Output: 33
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = maxAscendingSum(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
