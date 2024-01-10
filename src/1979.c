#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int a, int b) {
    int remainder;
    while (b != 0) {
        remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}
int findGCD(int* nums, int numsSize) {
    int retVal = 0;

    int minNums = INT_MAX;
    int maxNums = INT_MIN;
    int i;
    for (i = 0; i < numsSize; ++i) {
        minNums = fmin(minNums, nums[i]);
        maxNums = fmax(maxNums, nums[i]);
    }
    retVal = gcd(minNums, maxNums);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 5, 6, 9, 10}, 5}, {{7, 5, 6, 8, 3}, 5}, {{3, 3}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = findGCD(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
