#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int climbStairs(int n) {
    int retVal = 0;

    /* Climbing Stairs
     *  C[1] = 1; 1
     *  C[2] = 2; 1+1, 2
     *  C[n] = F[n-1] + F[n-2], n>=3.
     */
#define CLIMBSTAIRS_1 (1)
#define CLIMBSTAIRS_2 (2)
#define CLIMBSTAIRS (3)
    int dp[CLIMBSTAIRS] = {0, CLIMBSTAIRS_1, CLIMBSTAIRS_2};

    retVal = dp[n % CLIMBSTAIRS];
    int i;
    for (i = CLIMBSTAIRS; i <= n; ++i) {
        dp[i % CLIMBSTAIRS] = dp[(i - 1) % CLIMBSTAIRS] + dp[(i - 2) % CLIMBSTAIRS];
        retVal = dp[i % CLIMBSTAIRS];
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{2}, {3}, {4}, {5}, {6}, {1}, {45}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 2
     *  Output: 2
     *
     *  Input: n = 3
     *  Output: 3
     *
     *  Input: n = 4
     *  Output: 5
     *
     *  Input: n = 5
     *  Output: 8
     *
     *  Input: n = 6
     *  Output: 13
     *
     *  Input: n = 1
     *  Output: 1
     *
     *  Input: n = 45
     *  Output: 1836311903
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = climbStairs(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
