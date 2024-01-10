#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/tallest-billboard/solutions/368725/yi-quan-ji-ben-mei-shuo-ming-bai-de-zhe-pian-kan-l/
int tallestBillboard(int *rods, int rodsSize) {
    int retVal = 0;

    int i;

    // sum(rods[i]) <= 5000
    int maxSum = 0;
    for (i = 0; i < rodsSize; ++i) {
        maxSum += rods[i];
    }
    int dpShift = maxSum + 1;
    int dpSize = 2 * dpShift + 1;
    int dp[dpSize];
    memset(dp, -1, sizeof(dp));
    dp[dpShift] = 0;

    int idx;
    int tmp[dpSize];
    for (i = 0; i < rodsSize; ++i) {
        memset(tmp, 0, sizeof(tmp));
        memcpy(tmp, dp, sizeof(tmp));
        for (idx = 0; idx < dpSize; ++idx) {
            if (tmp[idx] == -1) {
                continue;
            }
            dp[idx + rods[i]] = fmax(dp[idx + rods[i]], tmp[idx] + rods[i]);
            dp[idx - rods[i]] = fmax(dp[idx - rods[i]], tmp[idx]);
        }
    }
    retVal = dp[dpShift];

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (20)
    struct testCaseType {
        int rods[MAX_SIZE];
        int rodsSize;
    } testCase[] = {{{1, 2, 3, 6}, 4}, {{1, 2, 3, 4, 5, 6}, 6}, {{1, 2}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: rods = [1,2,3,6]
     *  Output: 6
     *
     *  Input: rods = [1,2,3,4,5,6]
     *  Output: 10
     *
     *  Input: rods = [1,2]
     *  Output: 0
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: rods = [");
        for (j = 0; j < testCase[i].rodsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].rods[j]);
        }
        printf("]\n");

        answer = tallestBillboard(testCase[i].rods, testCase[i].rodsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
