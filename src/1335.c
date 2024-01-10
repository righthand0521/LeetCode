#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minDifficulty(int* jobDifficulty, int jobDifficultySize, int d) {
    int retVal = -1;

    if (jobDifficultySize < d) {
        return retVal;
    }

    int i, j;

    int maxDifficulty = 0;
    int dp[jobDifficultySize];
    for (i = 0; i < jobDifficultySize; ++i) {
        maxDifficulty = fmax(maxDifficulty, jobDifficulty[i]);
        dp[i] = maxDifficulty;
    }

    int minDifficulty;
    int monotonicStack[jobDifficultySize][2];
    int monotonicStackTop;
    int dpNext[jobDifficultySize];
    for (i = 1; i < d; ++i) {
        memset(dpNext, 0, sizeof(dpNext));
        memset(monotonicStack, 0, sizeof(monotonicStack));
        monotonicStackTop = 0;

        for (j = i; j < jobDifficultySize; ++j) {
            minDifficulty = dp[j - 1];
            while ((monotonicStackTop > 0) &&
                   (jobDifficulty[monotonicStack[monotonicStackTop - 1][0]] < jobDifficulty[j])) {
                minDifficulty = fmin(minDifficulty, monotonicStack[monotonicStackTop - 1][1]);
                --monotonicStackTop;
            }

            if (monotonicStackTop == 0) {
                dpNext[j] = minDifficulty + jobDifficulty[j];
            } else {
                dpNext[j] = fmin(dpNext[monotonicStack[monotonicStackTop - 1][0]], minDifficulty + jobDifficulty[j]);
            }
            monotonicStack[monotonicStackTop][0] = j;
            monotonicStack[monotonicStackTop][1] = minDifficulty;
            ++monotonicStackTop;
        }
        memcpy(dp, dpNext, sizeof(dp));
    }
    retVal = dp[jobDifficultySize - 1];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (300)
    struct testCaseType {
        int jobDifficulty[MAX_SIZE];
        int jobDifficultySize;
        int d;
    } testCase[] = {{{6, 5, 4, 3, 2, 1}, 6, 2}, {{9, 9, 9}, 3, 4}, {{1, 1, 1}, 3, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: jobDifficulty = [6,5,4,3,2,1], d = 2
     *  Output: 7
     *
     *  Input: jobDifficulty = [9,9,9], d = 4
     *  Output: -1
     *
     *  Input: jobDifficulty = [1,1,1], d = 3
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: jobDifficulty = [");
        for (j = 0; j < testCase[i].jobDifficultySize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].jobDifficulty[j]);
        }
        printf("], d = %d\n", testCase[i].d);

        answer = minDifficulty(testCase[i].jobDifficulty, testCase[i].jobDifficultySize, testCase[i].d);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
