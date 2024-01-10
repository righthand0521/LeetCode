#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int jump(int* nums, int numsSize) {
    int retVal = 0;

    int maxPosition = 0;
    int end = 0;
    int i;
    for (i = 0; i < (numsSize - 1); ++i) {
        // find maximum jumping length
        maxPosition = fmax(maxPosition, nums[i] + i);

        // reach end boundary need to  update end boundary and add steps
        if (i == end) {
            end = maxPosition;
            ++retVal;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 3, 1, 1, 4}, 5}, {{2, 3, 0, 1, 4}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,3,1,1,4]
     *  Output: 2
     *
     *  Input: nums = [2,3,0,1,4]
     *  Output: 2
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = jump(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
