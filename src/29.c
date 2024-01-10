#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int divide(int dividend, int divisor) {
    int quotient = 0;

    if ((dividend == 0) || (divisor == 0)) {
        return quotient;
    }

    long absDividend = labs(dividend);
    long absDivisor = labs(divisor);
    if (absDividend < absDivisor) {
        return quotient;
    }

    int i;
    for (i = 31; i >= 0; --i) {
        if ((absDivisor << i) > absDividend) {
            continue;
        }
        absDividend -= (absDivisor << i);
        quotient += ((long)1 << i);
    }

    int negative = (((dividend < 0) ^ (divisor < 0)) == 1) ? (-1) : 1;
    if ((quotient == INT_MIN) && (negative == 1)) {
        quotient = INT_MAX;
    } else if ((quotient == INT_MIN) && (negative == -1)) {
        negative = 1;
    }
    quotient = negative * quotient;

    return quotient;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int dividend;
        int divisor;
    } testCase[] = {{10, 3}, {7, -3}, {-1, -1}, {1, 2}, {2, 2}, {INT_MIN, -1}, {INT_MIN, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: dividend = 10, divisor = 3
     *  Output: 3
     *
     *  Input: dividend = 7, divisor = -3
     *  Output: -2
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: dividend = %d, divisor = %d\n", testCase[i].dividend, testCase[i].divisor);

        answer = divide(testCase[i].dividend, testCase[i].divisor);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
