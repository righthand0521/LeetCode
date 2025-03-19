#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minOperations(int* nums, int numsSize) {
    int retVal = 0;

    for (int i = 0; i < numsSize - 2; ++i) {
        if (nums[i] == 1) {
            continue;
        }
        nums[i] = 1;
        nums[i + 1] = (nums[i + 1] == 0) ? 1 : 0;
        nums[i + 2] = (nums[i + 2] == 0) ? 1 : 0;
        retVal++;
    }
    if ((nums[numsSize - 2] == 0) || (nums[numsSize - 1] == 0)) {
        retVal = -1;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{0, 1, 1, 1, 0, 0}, 6}, {{0, 1, 1, 1}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [0,1,1,1,0,0]
     *  Output: 3
     *
     *  Input: nums = [0,1,1,1]
     *  Output: -1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minOperations(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
