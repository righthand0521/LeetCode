#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int integerBreak(int n) {
    int retVal = 1;

    if (n <= 3) {
        retVal = n - 1;
        return retVal;
    }

    int dp[n + 1];
    memset(dp, 0, sizeof(dp));

    int maximizeProduct, product1, product2;
    int i, j;
    for (i = 2; i <= n; ++i) {
        maximizeProduct = 0;
        for (j = 1; j < i; ++j) {
            product1 = j * (i - j);
            product2 = j * dp[i - j];
            maximizeProduct = fmax(maximizeProduct, fmax(product1, product2));
        }
        dp[i] = maximizeProduct;
    }
    retVal = dp[n];

#if (0)  // Mathematics
    int quotient = n / 3;
    int remainder = n % 3;
    if (remainder == 0) {
        retVal = pow(3, quotient);
    } else if (remainder == 1) {
        retVal = pow(3, (quotient - 1)) * 4;
    } else {
        retVal = pow(3, quotient) * 2;
    }
#endif

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{2}, {10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 2
     *  Output: 1
     *
     *  Input: n = 10
     *  Output: 36
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = integerBreak(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
