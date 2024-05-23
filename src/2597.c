#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int beautifulSubsets(int *nums, int numsSize, int k) {
    int retVal = 0;

    if ((numsSize == 0) || (numsSize == 1)) {
        retVal = numsSize;
        return retVal;
    }

    int dp[numsSize];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    if ((nums[1] - nums[0] == k) || (nums[0] - nums[1] == k)) {
        dp[1] = 2;
    } else {
        dp[1] = 3;
    }

    int *pTemp = (int *)malloc(numsSize * sizeof(int));
    if (pTemp == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(pTemp, 0, (numsSize * sizeof(int)));

    int t = 0;
    int q = 0;
    int i, j;
    for (i = 2; i < numsSize; i++) {
        for (j = 0; j < i; j++) {
            if (nums[i] - nums[j] == k || nums[j] - nums[i] == k) {
                t++;
            } else {
                pTemp[q] = nums[j];
                q++;
            }
        }

        if (t == 0) {
            dp[i] = 2 * dp[i - 1] + 1;
        } else {
            dp[i] = dp[i - 1] + 1 + beautifulSubsets(pTemp, q, k);
        }

        t = 0;
        q = 0;
    }
    retVal = dp[numsSize - 1];

    free(pTemp);
    pTemp = NULL;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (20)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{2, 4, 6}, 3, 2}, {{1}, 1, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,4,6], k = 2
     *  Output: 4
     *
     *  Input: nums = [1], k = 1
     *  Output: 1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = beautifulSubsets(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
