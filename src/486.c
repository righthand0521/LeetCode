#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool PredictTheWinner(int* nums, int numsSize) {
    int retVal = false;

    /* https://leetcode.cn/problems/predict-the-winner/solutions/396343/shou-hua-tu-jie-san-chong-xie-fa-di-gui-ji-yi-hua-/
     *  i = j: dp[i][j] = nums[i]
     *  i < j: dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]
     *
     *  Example: nums = [1,5,2]
     *    | 1 5 2 | 1 5 2 | 1 5 2 | 1 5  2
     *  --+-------+-------+-------+--------
     *  1 | 1     | 1     | 1 4   | 1 4 -2
     *  5 | 0 5   | 0 5 3 | 0 5 3 | 0 5  3
     *  2 | 0 0 2 | 0 0 2 | 0 0 2 | 0 0  2
     *
     *  Example: nums = [1,5,233,7]
     *      | 1 5 233 7 | 1  5 233  7  | 1 5 233   7  | 1 5 233   7
     *  ----+-----------+--------------+--------------+-------------
     *   1  | 1         | 1            | 1            | 1 4 229  222
     *   5  | 0 5       | 0  5         | 0 5 228 -221 | 0 5 229 -221
     *  233 | 0 0 233   | 0  0 233 226 | 0 0 233  226 | 0 0 233  226
     *   7  | 0 0  0  7 | 0  0  0   7  | 0 0  0    7  | 0 0  0    7
     */

    int dp[numsSize][numsSize];
    memset(dp, 0, sizeof(dp));

    int i, j;

    for (i = 0; i < numsSize; ++i) {
        dp[i][i] = nums[i];
    }

    for (i = numsSize - 2; i >= 0; --i) {
        for (j = i + 1; j < numsSize; ++j) {
            dp[i][j] = fmax(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]);
        }
    }

    if (dp[0][numsSize - 1] >= 0) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (20)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 5, 2}, 3}, {{1, 5, 233, 7}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,5,2]
     *  Output: false
     *
     *  Input: nums = [1,5,233,7]
     *  Output: true
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = PredictTheWinner(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
