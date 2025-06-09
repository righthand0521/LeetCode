#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool matches(char* s, char* p, int i, int j) {
    bool retVal = false;

    if (i == 0) {
        retVal = false;
    } else if (p[j - 1] == '.') {
        retVal = true;
    } else {
        retVal = (s[i - 1] == p[j - 1]);
    }

    return retVal;
}
bool isMatch(char* s, char* p) {
    bool retVal = false;

    int sSize = strlen(s);
    int pSize = strlen(p);
    int dp[sSize + 1][pSize + 1];
    memset(dp, false, sizeof(dp));
    dp[0][0] = true;
    for (int i = 0; i <= sSize; ++i) {
        for (int j = 1; j <= pSize; ++j) {
            if (p[j - 1] == '*') {
                dp[i][j] |= dp[i][j - 2];
                if (matches(s, p, i, j - 1) == true) {
                    dp[i][j] |= dp[i - 1][j];
                }
            } else {
                if (matches(s, p, i, j) == true) {
                    dp[i][j] |= dp[i - 1][j - 1];
                }
            }
        }
    }
    retVal = dp[sSize][pSize];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (20)
    struct testCaseType {
        char s[MAX_SIZE];
        char p[MAX_SIZE];
    } testCase[] = {{"aa", "a"}, {"aa", "a*"}, {"ab", ".*"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "aa", p = "a"
     *  Output: false
     *
     *  Input: s = "aa", p = "a*"
     *  Output: true
     *
     *  Input: s = "ab", p = ".*"
     *  Output: true
     */

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", p = \"%s\"\n", testCase[i].s, testCase[i].p);

        answer = isMatch(testCase[i].s, testCase[i].p);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
