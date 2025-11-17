#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool kLengthApart(int* nums, int numsSize, int k) {
    bool retVal = false;

    int previous = -1;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] != 1) {
            continue;
        }
        if ((previous != -1) && (i - previous - 1 < k)) {
            return retVal;
        }
        previous = i;
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 0, 0, 0, 1, 0, 0, 1}, 8, 2}, {{1, 0, 0, 1, 0, 1}, 6, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example:
     *  Input: nums = [1,0,0,0,1,0,0,1], k = 2
     *  Output: true
     *
     *  Input: nums = [1,0,0,1,0,1], k = 2
     *  Output: false
     */

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = kLengthApart(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
