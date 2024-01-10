#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int waysToMakeFair(int* nums, int numsSize) {
    int retVal = 0;

    /* https://leetcode.com/problems/ways-to-make-a-fair-array/solutions/944544/java-python-python-easy-and-concise/
     *
     *  left[odd] + right[even] = left[even] + right[odd]
     *  +-----------------------------+---------------------------+
     *  | 0 | 1 | 2 | 3 | 4 | 5 | ... | 0 _ 2 _ 4 _ | _ 1 _ 3 _ 5 |
     *  +-----------------------------+---------------------------+
     *  |   | 1 | 2 | 3 | 4 | 5 | ... | x _ 2 _ 4 _ | _ 1 _ 3 _ 5 |
     *  | 0 |   | 2 | 3 | 4 | 5 | ... | x _ 2 _ 4 _ | 0 x _ 3 _ 5 |
     *  | 0 | 1 |   | 3 | 4 | 5 | ... | x 1 x _ 4 _ | 0 x _ 3 _ 5 |
     *  | 0 | 1 | 2 |   | 4 | 5 | ... | x 1 x _ 4 _ | 0 x 2 x _ 5 |
     *  | 0 | 1 | 2 | 3 |   | 5 | ... | x 1 x 3 x _ | 0 x 2 x _ 5 |
     *  | 0 | 1 | 2 | 3 | 4 |   | ... | x 1 x 3 x _ | 0 x 2 x 4 x |
     *  +-----------------------------+---------------------------+
     */

    int i;

    int right[2];
    memset(right, 0, sizeof(right));
    for (i = 0; i < numsSize; ++i) {
        right[i % 2] += nums[i];
    }

    int left[2];
    memset(left, 0, sizeof(left));
    for (i = 0; i < numsSize; ++i) {
        right[i % 2] -= nums[i];
        if ((left[(i + 1) % 2] + right[i % 2]) == (left[i % 2] + right[(i + 1) % 2])) {
            ++retVal;
        }
        left[i % 2] += nums[i];
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 1, 6, 4}, 4}, {{1, 1, 1}, 3}, {{1, 2, 3}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = waysToMakeFair(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
