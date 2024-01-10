#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INDEX_AGES (0)
#define INDEX_SCORES (1)
int compareIntArray(const void* pA, const void* pB) {
    int* a = (int*)pA;
    int* b = (int*)pB;

    // ascending order: ages, scores
    if (a[INDEX_AGES] == b[INDEX_AGES]) {
        return (a[INDEX_SCORES] > b[INDEX_SCORES]);
    } else {
        return (a[INDEX_AGES] > b[INDEX_AGES]);
    }
}
int bestTeamScore(int* scores, int scoresSize, int* ages, int agesSize) {
    int retVal = 0;

    int i, j;

    int player[scoresSize][2];
    for (i = 0; i < scoresSize; ++i) {
        player[i][INDEX_AGES] = ages[i];
        player[i][INDEX_SCORES] = scores[i];
    }
    qsort(player, scoresSize, sizeof(player[0]), compareIntArray);

    int dp[scoresSize];
    for (i = 0; i < scoresSize; ++i) {
        dp[i] = player[i][INDEX_SCORES];
        for (j = 0; j < i; ++j) {
            if (player[j][INDEX_SCORES] <= player[i][INDEX_SCORES]) {
                dp[i] = fmax(dp[i], dp[j] + player[i][INDEX_SCORES]);
            }
        }
        retVal = fmax(retVal, dp[i]);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int scores[MAX_SIZE];
        int scoresSize;
        int ages[MAX_SIZE];
        int agesSize;
    } testCase[] = {{{1, 3, 5, 10, 15}, 5, {1, 2, 3, 4, 5}, 5},
                    {{4, 5, 6, 5}, 4, {2, 1, 2, 1}, 4},
                    {{1, 2, 3, 5}, 4, {8, 9, 10, 1}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: scores = [");
        for (j = 0; j < testCase[i].scoresSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].scores[j]);
        }
        printf("], ages = [");
        for (j = 0; j < testCase[i].agesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].ages[j]);
        }
        printf("]\n");

        answer = bestTeamScore(testCase[i].scores, testCase[i].scoresSize, testCase[i].ages, testCase[i].agesSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
