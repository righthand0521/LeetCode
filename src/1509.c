#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minDifference(int* nums, int numsSize) {
    int retVal = 0;

    if (numsSize <= 4) {  // If the array has 4 or fewer elements, return 0
        return retVal;
    }

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int minDiff = INT_MAX;
    int left, right;
    for (left = 0; left < 4; ++left) {
        right = numsSize - 4 + left;
        minDiff = fmin(minDiff, nums[right] - nums[left]);
    }
    retVal = minDiff;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{5, 3, 2, 4}, 4}, {{1, 5, 0, 10, 14}, 5}, {{3, 100, 20}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [5,3,2,4]
     *  Output: 0
     *
     *  Input: nums = [1,5,0,10,14]
     *  Output: 1
     *
     *  Input: nums = [3,100,20]
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minDifference(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
