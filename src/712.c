#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumDeleteSum(char* s1, char* s2) {
    int retVal = 0;

    // 1143. Longest Common Subsequence: https://leetcode.com/problems/longest-common-subsequence/
    int s1Size = strlen(s1);
    int s2Size = strlen(s2);
    int idx1, idx2;

    int sum = 0;
    for (idx1 = 0; idx1 < s1Size; ++idx1) {
        sum += s1[idx1];
    }
    for (idx2 = 0; idx2 < s2Size; ++idx2) {
        sum += s2[idx2];
    }

    int dp[s1Size + 1][s2Size + 1];
    memset(dp, 0, sizeof(dp));
    for (idx1 = 1; idx1 <= s1Size; ++idx1) {
        for (idx2 = 1; idx2 <= s2Size; ++idx2) {
            if (s1[idx1 - 1] == s2[idx2 - 1]) {
                dp[idx1][idx2] = dp[idx1 - 1][idx2 - 1] + s1[idx1 - 1];
            } else {
                dp[idx1][idx2] = fmax(dp[idx1 - 1][idx2], dp[idx1][idx2 - 1]);
            }
        }
    }
    retVal = sum - (2 * dp[s1Size][s2Size]);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char s1[MAX_SIZE];
        char s2[MAX_SIZE];
    } testCase[] = {{"sea", "eat"}, {"delete", "leet"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s1 = "sea", s2 = "eat"
     *  Output: 231
     *
     *  Input: s1 = "delete", s2 = "leet"
     *  Output: 403
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s1 = \"%s\", s2 = \"%s\"\n", testCase[i].s1, testCase[i].s2);

        answer = minimumDeleteSum(testCase[i].s1, testCase[i].s2);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
