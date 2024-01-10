#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int knightDialer(int n) {
    int retVal = 0;

    int numericCell = 10;

    struct jumpsType {
        int nextNumber[10];
        int nextNumberSize;
    } jumps[] = {{{4, 6}, 2}, {{6, 8}, 2},    {{7, 9}, 2}, {{4, 8}, 2}, {{3, 9, 0}, 3},
                 {{}, 0},     {{1, 7, 0}, 3}, {{2, 6}, 2}, {{1, 3}, 2}, {{2, 4}, 2}};

    int previousDp[numericCell];
    memset(previousDp, 0, sizeof(previousDp));
    int i;
    for (i = 0; i < numericCell; ++i) {
        previousDp[i] = 1;
    }

    int square, nextSquare, sum;
    int dp[numericCell];
    for (i = 1; i < n; ++i) {
        memset(dp, 0, sizeof(dp));

        for (square = 0; square < numericCell; ++square) {
            sum = 0;
            for (nextSquare = 0; nextSquare < jumps[square].nextNumberSize; ++nextSquare) {
                sum = (sum + previousDp[jumps[square].nextNumber[nextSquare]]) % MODULO;
            }

            dp[square] = sum;
        }

        memcpy(previousDp, dp, sizeof(previousDp));
    }

    for (square = 0; square < numericCell; ++square) {
        retVal = (retVal + previousDp[square]) % MODULO;
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{1}, {2}, {3131}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 1
     *  Output: 10
     *
     *  Input: n = 2
     *  Output: 20
     *
     *  Input: n = 3131
     *  Output: 136006598
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = knightDialer(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
