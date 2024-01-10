#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestCommonSubsequence(char* text1, char* text2) {
    int retVal = 0;

    // 712. Minimum ASCII Delete Sum for Two Strings:
    // https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/
    int s1Size = strlen(text1);
    int s2Size = strlen(text2);
    int dp[s1Size + 1][s2Size + 1];
    memset(dp, 0, sizeof(dp));

    // https://pic.leetcode-cn.com/1617411822-KhEKGw-image.png
    int idx1, idx2;
    for (idx1 = 1; idx1 <= s1Size; ++idx1) {
        for (idx2 = 1; idx2 <= s2Size; ++idx2) {
            if (text1[idx1 - 1] == text2[idx2 - 1]) {
                dp[idx1][idx2] = dp[idx1 - 1][idx2 - 1] + 1;
            } else {
                dp[idx1][idx2] = fmax(dp[idx1 - 1][idx2], dp[idx1][idx2 - 1]);
            }
        }
    }
    retVal = dp[s1Size][s2Size];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char text1[MAX_SIZE];
        char text2[MAX_SIZE];
    } testCase[] = {{"abcde", "ace"}, {"abc", "abc"}, {"abc", "def"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: text1 = "abcde", text2 = "ace"
     *  Output: 3
     *
     *  Input: text1 = "abc", text2 = "abc"
     *  Output: 3
     *
     *  Input: text1 = "abc", text2 = "def"
     *  Output: 0
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: text1 = \"%s\", text2=\"%s\"\n", testCase[i].text1, testCase[i].text2);

        answer = longestCommonSubsequence(testCase[i].text1, testCase[i].text2);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
