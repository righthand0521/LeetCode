#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isArraySpecial(int* nums, int numsSize) {
    bool retVal = true;

    for (int i = 1; i < numsSize; ++i) {
        if (nums[i - 1] % 2 == nums[i] % 2) {
            retVal = false;
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1}, 1}, {{2, 1, 4}, 3}, {{4, 3, 1, 6}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1]
     *  Output: true
     *
     *  Input: nums = [2,1,4]
     *  Output: true
     *
     *  Input: nums = [4,3,1,6]
     *  Output: false
     */

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = isArraySpecial(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
