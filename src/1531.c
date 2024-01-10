#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calc(int x) {
    int retVal = 4;

    if (x == 1) {
        retVal = 1;
    } else if (x < 10) {
        retVal = 2;
    } else if (x < 100) {
        retVal = 3;
    }

    return retVal;
}
int getLengthOfOptimalCompression(char *s, int k) {
    int retVal = 0;

    int sSize = strlen(s);

    int dp[sSize + 1][k + 1];
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    int same, diff;
    int x, y, z;
    for (x = 1; x <= sSize; ++x) {
        for (y = 0; y <= k && y <= x; ++y) {
            if (y > 0) {
                dp[x][y] = dp[x - 1][y - 1];
            }

            same = 0;
            diff = 0;
            for (z = x; (z >= 1 && diff <= y); --z) {
                if (s[z - 1] == s[x - 1]) {
                    ++same;
                    dp[x][y] = fmin(dp[x][y], dp[z - 1][y - diff] + calc(same));
                } else {
                    ++diff;
                }
            }
        }
    }
    retVal = dp[sSize][k];

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
        int k;
    } testCase[] = {{"aaabcccd", 2}, {"aabbaa", 2}, {"aaaaaaaaaaa", 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "aaabcccd", k = 2
     *  Output: 4
     *
     *  Input: s = "aabbaa", k = 2
     *  Output: 2
     *
     *  Input: s = "aaaaaaaaaaa", k = 0
     *  Output: 3
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", k = %d\n", testCase[i].s, testCase[i].k);

        answer = getLengthOfOptimalCompression(testCase[i].s, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
