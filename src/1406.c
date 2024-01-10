#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* stoneGameIII(int* stoneValue, int stoneValueSize) {
    char* pRetVal = "Tie";

    int dp[stoneValueSize + 1];
    memset(dp, 0, sizeof(dp));
    int i;
    for (i = stoneValueSize - 1; i >= 0; --i) {
        dp[i] = stoneValue[i] - dp[i + 1];
        if (i + 2 <= stoneValueSize) {
            dp[i] = fmax(dp[i], stoneValue[i] + stoneValue[i + 1] - dp[i + 2]);
        }
        if (i + 3 <= stoneValueSize) {
            dp[i] = fmax(dp[i], stoneValue[i] + stoneValue[i + 1] + stoneValue[i + 2] - dp[i + 3]);
        }
    }

    if (dp[0] > 0) {
        pRetVal = "Alice";
    } else if (dp[0] < 0) {
        pRetVal = "Bob";
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int stoneValue[MAX_SIZE];
        int stoneValueSize;
    } testCase[] = {{{1, 2, 3, 7}, 4}, {{1, 2, 3, -9}, 4}, {{1, 2, 3, 6}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: values = [1,2,3,7]
     *  Output: "Bob"
     *
     *  Input: values = [1,2,3,-9]
     *  Output: "Alice"
     *
     *  Input: values = [1,2,3,6]
     *  Output: "Tie"
     */

    int i, j;
    char* pAnswer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: values = [");
        for (j = 0; j < testCase[i].stoneValueSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].stoneValue[j]);
        }
        printf("]\n");

        pAnswer = stoneGameIII(testCase[i].stoneValue, testCase[i].stoneValueSize);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
