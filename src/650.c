#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minSteps(int n) {
    int retVal = 0;

    int i = 2;
    while (i * i <= n) {
        while (n % i == 0) {
            n /= i;
            retVal += i;
        }
        i += 1;
    }

    if (n > 1) {
        retVal += n;
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{3}, {1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3
     *  Output: 3
     *
     *  Input: n = 1
     *  Output: 0
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = minSteps(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
