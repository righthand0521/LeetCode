#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BINARY_SEARCH (1)
#define DYNAMIC_PROGRAMMING (1)
int lengthOfLIS(int* nums, int numsSize) {
    int retVal = 0;

    if (numsSize == 0) {
        return retVal;
    }

#if (BINARY_SEARCH)
    printf("BINARY_SEARCH\n");

    int greedy[numsSize + 1];
    memset(greedy, 0, sizeof(greedy));
    int idx = 1;
    greedy[idx] = nums[0];

    int left, right, middle;
    int position;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i] > greedy[idx]) {
            greedy[++idx] = nums[i];
            continue;
        }

        left = 1;
        right = idx;
        position = 0;
        while (left < right) {
            middle = left + (right - left) / 2;
            if (greedy[middle] < nums[i]) {
                position = middle;
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        greedy[position + 1] = nums[i];
    }
    retVal = idx;
#elif (DYNAMIC_PROGRAMMING)
    printf("DYNAMIC_PROGRAMMING\n");

    int dp[numsSize];
    memset(dp, 0, sizeof(dp));
    int i, j;
    for (i = 0; i < numsSize; ++i) {
        dp[i] = 1;
        for (j = 0; j < i; ++j) {
            if (nums[j] < nums[i]) {
                dp[i] = fmax(dp[i], dp[j] + 1);
            }
        }
    }

    for (i = 0; i < numsSize; ++i) {
        retVal = fmax(retVal, dp[i]);
    }
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2500)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{10, 9, 2, 5, 3, 7, 101, 18}, 8}, {{0, 1, 0, 3, 2, 3}, 6}, {{7, 7, 7, 7, 7, 7, 7}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [10,9,2,5,3,7,101,18]
     *  Output: 4
     *
     *  Input: nums = [0,1,0,3,2,3]
     *  Output: 4
     *
     *  Input: nums = [7,7,7,7,7,7,7]
     *  Output: 1
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = lengthOfLIS(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
