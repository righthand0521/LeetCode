#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isPowerOfThree(int n) {
    bool retVal = false;

    if (n <= 0) {
        return retVal;
    }

    if (n % 2 == 0) {
        return retVal;
    }

    /*  n = 3^x
     *  => log(n) = x * log(3)
     *  => x = log(n) / log(3)
     */
    double x = log10(n) / log10(3);
    if (x - (int)x == 0) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{27}, {0}, {-1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 27
     *  Output: true
     *
     *  Input: n = 0
     *  Output: false
     *
     *  Input: n = -1
     *  Output: false
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = isPowerOfThree(testCase[i].n);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
