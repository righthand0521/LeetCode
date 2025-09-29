#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minScoreTriangulation(int* values, int valuesSize) {
    int retVal = 0;

    int dp[valuesSize][valuesSize];
    memset(dp, 0, sizeof(dp));
    for (int d = 2; d < valuesSize; ++d) {
        for (int i = 0; i < valuesSize - d; ++i) {
            int j = i + d;
            dp[i][j] = INT_MAX;
            for (int k = i + 1; k < j; ++k) {
                dp[i][j] = fmin(dp[i][j], dp[i][k] + dp[k][j] + values[i] * values[j] * values[k]);
            }
        }
    }
    retVal = dp[0][valuesSize - 1];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50)
    struct testCaseType {
        int values[MAX_SIZE];
        int valuesSize;
    } testCase[] = {{{1, 2, 3}, 3}, {{3, 7, 4, 5}, 4}, {{1, 3, 1, 4, 1, 5}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: values = [1,2,3]
     *  Output: 6
     *
     *  Input: values = [3,7,4,5]
     *  Output: 144
     *
     *  Input: values = [1,3,1,4,1,5]
     *  Output: 13
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: values = [");
        for (j = 0; j < testCase[i].valuesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].values[j]);
        }
        printf("]\n");

        answer = minScoreTriangulation(testCase[i].values, testCase[i].valuesSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
