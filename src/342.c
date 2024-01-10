#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isPowerOfFour(int n) {
    bool retVal = false;

    if (n <= 0) {
        return retVal;
    }

#if (0)
    if ((n & (n - 1)) != 0) {
        return retVal;
    }

    if ((n & 0x55555555) != 0) {
        retVal = true;
    }
#else
    /* n = 4 ^ x
     * = > log(n) = x * log(4)
     * = > x = log(n) / log(4)
     */
    double x = log10(n) / log10(4);
    if (x - (int)x == 0) {
        retVal = true;
    }
#endif

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{16}, {5}, {1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 16
     *  Output: true
     *
     *  Input: n = 5
     *  Output: false
     *
     *  Input: n = 1
     *  Output: true
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = isPowerOfFour(testCase[i].n);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
