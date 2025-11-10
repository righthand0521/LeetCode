#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minOperations(int* nums, int numsSize) {
    int retVal = 0;

    int monotonicStack[numsSize];
    int monotonicStackTop = 0;
    int num;
    for (int i = 0; i < numsSize; ++i) {
        num = nums[i];
        while ((monotonicStackTop > 0) && (monotonicStack[monotonicStackTop - 1] > num)) {
            --monotonicStackTop;
        }
        if (num == 0) {
            continue;
        }

        if ((monotonicStackTop == 0) || (monotonicStack[monotonicStackTop - 1] < num)) {
            retVal++;
            monotonicStack[monotonicStackTop++] = num;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{0, 2}, 2}, {{3, 1, 2, 1}, 4}, {{1, 2, 1, 2, 1, 2}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [0,2]
     *  Output: 1
     *
     *  Input: nums = [3,1,2,1]
     *  Output: 3
     *
     *  Input: nums = [1,2,1,2,1,2]
     *  Output: 4
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
