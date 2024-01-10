#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isInterleave(char *s1, char *s2, char *s3) {
    bool retVal = false;

    int s1Size = strlen(s1);
    int s2Size = strlen(s2);
    int s3Size = strlen(s3);
    if (s1Size + s2Size != s3Size) {
        return retVal;
    }

    /* dp[i,j]: s1[0:i] + s2[0:j] = s3[0:(i+j)]
     * dp[i,j] = (dp[i-1,j] and s1[0:i-1] = s3[0:i+j-1]) or (dp[i,j-1] and s2[0:j-1] = s3[0:i+j-1]), dp[0,0] = true.
     */
    bool dp[s1Size + 1][s2Size + 1];
    memset(dp, false, sizeof(dp));
    dp[0][0] = true;
    int s1Idx, s2Idx, s3Idx;
    for (s1Idx = 0; s1Idx <= s1Size; ++s1Idx) {
        for (s2Idx = 0; s2Idx <= s2Size; ++s2Idx) {
            s3Idx = s1Idx + s2Idx - 1;
            if (s1Idx > 0) {
                dp[s1Idx][s2Idx] |= (dp[s1Idx - 1][s2Idx] && s1[s1Idx - 1] == s3[s3Idx]);
            }
            if (s2Idx > 0) {
                dp[s1Idx][s2Idx] |= (dp[s1Idx][s2Idx - 1] && s2[s2Idx - 1] == s3[s3Idx]);
            }
        }
    }
    retVal = dp[s1Size][s2Size];

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE_1 (100 + 4)
#define MAX_SIZE_2 (100 + 4)
#define MAX_SIZE_3 (200 + 4)
    struct testCaseType {
        char s1[MAX_SIZE_1];
        char s2[MAX_SIZE_2];
        char s3[MAX_SIZE_3];
    } testCase[] = {{"aabcc", "dbbca", "aadbbcbcac"}, {"aabcc", "dbbca", "aadbbbaccc"}, {"", "", ""}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
     *  Output: true
     *
     *  Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
     *  Output: false
     *
     *  Input: s1 = "", s2 = "", s3 = ""
     *  Output: true
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s1 = \"%s\", s2 = \"%s\", s3 = \"%s\"\n", testCase[i].s1, testCase[i].s2, testCase[i].s3);

        answer = isInterleave(testCase[i].s1, testCase[i].s2, testCase[i].s3);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
