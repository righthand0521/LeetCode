#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long zeroFilledSubarray(int *nums, int numsSize) {
    long long retVal = 0;

    int contiguous = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] != 0) {
            contiguous = 0;
            continue;
        }

        ++contiguous;
        retVal += contiguous;
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 3, 0, 0, 2, 0, 0, 4}, 8}, {{0, 0, 0, 2, 0, 0}, 6}, {{2, 10, 2019}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,3,0,0,2,0,0,4]
     *  Output: 6
     *
     *  Input: nums = [0,0,0,2,0,0]
     *  Output: 9
     *
     *  Input: nums = [2,10,2019]
     *  Output: 0
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = zeroFilledSubarray(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
