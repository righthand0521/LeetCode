#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/scramble-string/solutions/203284/chun-cdi-gui-fa-chao-shi-dong-tai-gui-hua-suan-fa-/
bool isScramble(char *s1, char *s2) {
    bool retVal = false;

    int iLenS1 = strlen(s1);
    int iLenS2 = strlen(s2);
    if ((NULL == s1) || (NULL == s2) || (iLenS1 != iLenS2)) {
        return retVal;
    }

    int i, j, l, k;

    //
    bool dp[iLenS1][iLenS2][iLenS1 + 1];
    memset(dp, 0x00, sizeof(bool) * iLenS1 * iLenS2 * (iLenS1 + 1));
    for (i = 0; i < iLenS1; ++i) {
        for (j = 0; j < iLenS2; ++j) {
            if (s1[i] == s2[j]) {
                dp[i][j][1] = true;
            }
        }
    }

    //
    for (l = 2; l <= iLenS1; ++l) {
        for (i = 0; i <= iLenS1 - l; ++i) {
            for (j = 0; j <= iLenS2 - l; ++j) {
                for (k = 1; k < l; ++k) {
                    if ((dp[i][j][k]) && (dp[i + k][j + k][l - k])) {
                        dp[i][j][l] = true;
                        break;
                    }

                    if ((dp[i][j + l - k][k]) && (dp[i + k][j][l - k])) {
                        dp[i][j][l] = true;
                        break;
                    }
                }
            }
        }
    }
    retVal = dp[0][0][iLenS1];

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (30)
    struct testCaseType {
        char s1[MAX_SIZE];
        char s2[MAX_SIZE];
    } testCase[] = {{"great", "rgeat"}, {"abcde", "caebd"}, {"a", "a"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s1 = "great", s2 = "rgeat"
     *  Output: true
     *
     *  Input: s1 = "abcde", s2 = "caebd"
     *  Output: false
     *
     *  Input: s1 = "a", s2 = "a"
     *  Output: true
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s1 = \"%s\", s2 = \"%s\"\n", testCase[i].s1, testCase[i].s2);

        answer = isScramble(testCase[i].s1, testCase[i].s2);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
