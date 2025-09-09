#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int peopleAwareOfSecret(int n, int delay, int forget) {
    int retVal = 0;

    long dp[forget];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    long share = 0;
    for (int i = 1; i < n; ++i) {
        share = (share + dp[(i - delay + forget) % forget] - dp[i % forget] + MODULO) % MODULO;
        dp[i % forget] = share;
    }

    long long sum = 0;
    for (int i = 0; i < forget; ++i) {
        sum = (sum + dp[i]) % MODULO;
    }
    retVal = sum;

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
        int delay;
        int forget;
    } testCase[] = {{6, 2, 4}, {4, 1, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 6, delay = 2, forget = 4
     *  Output: 5
     *
     *  Input: n = 4, delay = 1, forget = 3
     *  Output: 6
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, delay = %d, forget = %d\n", testCase[i].n, testCase[i].delay, testCase[i].forget);

        answer = peopleAwareOfSecret(testCase[i].n, testCase[i].delay, testCase[i].forget);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
