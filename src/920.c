#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int numMusicPlaylists(int n, int goal, int k) {
    int retVal = 0;

    // the number of possible playlists of length goal containing exactly n unique songs
    long dp[goal + 1][n + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    int uniqueSongs;
    int i, j;
    for (i = 1; i < (goal + 1); ++i) {
        uniqueSongs = (i < n) ? i : n;
        for (j = 1; j < (uniqueSongs + 1); ++j) {
            // The i-th song is a new song
            dp[i][j] = dp[i - 1][j - 1] * (n - j + 1) % MODULO;
            // The i-th song is a song we have played before
            if (j > k) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j] * (j - k)) % MODULO;
            }
        }
    }

    retVal = dp[goal][n];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int n;
        int goal;
        int k;
    } testCase[] = {{3, 3, 1}, {2, 3, 0}, {2, 3, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3, goal = 3, k = 1
     *  Output: 6
     *
     *  Input: n = 2, goal = 3, k = 0
     *  Output: 6
     *
     *  Input: n = 2, goal = 3, k = 1
     *  Output: 2
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, goal = %d, k = %d\n", testCase[i].n, testCase[i].goal, testCase[i].k);

        answer = numMusicPlaylists(testCase[i].n, testCase[i].goal, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
