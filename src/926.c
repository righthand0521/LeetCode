#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minFlipsMonoIncr(char* s) {
    int retVal = 0;

    int num = 0;
    int len = strlen(s);
    int i;
    for (i = 0; i < len; ++i) {
        /* Let number num be the number of character 1s in s' prefix of length i:
         *  dp[i] = dp[i - 1] if s[i - 1] = '1'
         *  dp[i] = min(num, dp[i - 1] + 1) otherwise.
         */
        if (s[i] == '0') {
            retVal = fmin((retVal + 1), num);
        } else {
            ++num;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"00110"}, {"010110"}, {"00011000"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = minFlipsMonoIncr(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
