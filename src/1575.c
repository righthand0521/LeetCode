#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int countRoutes(int* locations, int locationsSize, int start, int finish, int fuel) {
    int retVal = 0;

    int i;

    int dp[locationsSize][fuel + 1];
    memset(dp, 0, sizeof(dp));
    for (i = 0; i <= fuel; i++) {
        dp[finish][i] = 1;
    }

    int src, dst;
    for (i = 0; i <= fuel; ++i) {
        for (src = 0; src < locationsSize; ++src) {
            for (dst = 0; dst < locationsSize; ++dst) {
                if (dst == src) {
                    continue;
                }
                if (abs(locations[src] - locations[dst]) <= i) {
                    dp[src][i] = (dp[src][i] + dp[dst][i - abs(locations[src] - locations[dst])]) % MODULO;
                }
            }
        }
    }

    retVal = dp[start][fuel];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int locations[MAX_SIZE];
        int locationsSize;
        int start;
        int finish;
        int fuel;
    } testCase[] = {{{2, 3, 6, 8, 4}, 5, 1, 3, 5}, {{4, 3, 1}, 3, 1, 0, 6}, {{5, 2, 1}, 3, 0, 2, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: locations = [2,3,6,8,4], start = 1, finish = 3, fuel = 5
     *  Output: 4
     *
     *  Input: locations = [4,3,1], start = 1, finish = 0, fuel = 6
     *  Output: 5
     *
     *  Input: locations = [5,2,1], start = 0, finish = 2, fuel = 3
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: locations = [");
        for (j = 0; j < testCase[i].locationsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].locations[j]);
        }
        printf("], start = %d, finish = %d, fuel = %d\n", testCase[i].start, testCase[i].finish, testCase[i].fuel);

        answer = countRoutes(testCase[i].locations, testCase[i].locationsSize, testCase[i].start, testCase[i].finish,
                             testCase[i].fuel);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
