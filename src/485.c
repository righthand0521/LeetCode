#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findMaxConsecutiveOnes(int* nums, int numsSize) {
    int retVal = 0;

    int count = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] == 1) {
            ++count;
            continue;
        }
        retVal = (retVal > count) ? retVal : count;
        count = 0;
    }
    retVal = (retVal > count) ? retVal : count;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 1, 0, 1, 1, 1}, 6}, {{1, 0, 1, 1, 0, 1}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,1,0,1,1,1]
     *  Output: 3
     *
     *  Input: nums = [1,0,1,1,0,1]
     *  Output: 2
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = findMaxConsecutiveOnes(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
