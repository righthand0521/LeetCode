#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dominantIndex(int* nums, int numsSize) {
    int retVal = 0;

    int largest = nums[0];
    int second = 0;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i] > largest) {
            second = largest;
            largest = nums[i];
            retVal = i;
            continue;
        }
        second = (second > nums[i]) ? second : nums[i];
    }

    if (largest < (2 * second)) {
        retVal = -1;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_NUMSSIZE (50)
    struct testCaseType {
        int nums[MAX_NUMSSIZE];
        int numsSize;
    } testCase[] = {{{3, 6, 1, 0}, 4}, {{1, 2, 3, 4}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = dominantIndex(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
