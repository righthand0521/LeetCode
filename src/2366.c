#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long minimumReplacement(int* nums, int numsSize) {
    long long retVal = 0;

    long long operations;
    int i;
    for (i = numsSize - 2; i >= 0; --i) {
        if (nums[i] <= nums[i + 1]) {
            continue;
        }

        operations = (nums[i] + nums[i + 1] - 1) / nums[i + 1];
        retVal += (operations - 1);
        nums[i] = nums[i] / operations;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{3, 9, 3}, 3}, {{1, 2, 3, 4, 5}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,9,3]
     *  Output: 2
     *
     *  Input: nums = [1,2,3,4,5]
     *  Output: 0
     */

    long long answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", ((j == 0) ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minimumReplacement(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
