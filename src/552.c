#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int checkRecord(int n) {
    int retVal = 0;

    int dp[n + 1][2][3];
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;  // Base case: there is 1 string of length 0 with zero 'A' and zero 'L'.

    // Iterate on smaller sub-problems and use the current smaller sub-problem
    // to generate results for bigger sub-problems.
    int len, totalAbsences, consecutiveLates;
    for (len = 0; len < n; ++len) {
        for (totalAbsences = 0; totalAbsences <= 1; ++totalAbsences) {
            for (consecutiveLates = 0; consecutiveLates <= 2; ++consecutiveLates) {
                // Store the count when 'P' is chosen.
                dp[len + 1][totalAbsences][0] =
                    (dp[len + 1][totalAbsences][0] + dp[len][totalAbsences][consecutiveLates]) % MODULO;

                // Store the count when 'A' is chosen.
                if (totalAbsences < 1) {
                    dp[len + 1][totalAbsences + 1][0] =
                        (dp[len + 1][totalAbsences + 1][0] + dp[len][totalAbsences][consecutiveLates]) % MODULO;
                }

                // Store the count when 'L' is chosen.
                if (consecutiveLates < 2) {
                    dp[len + 1][totalAbsences][consecutiveLates + 1] =
                        (dp[len + 1][totalAbsences][consecutiveLates + 1] + dp[len][totalAbsences][consecutiveLates]) %
                        MODULO;
                }
            }
        }
    }

    // Sum up the counts for all combinations of length 'n' with different absent and late counts.
    for (totalAbsences = 0; totalAbsences <= 1; ++totalAbsences) {
        for (consecutiveLates = 0; consecutiveLates <= 2; ++consecutiveLates) {
            retVal = (retVal + dp[n][totalAbsences][consecutiveLates]) % MODULO;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{2}, {1}, {10101}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 2
     *  Output: 8
     *
     *  Input: n = 1
     *  Output: 3
     *
     *  Input: n = 10101
     *  Output: 183236316
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = checkRecord(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
