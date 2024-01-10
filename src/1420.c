#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int numOfArrays(int n, int m, int k) {
    int retVal = 0;

    long long dp[m + 1][k + 1];
    memset(dp, 0, sizeof(dp));
    long long prefix[m + 1][k + 1];
    memset(prefix, 0, sizeof(prefix));
    long long prevDp[m + 1][k + 1];
    memset(prevDp, 0, sizeof(prevDp));
    long long prevPrefix[m + 1][k + 1];
    memset(prevPrefix, 0, sizeof(prevPrefix));

    int i;
    for (i = 1; i <= m; i++) {
        dp[i][1] = 1;
    }
    long long answer;
    int maxNum, cost;
    for (i = 1; i <= n; i++) {
        if (i > 1) {
            memset(dp, 0, sizeof(dp));
        }

        memset(prefix, 0, sizeof(prefix));
        for (maxNum = 1; maxNum <= m; maxNum++) {
            for (cost = 1; cost <= k; cost++) {
                answer = (maxNum * prevDp[maxNum][cost]) % MODULO;
                answer = (answer + prevPrefix[maxNum - 1][cost - 1]) % MODULO;

                dp[maxNum][cost] += answer;
                dp[maxNum][cost] %= MODULO;

                prefix[maxNum][cost] = (prefix[maxNum - 1][cost] + dp[maxNum][cost]);
                prefix[maxNum][cost] %= MODULO;
            }
        }

        for (maxNum = 0; maxNum <= m; maxNum++) {
            for (cost = 0; cost <= k; cost++) {
                prevDp[maxNum][cost] = dp[maxNum][cost];
                prevPrefix[maxNum][cost] = prefix[maxNum][cost];
            }
        }
    }
    retVal = prefix[m][k];

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int m;
        int k;
    } testCase[] = {{2, 3, 1}, {5, 2, 3}, {9, 1, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 2, m = 3, k = 1
     *  Output: 6
     *
     *  Input: n = 5, m = 2, k = 3
     *  Output: 0
     *
     *  Input: n = 9, m = 1, k = 1
     *  Output: 1
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, m = %d, k = %d\n", testCase[i].n, testCase[i].m, testCase[i].k);

        answer = numOfArrays(testCase[i].n, testCase[i].m, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
