#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int specialArray(int* nums, int numsSize) {
    int retVal = -1;

    int frequency[numsSize + 1];
    memset(frequency, 0, sizeof(frequency));

    int index;
    int i;
    for (i = 0; i < numsSize; ++i) {
        index = fmin(numsSize, nums[i]);
        frequency[index] += 1;
    }

    int greaterThanOrEqual = 0;
    for (i = numsSize; i >= 0; --i) {
        greaterThanOrEqual += frequency[i];
        if (i == greaterThanOrEqual) {
            retVal = i;
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
    } testCase[] = {{{3, 5}, 2}, {{0, 0}, 2}, {{0, 4, 3, 0, 4}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,5]
     *  Output: 2
     *
     *  Input: nums = [0,0]
     *  Output: -1
     *
     *  Input: nums = [0,4,3,0,4]
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = specialArray(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
