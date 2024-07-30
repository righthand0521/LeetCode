#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumDeletions(char *s) {
    int retVal = 0;

    /* 926. Flip String to Monotone Increasing
     *  https://leetcode.com/problems/flip-string-to-monotone-increasing/
     */
    int num = 0;
    int sSize = strlen(s);
    int i;
    for (i = 0; i < sSize; ++i) {
        /* Let num be the number of character 'b' in s' prefix of length i:
         *  dp[i] = dp[i - 1] if s[i - 1] = 'b'
         *  dp[i] = min(num, dp[i - 1] + 1) otherwise.
         */
        if (s[i] == 'a') {
            retVal = fmin((retVal + 1), num);
        } else {
            ++num;
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"aababbab"}, {"bbaaaaabb"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "aababbab"
     *  Output: 2
     *
     *  Input: s = "bbaaaaabb"
     *  Output: 2
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = minimumDeletions(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
