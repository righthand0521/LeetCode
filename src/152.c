#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
int maxProduct(int* nums, int numsSize) {
    int retVal = INT_MIN;

    int max = 1;
    int min = 1;
    int tmp;
    int i;
    for (i = 0; i < numsSize; ++i) {
        /* Dynamic Programming
         *  keep max = MAX(max, nums[i])
         *  keep min = MAX(min, nums[i]) because -10 <= nums[i] <= 10
         *  swap max and min if nums[i] < 0
         *
         *  Example
         *   nums[] = {2, 3, -2, 4}
         *   nums[0]=2: keep max=2, min=2; retVal=2.
         *   nums[1]=3: keep max=6, min=3; retVal=6.
         *   nums[2]=-2: swap max=3, min=6; keep max=-2, min=-12; retVal=6.
         *   nums[3]=4: keep max=4, min=-48; retVal=6.
         */
        if (nums[i] < 0) {
            tmp = max;
            max = min;
            min = tmp;
        }
        max = MAX(nums[i], (max * nums[i]));
        min = MIN(nums[i], (min * nums[i]));
        retVal = MAX(retVal, max);
        // printf("%d: %d; %d, %d; %d\n", i, nums[i], max, min, retVal);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 3, -2, 4}, 4}, {{-2, 0, -1}, 3}, {{-3, -1, -1}, 3}, {{0, 2}, 2}, {{-1, -2, -9, -6}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = maxProduct(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
