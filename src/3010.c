#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumCost(int* nums, int numsSize) {
    int retVal = 0;

    int min1 = (nums[1] < nums[2]) ? (nums[1]) : (nums[2]);
    int min2 = (nums[1] < nums[2]) ? (nums[2]) : (nums[1]);
    for (int i = 3; i < numsSize; ++i) {
        if (nums[i] <= min1) {
            min2 = min1;
            min1 = nums[i];
        } else if (nums[i] < min2) {
            min2 = nums[i];
        }
    }
    retVal = nums[0] + min1 + min2;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 3, 12}, 4}, {{5, 4, 3}, 3}, {{10, 3, 1, 1}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3,12]
     *  Output: 6
     *
     *  Input: nums = [5,4,3]
     *  Output: 12
     *
     *  Input: nums = [10,3,1,1]
     *  Output: 12
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minimumCost(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
