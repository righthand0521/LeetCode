#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool check(int* nums, int numsSize) {
    bool retVal = true;

    if (numsSize <= 1) {
        return retVal;
    }

    int inversionCount = 0;
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i - 1] > nums[i]) {
            inversionCount++;
        }
    }
    if (nums[numsSize - 1] > nums[0]) {
        inversionCount++;
    }
    retVal = (inversionCount <= 1);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{3, 4, 5, 1, 2}, 5}, {{2, 1, 3, 4}, 4}, {{1, 2, 3}, 3}, {{2, 4, 1, 3}, 4}, {{1, 3, 2}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,4,5,1,2]
     *  Output: true
     *
     *  Input: nums = [2,1,3,4]
     *  Output: false
     *
     *  Input: nums = [1,2,3]
     *  Output: true
     *
     *  Input: nums = [2,4,1,3]
     *  Output: false
     *
     *  Input: nums = [1,3,2]
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

        answer = check(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
