#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool canJump(int* nums, int numsSize) {
    bool retVal = false;

    /* maxPosition is index + nums[index]
     *  If maxPosition could not reach next index, thah is, it could not reach the last index.
     */
    int maxPosition = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (i > maxPosition) {
            return retVal;
        }

        maxPosition = fmax(maxPosition, i + nums[i]);
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 3, 1, 1, 4}, 5}, {{3, 2, 1, 0, 4}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,3,1,1,4]
     *  Output: true
     *
     *  Input: nums = [3,2,1,0,4]
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

        answer = canJump(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
