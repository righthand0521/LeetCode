#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minDeletionSize(char** strs, int strsSize) {
    int retVal = 0;

    int strSize = strlen(strs[0]);
    if (strsSize == 0) {
        return retVal;
    }

    int dp[strSize];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < strSize; ++i) {
        dp[i] = 1;
    }

    bool needUpdate;
    for (int i = strSize - 2; i >= 0; --i) {
        for (int j = i + 1; j < strSize; ++j) {
            needUpdate = true;
            for (int k = 0; k < strsSize; ++k) {
                if (strs[k][i] > strs[k][j]) {
                    needUpdate = false;
                    break;
                }
            }
            if (needUpdate == true) {
                dp[i] = fmax(dp[i], 1 + dp[j]);
            }
        }
    }

    int maxDp = dp[0];
    for (int i = 1; i < strSize; ++i) {
        if (dp[i] > maxDp) {
            maxDp = dp[i];
        }
    }
    retVal = strSize - maxDp;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* strs[MAX_SIZE];
        int strsSize;
    } testCase[] = {{{"babca", "bbazb"}, 2}, {{"edcba"}, 1}, {{"ghi", "def", "abc"}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: strs = ["babca","bbazb"]
     *  Output: 3
     *
     *  Input: strs = ["edcba"]
     *  Output: 4
     *
     *  Input: strs = ["ghi","def","abc"]
     *  Output: 0
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: strs = [");
        for (j = 0; j < testCase[i].strsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].strs[j]);
        }
        printf("]\n");

        answer = minDeletionSize(testCase[i].strs, testCase[i].strsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
