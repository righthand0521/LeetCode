#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numDecodings(char* s) {
    int retVal = 0;

    int sSize = strlen(s);

    /* dp(i): s[1:i]
     *  dp(i) = dp(i-1), s[i-1] != 0
     *  dp(i) = dp(i-2), s[i-2] != 0, 10*s[i-2] + s[i-1] <= 26.
     *  dp(0) = 1
     *
     *  f1 = dp[i-2], f2 = dp[i-1], f3 = dp[i]
     */
    int f1 = 0;
    int f2 = 1;
    int f3 = 0;
    int i;
    for (i = 1; i <= sSize; ++i) {
        f3 = 0;
        if (s[i - 1] != '0') {
            f3 += f2;
        }
        if ((i > 1) && (s[i - 2] != '0') && (10 * (s[i - 2] - '0') + (s[i - 1] - '0') <= 26)) {
            f3 += f1;
        }
        f1 = f2;
        f2 = f3;
    }
    retVal = f3;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"12"}, {"226"}, {"06"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "12"
     *  Output: 2
     *
     *  Input: s = "226"
     *  Output: 3
     *
     *  Input: s = "06"
     *  Output: 0
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = numDecodings(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
