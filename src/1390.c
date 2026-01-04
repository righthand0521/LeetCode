#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sumFourDivisors(int* nums, int numsSize) {
    int retVal = 0;

    int num, factorCount, factorSum;
    for (int i = 0; i < numsSize; ++i) {
        num = nums[i];
        factorCount = 0;
        factorSum = 0;
        for (int j = 1; j * j <= num; ++j) {
            if (num % j != 0) {
                continue;
            }
            factorCount++;
            factorSum += j;
            if (j * j != num) {
                factorCount++;
                factorSum += (num / j);
            }
        }
        if (factorCount == 4) {
            retVal += factorSum;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{21, 4, 7}, 3}, {{21, 21}, 2}, {{1, 2, 3, 4, 5}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [21,4,7]
     *  Output: 32
     *
     *  Input: nums = [21,21]
     *  Output: 64
     *
     *  Input: nums = [1,2,3,4,5]
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

        answer = sumFourDivisors(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
