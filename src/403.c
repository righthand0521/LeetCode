#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool canCross(int* stones, int stonesSize) {
    bool retVal = false;

    bool dp[stonesSize][stonesSize];
    memset(dp, false, sizeof(dp));
    dp[0][0] = true;

    int i, j, k;

    for (i = 1; i < stonesSize; ++i) {
        if (stones[i] - stones[i - 1] > i) {
            return retVal;
        }
    }

    for (i = 1; i < stonesSize; ++i) {
        for (j = i - 1; j >= 0; --j) {
            k = stones[i] - stones[j];
            if (k > j + 1) {
                break;
            }

            dp[i][k] = dp[j][k - 1] || dp[j][k] || dp[j][k + 1];
            if ((i == stonesSize - 1) && (dp[i][k] != 0)) {
                retVal = true;
                return retVal;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2000)
    struct testCaseType {
        int stones[MAX_SIZE];
        int stonesSize;
    } testCase[] = {{{0, 1, 3, 5, 6, 8, 12, 17}, 8}, {{0, 1, 2, 3, 4, 8, 9, 11}, 8}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: stones = [0,1,3,5,6,8,12,17]
     *  Output: true
     *
     *  Input: stones = [0,1,2,3,4,8,9,11]
     *  Output: false
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: stones = [");
        for (j = 0; j < testCase[i].stonesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].stones[j]);
        }
        printf("]\n");

        answer = canCross(testCase[i].stones, testCase[i].stonesSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
