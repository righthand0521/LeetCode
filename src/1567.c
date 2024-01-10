#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getMaxLen(int* nums, int numsSize) {
    int retVal = 0;

    int positive = (nums[0] > 0 ? 1 : 0);
    int negative = (nums[0] < 0 ? 1 : 0);
    retVal = positive;

    int tmp;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i] == 0) {
            positive = 0;
            negative = 0;
        } else if (nums[i] > 0) {
            ++positive;
            negative = (negative > 0 ? negative + 1 : 0);
        } else if (nums[i] < 0) {
            tmp = positive;
            positive = (negative > 0 ? negative + 1 : 0);
            negative = tmp + 1;
        }

        retVal = fmax(retVal, positive);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, -2, -3, 4}, 4},
                    {{0, 1, -2, -3, -4}, 5},
                    {{-1, -2, -3, 0, 1}, 5},
                    {{1, 2, 3, 5, -6, 4, 0, 10}, 8},
                    {{5, -20, -20, -39, -5, 0, 0, 0, 36, -32, 0, -7, -10, -7, 21, 20, -12, -34, 26, 2}, 20}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = getMaxLen(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
