#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int removeDuplicates(int* nums, int numsSize) {
    int retVal = 0;

    if (numsSize == 0) {
        return retVal;
    }

    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[retVal] != nums[i]) {
            nums[++retVal] = nums[i];
        }
    }
    ++retVal;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 1, 2}, 3}, {{0, 0, 1, 1, 1, 2, 2, 3, 3, 4}, 10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,1,2]
     *  Output: 2, nums = [1,2,_]
     *
     *  Input: nums = [0,0,1,1,1,2,2,3,3,4]
     *  Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = removeDuplicates(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
