#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int a, int b) {
    int retVal = 0;

    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    retVal = a;

    return retVal;
}
int minOperations(int* nums, int numsSize) {
    int retVal = -1;

    int numberOfOne = 0;
    int greatestCommonDivisor = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 1) {
            numberOfOne++;
        }
        greatestCommonDivisor = gcd(greatestCommonDivisor, nums[i]);
    }
    if (numberOfOne > 0) {
        retVal = numsSize - numberOfOne;
        return retVal;
    } else if (greatestCommonDivisor > 1) {
        return retVal;
    }

    int minNumsSize = numsSize;
    for (int i = 0; i < numsSize; i++) {
        greatestCommonDivisor = 0;
        for (int j = i; j < numsSize; j++) {
            greatestCommonDivisor = gcd(greatestCommonDivisor, nums[j]);
            if (greatestCommonDivisor == 1) {
                if (j - i + 1 < minNumsSize) {
                    minNumsSize = j - i + 1;
                }
                break;
            }
        }
    }
    retVal = minNumsSize + numsSize - 2;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 6, 3, 4}, 4}, {{2, 10, 6, 14}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,6,3,4]
     *  Output: 4
     *
     *  Input: nums = [2,10,6,14]
     *  Output: -1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minOperations(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
