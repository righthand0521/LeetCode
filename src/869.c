#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long counter(int n) {
    long retVal = 0;

    for (; n; n /= 10) {
        retVal += pow(10, n % 10);
    }

    return retVal;
}
bool reorderedPowerOf2(int n) {
    bool retVal = false;

    long c = counter(n);
    for (int i = 0; i < 31; i++) {
        if (counter(1 << i) == c) {
            retVal = true;
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{1}, {10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 1
     *  Output: true
     *
     *  Input: n = 10
     *  Output: false
     */

    bool answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = reorderedPowerOf2(testCase[i].n);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
