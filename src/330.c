#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minPatches(int* nums, int numsSize, int n) {
    int retVal = 0;

    int index = 0;
    long x = 1;
    while (x <= n) {
        if ((index < numsSize) && (nums[index] <= x)) {
            x += nums[index];
            index += 1;
        } else {
            x <<= 1;
            retVal += 1;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int n;
    } testCase[] = {{{1, 3}, 2, 6}, {{1, 5, 10}, 3, 20}, {{1, 2, 2}, 3, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,3], n = 6
     *  Output: 1
     *
     *  Input: nums = [1,5,10], n = 20
     *  Output: 2
     *
     *  Input: nums = [1,2,2], n = 5
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], n = %d\n", testCase[i].n);

        answer = minPatches(testCase[i].nums, testCase[i].numsSize, testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
