#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countPartitions(int* nums, int numsSize) {
    int retVal = 0;

    int sumNums = 0;
    for (int i = 0; i < numsSize; ++i) {
        sumNums += nums[i];
    }
    if (sumNums % 2 == 0) {
        retVal = numsSize - 1;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{10, 10, 3, 7, 6}, 5}, {{1, 2, 2}, 3}, {{2, 4, 6, 8}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [10,10,3,7,6]
     *  Output: 4
     *
     *  Input: nums = [1,2,2]
     *  Output: 0
     *
     *  Input: nums = [2,4,6,8]
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = countPartitions(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
