#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long maxPoints(int** points, int pointsSize, int* pointsColSize) {
    long long retVal = 0;

    int i, j, k;

    int row = pointsSize;
    int col = pointsColSize[0];
    long long dp[row][col];
    memset(dp, 0, sizeof(dp));
    for (i = 0; i < col; ++i) {
        dp[0][i] = points[0][i];
    }

    // https://leetcode.com/problems/maximum-number-of-points-with-cost/solutions/1344888/c-dp-from-o-m-n-n-to-o-m-n/
    //  dp[i][j] = max(dp[i - 1][k] + point[i][j] - abs(j - k)) for each 0 <= k < points[i - 1].size()
    //  => dp[i][j] = max(dp[i - 1][k] + k) + points[i][j] - j for all 0 <= k <= j
    //  => dp[i][j] = max(dp[i - 1][k] - k) + points[i][j] + j for all j <= k <= points[i].size() - 1
    long long dpLeft[col];
    long long dpRight[col];
    for (i = 1; i < row; ++i) {
        memset(dpLeft, 0, sizeof(dpLeft));
        dpLeft[0] = dp[i - 1][0];
        for (int k = 1; k < col; ++k) {
            dpLeft[k] = fmax(dpLeft[k - 1], dp[i - 1][k] + k);
        }

        memset(dpRight, 0, sizeof(dpRight));
        dpRight[col - 1] = dp[i - 1][col - 1] - col + 1;
        for (k = col - 2; k >= 0; --k) {
            dpRight[k] = fmax(dpRight[k + 1], dp[i - 1][k] - k);
        }

        for (j = 0; j < col; ++j) {
            dp[i][j] = fmax(dpLeft[j] - j, dpRight[j] + j) + points[i][j];
        }
    }
    for (j = 0; j < col; ++j) {
        retVal = fmax(retVal, dp[row - 1][j]);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (int)(1e3)
#define MAX_COLUMN (int)(1e3)
    struct testCaseType {
        int points[MAX_ROW][MAX_COLUMN];
        int pointsSize;
        int pointsColSize[MAX_ROW];
    } testCase[] = {{{{1, 2, 3}, {1, 5, 1}, {3, 1, 1}}, 3, {3, 3, 3}}, {{{1, 5}, {2, 3}, {4, 2}}, 3, {2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: points = [[1,2,3],[1,5,1],[3,1,1]]
     *  Output: 9
     *
     *  Input: points = [[1,5],[2,3],[4,2]]
     *  Output: 11
     */

    int** pPoints = NULL;
    long long answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: points = [");
        for (j = 0; j < testCase[i].pointsSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].pointsColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].points[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pPoints = (int**)malloc(testCase[i].pointsSize * sizeof(int*));
        if (pPoints == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].pointsSize; ++j) {
            pPoints[j] = (int*)malloc(testCase[i].pointsColSize[j] * sizeof(int));
            if (pPoints[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pPoints[k]);
                    pPoints[k] = NULL;
                }
                free(pPoints);
                pPoints = NULL;
                return EXIT_FAILURE;
            }
            memset(pPoints[j], 0, testCase[i].pointsColSize[j] * sizeof(int));
            memcpy(pPoints[j], testCase[i].points[j], testCase[i].pointsColSize[j] * sizeof(int));
        }
        answer = maxPoints(pPoints, testCase[i].pointsSize, testCase[i].pointsColSize);
        printf("Output: %lld\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].pointsSize; ++j) {
            free(pPoints[j]);
            pPoints[j] = NULL;
        }
        free(pPoints);
        pPoints = NULL;
    }

    return EXIT_SUCCESS;
}
