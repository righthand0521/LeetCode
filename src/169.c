#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int majorityElement(int* nums, int numsSize) {
    int retVal = 0;

    /* Boyer–Moore majority vote algorithm
     *  https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm
     *
     *  Example: Input: nums = [2,2,1,1,1,2,2]
     *  +-----------+---------------------------+
     *  | nums      | 2 | 2 | 1 | 1 | 1 | 2 | 2 |
     *  | appears   | 1 | 2 | 1 | 0 | 1 | 0 | 1 |
     *  |-----------+---------------------------+
     *  | candidate | 2 | 2 | 2 | 2 | 1 | 1 | 2 |
     *  | count     | 1 | 2 | 1 | 0 | 1 | 0 | 1 |
     *  +-----------+---------------------------+
     */
    int appears = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (appears == 0) {
            retVal = nums[i];
        }

        if (retVal == nums[i]) {
            ++appears;
        } else {
            --appears;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{3, 2, 3}, 3}, {{2, 2, 1, 1, 1, 2, 2}, 7}, {{3}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,2,3]
     *  Output: 3
     *
     *  Input: nums = [2,2,1,1,1,2,2]
     *  Output: 2
     *
     *  Input: nums = [3]
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = majorityElement(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
