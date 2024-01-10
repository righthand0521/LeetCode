#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int smallestDivisor(int* nums, int numsSize, int threshold) {
    int retVal = 0;

    int i;

    int left = 1;
    int right = 0;
    for (i = 0; i < numsSize; ++i) {
        right = fmax(right, nums[i]);
    }

    int middle;
    int sum;
    while (left < right) {
        middle = left + (right - left) / 2;

        sum = 0;
        for (i = 0; i < numsSize; ++i) {
            sum += ((nums[i] + middle - 1) / middle);
        }

        if (sum > threshold) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int threshold;
    } testCase[] = {{{1, 2, 5, 9}, 4, 6}, {{44, 22, 33, 11, 1}, 5, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,5,9], threshold = 6
     *  Output: 5
     *
     *  Input: nums = [44,22,33,11,1], threshold = 5
     *  Output: 44
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], threshold = %d\n", testCase[i].threshold);

        answer = smallestDivisor(testCase[i].nums, testCase[i].numsSize, testCase[i].threshold);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
