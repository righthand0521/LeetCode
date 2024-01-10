#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int removeElement(int* nums, int numsSize, int val) {
    int retVal = 0;

    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] != val) {
            nums[retVal++] = nums[i];
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int val;
    } testCase[] = {{{3, 2, 2, 3}, 4, 3}, {{0, 1, 2, 2, 3, 0, 4, 2}, 8, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,2,2,3], val = 3
     *  Output: 2, nums = [2,2,_,_]
     *
     *  Input: nums = [0,1,2,2,3,0,4,2], val = 2
     *  Output: 5, nums = [0,1,4,0,3,_,_,_]
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], val = %d\n", testCase[i].val);

        answer = removeElement(testCase[i].nums, testCase[i].numsSize, testCase[i].val);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
