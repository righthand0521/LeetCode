#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numTrees(int n) {
    int retVal = 1;

/* Catalan number
 *  f(n) = f(0)f(n-1) + f(1)f(n-2) + f(2)f(n-3) + ... + f(n-1)f(0)
 *  C_n = C (2n, n) / (n+1) = (2n)! / (n! * (n+1)!)
 *  C_n+1 = (2x(2n+1) / (n+2))  x C_n, C_0 = 1.
 *  1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862,
 *  16796, 58786, 208012, 742900, 2674440, 9694845, 35357670, 129644790, 477638700, 1767263190
 *  https://en.wikipedia.org/wiki/Catalan_number
 */
#if 1  // f(n) = f(0)f(n-1) + f(1)f(n-2) + f(2)f(n-3) + ... + f(n-1)f(0)
    if ((n == 0) || (n == 1)) {
        return retVal;
    }

#define MAX_SIZW 20
    int CATALAN[MAX_SIZW] = {0};
    CATALAN[0] = 1;
    CATALAN[1] = 1;
    int i, j;
    for (i = 2; i <= n; ++i) {
        for (j = 0; j < i; ++j) {
            CATALAN[i] += (CATALAN[j] * CATALAN[i - j - 1]);
        }
    }
    retVal = CATALAN[n];
#else  // C_n+1 = (2x(2n+1) / (n+2))  x C_n, C_0 = 1.
    if (n == 0) {
        return retVal;
    }

    long tmp = retVal;
    int idx;
    int i;
    for (i = 1; i <= n; ++i) {
        idx = i - 1;
        tmp = tmp * (2 * (2 * idx + 1)) / (idx + 2);
    }
    retVal = tmp;
#endif

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{3}, {1}, {19}, {2}, {4}, {5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = numTrees(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
