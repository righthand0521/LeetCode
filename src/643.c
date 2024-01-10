#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double findMaxAverage(int* nums, int numsSize, int k) {
    double retVal = 0;

    int sum = 0;
    int i;
    for (i = 0; i < k; ++i) {
        sum += nums[i];
    }
    double max = sum;

    for (i = k; i < numsSize; ++i) {
        sum += (nums[i] - nums[i - k]);
        max = fmax(max, sum);
    }
    retVal = max / k;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 12, -5, -6, 50, 3}, 6, 4}, {{5}, 1, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,12,-5,-6,50,3], k = 4
     *  Output: 12.75000
     *
     *  Input: nums = [5], k = 1
     *  Output: 5.00000
     */

    double answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = findMaxAverage(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %f\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
