#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isPowerOfTwo(int n) {
    bool retVal = false;

    if (n <= 0) {
        return retVal;
    }

#if (0)
    if ((n & (n - 1)) == 0) {
        retVal = true;
    }
#else
    /* n = 2 ^ x
     * = > log(n) = x * log(2)
     * = > x = log(n) / log(2)
     */
    double x = log10(n) / log10(2);
    if (x - (int)x == 0) {
        retVal = true;
    }
#endif

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{1}, {16}, {3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 1
     *  Output: true
     *
     *  Input: n = 16
     *  Output: true
     *
     *  Input: n = 3
     *  Output: false
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = isPowerOfTwo(testCase[i].n);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
