#include <math.h>
#include <stdbool.h>
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
int countDifferentSubsequenceGCDs(int* nums, int numsSize) {
    int retVal = 0;

    int i, j;

    int maxNums = 0;
    for (i = 0; i < numsSize; ++i) {
        maxNums = fmax(maxNums, nums[i]);
    }
    bool NumsExist[maxNums + 1];
    memset(NumsExist, false, sizeof(NumsExist));
    for (i = 0; i < numsSize; ++i) {
        NumsExist[nums[i]] = true;
    }

    int subGcd;
    for (i = 1; i <= maxNums; i++) {
        subGcd = 0;
        for (j = i; j <= maxNums; j += i) {
            if (NumsExist[j] == false) {
                continue;
            }

            if (subGcd == 0) {
                subGcd = j;
            } else {
                subGcd = gcd(subGcd, j);
            }

            if (subGcd == i) {
                ++retVal;
                break;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{6, 10, 3}, 3}, {{5, 15, 40, 5, 6}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = countDifferentSubsequenceGCDs(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
