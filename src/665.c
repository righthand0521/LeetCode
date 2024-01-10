#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool checkPossibility(int* nums, int numsSize) {
    bool retVal = false;

    int modify = 0;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i - 1] <= nums[i]) {
            continue;
        }

        ++modify;
        if (modify > 1) {
            return retVal;
        }
        if ((i >= 2) && (nums[i] < nums[i - 2])) {
            nums[i] = nums[i - 1];
        }
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{4, 2, 3}, 3}, {{4, 2, 1}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = checkPossibility(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
