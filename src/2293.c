#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minMaxGame(int* nums, int numsSize) {
    int retVal = 0;

    int i;
    while (numsSize != 1) {
        numsSize /= 2;
        for (i = 0; i < numsSize; ++i) {
            if (i % 2 == 0) {
                nums[i] = fmin(nums[2 * i], nums[2 * i + 1]);
            } else {
                nums[i] = fmax(nums[2 * i], nums[2 * i + 1]);
            }
        }
    }
    retVal = nums[0];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 3, 5, 2, 4, 8, 2, 2}, 8}, {{3}, 1}, {{70, 38, 21, 22}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minMaxGame(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
