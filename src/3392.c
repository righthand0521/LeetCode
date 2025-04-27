#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countSubarrays(int* nums, int numsSize) {
    int retVal = 0;

    for (int i = 0; i < numsSize - 2; ++i) {
        if (2 * (nums[i] + nums[i + 2]) == nums[i + 1]) {
            retVal++;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 1, 4, 1}, 5}, {{1, 1, 1}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,1,4,1]
     *  Output: 1
     *
     *  Input: nums = [1,1,1]
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

        answer = countSubarrays(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
