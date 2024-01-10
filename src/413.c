#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numberOfArithmeticSlices(int* nums, int numsSize) {
    int retVal = 0;

    if (numsSize <= 1) {
        return retVal;
    }

    int diff = nums[1] - nums[0];
    int count = 0;
    int i;
    for (i = 2; i < numsSize; ++i) {
        if (nums[i] - nums[i - 1] == diff) {
            ++count;
        } else {
            diff = nums[i] - nums[i - 1];
            count = 0;
        }

        retVal += count;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 3, 4}, 4}, {{1}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = numberOfArithmeticSlices(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
