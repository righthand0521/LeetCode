#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findMaxForm(char** strs, int strsSize, int m, int n) {
    int retVal = 0;

    int bitsCount[strsSize][2];
    memset(bitsCount, 0, sizeof(bitsCount));
    int len;
    for (int i = 0; i < strsSize; ++i) {
        len = strlen(strs[i]);
        for (int j = 0; j < len; ++j) {
            ++bitsCount[i][(int)(strs[i][j] - '0')];
        }
    }

    int dp[m + 1][n + 1];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < strsSize; ++i) {
        for (int j = m; j >= bitsCount[i][0]; --j) {
            for (int k = n; k >= bitsCount[i][1]; --k) {
                dp[j][k] = fmax(dp[j][k], (dp[j - bitsCount[i][0]][k - bitsCount[i][1]] + 1));
            }
        }
    }
    retVal = dp[m][n];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (600)
    struct testCaseType {
        char* strs[MAX_SIZE];
        int strsSize;
        int m;
        int n;
    } testCase[] = {{{"10", "0001", "111001", "1", "0"}, 5, 5, 3}, {{"10", "0", "1"}, 3, 1, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
     *  Output: 4
     *
     *  Input: strs = ["10","0","1"], m = 1, n = 1
     *  Output: 2
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: strs = [");
        for (j = 0; j < testCase[i].strsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].strs[j]);
        }
        printf("], m = %d, n = %d\n", testCase[i].m, testCase[i].n);

        answer = findMaxForm(testCase[i].strs, testCase[i].strsSize, testCase[i].m, testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
