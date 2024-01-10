#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double knightProbability(int n, int k, int row, int column) {
    double retVal = 0;

    static int directions[8][2] = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}};

    double dp[k + 1][n][n];
    memset(dp, 0, sizeof(dp));
    int nextRow, nextCol;
    int idx;
    int step, i, j;
    for (step = 0; step <= k; step++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (step == 0) {
                    dp[step][i][j] = 1.0;
                    continue;
                }

                for (idx = 0; idx < 8; idx++) {
                    nextRow = i + directions[idx][0];
                    nextCol = j + directions[idx][1];
                    if (((nextRow >= 0) && (nextRow < n)) && ((nextCol >= 0) && (nextCol < n))) {
                        dp[step][i][j] += dp[step - 1][nextRow][nextCol] / 8;
                    }
                }
            }
        }
    }
    retVal = dp[k][row][column];

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int k;
        int row;
        int column;
    } testCase[] = {{3, 2, 0, 0}, {1, 0, 0, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3, k = 2, row = 0, column = 0
     *  Output: 0.06250
     *
     *  Input: n = 1, k = 0, row = 0, column = 0
     *  Output: 1.00000
     */

    int i;
    double answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, k = %d, row = %d, column = %d\n", testCase[i].n, testCase[i].k, testCase[i].row,
               testCase[i].column);

        answer = knightProbability(testCase[i].n, testCase[i].k, testCase[i].row, testCase[i].column);
        printf("Output: %.5f\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
