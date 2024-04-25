#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LETTERS (26)  // s consists of lowercase English letters.
int longestIdealString(char* s, int k) {
    int retVal = 0;

    int sSize = strlen(s);

    int dp[LETTERS];
    memset(dp, 0, sizeof(dp));

    int current, best;
    int i, j;
    for (i = 0; i < sSize; ++i) {
        current = s[i] - 'a';
        best = 0;
        for (j = 0; j < LETTERS; ++j) {
            if (abs(j - current) <= k) {
                best = fmax(best, dp[j]);
            }
        }

        dp[current] = fmax(dp[current], best + 1);
        retVal = fmax(retVal, dp[current]);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
        int k;
    } testCase[] = {{"acfgbd", 2}, {"abcd", 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "acfgbd", k = 2
     *  Output: 4
     *
     *  Input: s = "abcd", k = 3
     *  Output: 4
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", k=%d\n", testCase[i].s, testCase[i].k);

        answer = longestIdealString(testCase[i].s, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
