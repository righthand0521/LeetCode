#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isTrionic(int* nums, int numsSize) {
    int retVal = false;

    int i = 1;

    while ((i < numsSize) && (nums[i - 1] < nums[i])) {
        i += 1;
    }
    int p = i - 1;
    if (p == 0) {
        return retVal;
    }

    while ((i < numsSize) && (nums[i - 1] > nums[i])) {
        i += 1;
    }
    int q = i - 1;
    if (q == p) {
        return retVal;
    }

    while ((i < numsSize) && (nums[i - 1] < nums[i])) {
        i += 1;
    }
    i -= 1;
    if (i != (numsSize - 1)) {
        return retVal;
    } else if (i == q) {
        return retVal;
    } else {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 3, 5, 4, 2, 6}, 6}, {{2, 1, 3}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,3,5,4,2,6]
     *  Output: true
     *
     *  Input: nums = [2,1,3]
     *  Output: false
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = isTrionic(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
