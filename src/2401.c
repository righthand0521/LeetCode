#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestNiceSubarray(int* nums, int numsSize) {
    int retVal = 0;

    int niceCheck = 0;
    int head = 0;
    int tail = 0;
    while (tail < numsSize) {
        while ((niceCheck & nums[tail]) != 0) {
            niceCheck ^= nums[head];
            ++head;
        }
        retVal = fmax(retVal, tail - head + 1);

        niceCheck |= nums[tail];
        ++tail;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 3, 8, 48, 10}, 5}, {{3, 1, 5, 11, 13}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums  = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = longestNiceSubarray(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
