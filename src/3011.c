#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool canSortArray(int* nums, int numsSize) {
    bool retVal = true;

    int lastCnt = 0;
    int lastGroupMax = 0;
    int curGroupMax = 0;
    int curCnt;
    int i;
    for (i = 0; i < numsSize; i++) {
        curCnt = __builtin_popcount(nums[i]);
        if (curCnt == lastCnt) {
            curGroupMax = fmax(curGroupMax, nums[i]);
        } else {
            lastCnt = curCnt;
            lastGroupMax = curGroupMax;
            curGroupMax = nums[i];
        }

        if (nums[i] < lastGroupMax) {
            retVal = false;
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{8, 4, 2, 30, 15}, 5}, {{1, 2, 3, 4, 5}, 5}, {{3, 16, 8, 4, 2}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [8,4,2,30,15]
     *  Output: true
     *
     *  Input: nums = [1,2,3,4,5]
     *  Output: true
     *
     *  Input: nums = [3,16,8,4,2]
     *  Output: false
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = canSortArray(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
