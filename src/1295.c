#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getTheNumberOfDigits(int num) {
    int retVal = 0;

    while (num > 0) {
        ++retVal;
        num /= 10;
    }

    return retVal;
}
int findNumbers(int* nums, int numsSize) {
    int retVal = 0;

    int i;
    for (i = 0; i < numsSize; ++i) {
        if (getTheNumberOfDigits(nums[i]) % 2 == 0) {
            ++retVal;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_NUMSSIZE (500)
    struct testCaseType {
        int nums[MAX_NUMSSIZE];
        int numsSize;
    } testCase[] = {{{12, 345, 2, 6, 7896}, 5}, {{555, 901, 482, 1771}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = findNumbers(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
