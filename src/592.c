#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int dividend, int divisor) {
    int remainder;
    while (divisor != 0) {
        remainder = dividend % divisor;
        dividend = divisor;
        divisor = remainder;
    }

    return dividend;
}
char* fractionAddition(char* expression) {
    char* pRetVal = NULL;

    int expressionSize = strlen(expression);

    int returnSize = expressionSize + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    long long numerator = 0;
    long long x, sign;
    long long denominator = 1;
    long long y;
    int index = 0;
    while (index < expressionSize) {
        sign = 1;
        x = 0;
        if ((expression[index] == '-') || (expression[index] == '+')) {
            sign = expression[index] == '-' ? -1 : 1;
            index++;
        }
        while ((index < expressionSize) && (isdigit(expression[index]))) {
            x = x * 10 + expression[index] - '0';
            index++;
        }
        x = sign * x;
        index++;

        y = 0;
        while ((index < expressionSize) && (isdigit(expression[index]))) {
            y = y * 10 + expression[index] - '0';
            index++;
        }

        numerator = numerator * y + x * denominator;
        denominator *= y;
    }

    char buf[returnSize];
    memset(buf, 0, sizeof(buf));
    long long greatestCommonDivisor;
    if (numerator != 0) {
        greatestCommonDivisor = gcd(abs(numerator), denominator);
        snprintf(buf, sizeof(buf), "%lld/%lld", (numerator / greatestCommonDivisor),
                 (denominator / greatestCommonDivisor));
    } else {
        snprintf(buf, sizeof(buf), "0/1");
    }
    memcpy(pRetVal, buf, returnSize);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char expression[MAX_SIZE];
    } testCase[] = {{"-1/2+1/2"}, {"-1/2+1/2+1/3"}, {"1/3-1/2"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: expression = "-1/2+1/2"
     *  Output: "0/1"
     *
     *  Input: expression = "-1/2+1/2+1/3"
     *  Output: "1/3"
     *
     *  Input: expression = "1/3-1/2"
     *  Output: "-1/6"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: expression = \"%s\"\n", testCase[i].expression);

        pAnswer = fractionAddition(testCase[i].expression);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
