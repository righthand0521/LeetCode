#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minDistance(char* word1, char* word2) {
    // 72. Edit Distance: https://leetcode.com/problems/edit-distance/
    int retVal = 0;

    int len1 = strlen(word1);
    int len2 = strlen(word2);
    int dp[len1 + 1][len2 + 1];
    memset(dp, 0, sizeof(dp));

    /* Example: Input: word1 = "sea", word2 = "eat"
     *      e a t
     *    0 1 2 3
     *  s 1 2 3 4
     *  e 2 1 2 3
     *  a 3 2 1 2
     */
    int idx1 = 0;
    for (idx1 = 0; idx1 <= len1; ++idx1) {
        dp[idx1][0] = idx1;
    }
    int idx2 = 0;
    for (idx2 = 0; idx2 <= len2; ++idx2) {
        dp[0][idx2] = idx2;
    }
    for (idx1 = 1; idx1 <= len1; ++idx1) {
        for (idx2 = 1; idx2 <= len2; ++idx2) {
            if (word1[idx1 - 1] == word2[idx2 - 1]) {
                dp[idx1][idx2] = dp[idx1 - 1][idx2 - 1];
            } else {
                dp[idx1][idx2] = 1 + fmin(dp[idx1][idx2 - 1], dp[idx1 - 1][idx2]);
            }
        }
    }
    retVal = dp[len1][len2];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        char word1[MAX_SIZE];
        char word2[MAX_SIZE];
    } testCase[] = {{"sea", "eat"}, {"leetcode", "etco"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: word1 = "sea", word2 = "eat"
     *  Output: 2
     *
     *  Input: word1 = "leetcode", word2 = "etco"
     *  Output: 4
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: word1 = \"%s\", word2 = \"%s\"\n", testCase[i].word1, testCase[i].word2);

        answer = minDistance(testCase[i].word1, testCase[i].word2);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
