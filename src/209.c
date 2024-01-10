#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minSubArrayLen(int target, int* nums, int numsSize) {
    int retVal = numsSize + 1;

    int sum = 0;
    int head = 0;
    int tail;
    for (tail = 0; tail < numsSize; ++tail) {
        sum += nums[tail];
        while (sum >= target) {
            retVal = fmin(retVal, (tail - head + 1));
            sum -= nums[head++];
        }
    }
    if (retVal == numsSize + 1) {
        retVal = 0;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        int target;
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{7, {2, 3, 1, 2, 4, 3}, 6}, {4, {1, 4, 4}, 3}, {11, {1, 1, 1, 1, 1, 1, 1, 1}, 8}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: target = 7, nums = [2,3,1,2,4,3]
     *  Output: 2
     *
     *  Input: target = 4, nums = [1,4,4]
     *  Output: 1
     *
     *  Input: target = 11, nums = [1,1,1,1,1,1,1,1]
     *  Output: 0
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: target = %d, nums = [", testCase[i].target);
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minSubArrayLen(testCase[i].target, testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
