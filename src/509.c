#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fib(int n) {
    int retVal = n;

    if ((n == 0) || (n == 1)) {
        return retVal;
    }

#define FIBONACCI_0 0
#define FIBONACCI_1 1
    int FIBONACCI[3] = {FIBONACCI_0, FIBONACCI_1, 0};
    int i;
    for (i = 2; i <= n; ++i) {
        FIBONACCI[i % 3] = FIBONACCI[(i - 1) % 3] + FIBONACCI[(i - 2) % 3];
        retVal = FIBONACCI[i % 3];
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{2}, {3}, {4}, {5}, {6}, {0}, {1}, {30}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 2
     *  Output: 1
     *
     *  Input: n = 3
     *  Output: 2
     *
     *  Input: n = 4
     *  Output: 3
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = fib(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
