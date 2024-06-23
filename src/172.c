#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int trailingZeroes(int n) {
    int retVal = 0;

    while (n >= 5) {
        retVal += (n / 5);
        n /= 5;
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{3}, {5}, {0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3
     *  Output: 0
     *
     *  Input: n = 5
     *  Output: 1
     *
     *  Input: n = 0
     *  Output: 0
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = trailingZeroes(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
