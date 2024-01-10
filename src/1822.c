#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arraySign(int* nums, int numsSize) {
    int retVal = 1;

    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] == 0) {
            retVal = 0;
            break;
        } else if (nums[i] > 0) {
            retVal *= 1;
        } else if (nums[i] < 0) {
            retVal *= (-1);
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{-1, -2, -3, -4, 3, 2, 1}, 7}, {{1, 5, 0, 2, -3}, 5}, {{-1, 1, -1, 1, -1}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [-1,-2,-3,-4,3,2,1]
     *  Output: 1
     *
     *  Input: nums = [1,5,0,2,-3]
     *  Output: 0
     *
     *  Input: nums = [-1,1,-1,1,-1]
     *  Output: -1
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", ((j == 0) ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = arraySign(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
