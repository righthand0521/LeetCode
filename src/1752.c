#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool check(int* nums, int numsSize) {
    bool retVal = false;

    int head1 = 0;
    int tail1 = 0;
    int head2 = 0;
    int tail2 = numsSize - 1;

    int i;
    for (i = head1 + 1; i < numsSize; ++i) {
        if (nums[i - 1] <= nums[i]) {
            continue;
        }
        tail1 = i - 1;
        head2 = i;
        break;
    }
    if (i == numsSize) {
        retVal = true;
        return retVal;
    }

    for (i = head2 + 1; i < numsSize; ++i) {
        if (nums[i - 1] <= nums[i]) {
            continue;
        }
        return retVal;
    }

    if ((nums[head1] < nums[head2]) || (nums[head1] < nums[tail2])) {
        return retVal;
    } else if ((nums[tail1] < nums[head2]) || (nums[tail1] < nums[tail2])) {
        return retVal;
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{3, 4, 5, 1, 2}, 5}, {{2, 1, 3, 4}, 4}, {{1, 2, 3}, 3}, {{2, 4, 1, 3}, 4}, {{1, 3, 2}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,4,5,1,2]
     *  Output: true
     *
     *  Input: nums = [2,1,3,4]
     *  Output: false
     *
     *  Input: nums = [1,2,3]
     *  Output: true
     *
     *  Input: nums = [2,4,1,3]
     *  Output: false
     *
     *  Input: nums = [1,3,2]
     *  Output: false
     */

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = check(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
