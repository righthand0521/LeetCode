#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REVERSE (1)
#define MATH (1)
int alternateDigitSum(int n) {
    int retVal = 0;

#if (REVERSE)
    printf("REVERSE\n");

    int reverse = 0;
    while (n > 0) {
        reverse = reverse * 10 + (n % 10);
        n /= 10;
    }

    int round = 0;
    while (reverse > 0) {
        if (round % 2 == 0) {
            retVal += (reverse % 10);
        } else {
            retVal -= (reverse % 10);
        }
        ++round;
        reverse /= 10;
    }
#elif (MATH)
    printf("MATH\n");

    /* Alternating Digit Sum
     *  n has odd digit: n = abcde, a - b + c - d + e = (e - d + c - b + a) * (1)
     *  n has even digit: n = abcd, a - b + c - d = (d - c + b - a) * (-1)
     */
    int sign = -1;
    while (n > 0) {
        sign *= (-1);
        retVal += (sign * (n % 10));
        n /= 10;
    }
    retVal *= sign;
#endif

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{521}, {111}, {886996}, {10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = alternateDigitSum(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
