#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int countVowelPermutation(int n) {
    int retVal = 0;

    int numberOfCharacter = 5;  // Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
    int i;

    long long *dp = (long long *)malloc(numberOfCharacter * sizeof(long long));
    if (dp == NULL) {
        perror("malloc");
        return retVal;
    }
    for (i = 0; i < numberOfCharacter; ++i) {
        dp[i] = 1;
    }

    long long *nextDp = (long long *)malloc(numberOfCharacter * sizeof(long long));
    if (nextDp == NULL) {
        perror("malloc");
        free(dp);
        dp = NULL;
        return retVal;
    }
    for (i = 2; i <= n; ++i) {
        nextDp[0] = (dp[1] + dp[2] + dp[4]) % MODULO;
        nextDp[1] = (dp[0] + dp[2]) % MODULO;
        nextDp[2] = (dp[1] + dp[3]) % MODULO;
        nextDp[3] = dp[2];
        nextDp[4] = (dp[2] + dp[3]) % MODULO;

        memcpy(dp, nextDp, (numberOfCharacter * sizeof(long long)));
    }

    long long answer = 0;
    for (i = 0; i < numberOfCharacter; ++i) {
        answer = (answer + dp[i]) % MODULO;
    }
    retVal = answer;

    free(dp);
    dp = NULL;
    free(nextDp);
    nextDp = NULL;

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{1}, {2}, {5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 1
     *  Output: 5
     *
     *  Input: n = 2
     *  Output: 10
     *
     *  Input: n = 5
     *  Output: 68
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = countVowelPermutation(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
