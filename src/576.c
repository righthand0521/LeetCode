#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
    int retVal = 0;

    int dp[m][n];
    memset(dp, 0, sizeof(dp));
    dp[startRow][startColumn] = 1;

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int dpCurrent[m][n];
    int move, row, col, nextRow, nextCol, i;
    for (move = 0; move < maxMove; ++move) {
        memset(dpCurrent, 0, sizeof(dpCurrent));
        for (row = 0; row < m; ++row) {
            for (col = 0; col < n; ++col) {
                if (dp[row][col] <= 0) {
                    continue;
                }

                for (i = 0; i < 4; ++i) {
                    nextRow = row + directions[i][0];
                    nextCol = col + directions[i][1];
                    if (((nextRow >= 0) && (nextRow < m)) && ((nextCol >= 0) && (nextCol < n))) {
                        dpCurrent[nextRow][nextCol] = (dpCurrent[nextRow][nextCol] + dp[row][col]) % MODULO;
                    } else {
                        retVal = (retVal + dp[row][col]) % MODULO;
                    }
                }
            }
        }
        memcpy(dp, dpCurrent, sizeof(dp));
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int m;
        int n;
        int maxMove;
        int startRow;
        int startColumn;
    } testCase[] = {{2, 2, 2, 0, 0}, {1, 3, 3, 0, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
     *  Output: 6
     *
     *  Input: m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
     *  Output: 12
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: m = %d, n = %d, maxMove = %d, startRow = %d, startColumn = %d\n", testCase[i].m, testCase[i].n,
               testCase[i].maxMove, testCase[i].startRow, testCase[i].startColumn);

        answer =
            findPaths(testCase[i].m, testCase[i].n, testCase[i].maxMove, testCase[i].startRow, testCase[i].startColumn);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
