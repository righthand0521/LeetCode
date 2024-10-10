#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxWidthRamp(int* nums, int numsSize) {
    int retVal = 0;

    int indexStackTop = -1;
    int indexStack[numsSize];
    memset(indexStack, 0, sizeof(indexStack));
    indexStack[++indexStackTop] = 0;

    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[indexStack[indexStackTop]] > nums[i]) {
            indexStack[++indexStackTop] = i;
        }
    }

    for (i = numsSize - 1; i >= 0; --i) {
        while ((indexStackTop != -1) && (nums[indexStack[indexStackTop]] <= nums[i])) {
            retVal = fmax(retVal, i - indexStack[indexStackTop]);
            indexStack[indexStackTop--] = 0;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(5 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{6, 0, 8, 2, 1, 5}, 6}, {{9, 8, 1, 0, 1, 9, 4, 0, 4, 1}, 10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [6,0,8,2,1,5]
     *  Output: 4
     *
     *  Input: nums = [9,8,1,0,1,9,4,0,4,1]
     *  Output: 7
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = maxWidthRamp(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
