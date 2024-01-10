#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/stone-game-ii/solutions/284065/java-dong-tai-gui-hua-qing-xi-yi-dong-17xing-by-lg/
int stoneGameII(int* piles, int pilesSize) {
    int retVal = 0;

    int dp[pilesSize][pilesSize + 1];
    memset(dp, 0, sizeof(dp));
    int sum = 0;
    for (int i = pilesSize - 1; i >= 0; --i) {
        sum += piles[i];
        for (int M = 1; M <= pilesSize; ++M) {
            if (i + 2 * M >= pilesSize) {
                dp[i][M] = sum;
            } else {
                for (int x = 1; x <= 2 * M; ++x) {
                    int j = fmax(M, x);
                    dp[i][M] = fmax(dp[i][M], sum - dp[i + x][j]);
                }
            }
        }
    }
    retVal = dp[0][1];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int piles[MAX_SIZE];
        int pilesSize;
    } testCase[] = {{{2, 7, 9, 4, 4}, 5}, {{1, 2, 3, 4, 5, 100}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: piles = [2,7,9,4,4]
     *  Output: 10
     *
     *  Input: piles = [1,2,3,4,5,100]
     *  Output: 104
     */

    int i, j;
    int answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: piles = [");
        for (j = 0; j < testCase[i].pilesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].piles[j]);
        }
        printf("]\n");

        answer = stoneGameII(testCase[i].piles, testCase[i].pilesSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
