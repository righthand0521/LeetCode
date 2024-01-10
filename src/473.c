#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool makesquare(int* matchsticks, int matchsticksSize) {
    bool retVal = false;

    int i;

    int sumOfMatchsticks = 0;
    for (i = 0; i < matchsticksSize; ++i) {
        sumOfMatchsticks += matchsticks[i];
    }
    if (sumOfMatchsticks % 4 != 0) {
        return retVal;
    }
    int squareSide = sumOfMatchsticks / 4;

    int dpSize = (1 << matchsticksSize);
    int dp[dpSize];
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    int key, value;
    int j;
    for (i = 1; i < dpSize; ++i) {
        for (key = 0; key < matchsticksSize; ++key) {
            value = matchsticks[key];
            if ((i & (1 << key)) == 0) {
                continue;
            }
            j = i & ~(1 << key);

            if ((dp[j] >= 0) && (dp[j] + value <= squareSide)) {
                dp[i] = (dp[j] + value) % squareSide;
                break;
            }
        }
    }
    retVal = (dp[dpSize - 1] == 0);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (15)
    struct testCaseType {
        int matchsticks[MAX_SIZE];
        int matchsticksSize;
    } testCase[] = {{{1, 1, 2, 2, 2}, 5}, {{3, 3, 3, 3, 4}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: matchsticks = [1,1,2,2,2]
     *  Output: true
     *
     *  Input: matchsticks = [3,3,3,3,4]
     *  Output: false
     */

    int i, j;
    bool answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: matchsticks = [");
        for (j = 0; j < testCase[i].matchsticksSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].matchsticks[j]);
        }
        printf("]\n");

        answer = makesquare(testCase[i].matchsticks, testCase[i].matchsticksSize);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
