#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool checkPowersOfThree(int n) {
    bool retVal = false;

    /* get MAX power of three
     *  n = 3^x
     *  => log(n) = x * log(3)
     *  => x = log(n) / log(3)
     */
    int x = log10(n) / log10(3);

    // check the sum of distinct powers of three
    int powValue;
    int i;
    for (i = x; i >= 0; --i) {
        powValue = pow(3, i);
        if (n >= powValue) {
            n -= powValue;
        }
    }

    if (n == 0) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{12}, {91}, {21}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 12
     *  Output: true
     *
     *  Input: n = 91
     *  Output: true
     *
     *  Input: n = 21
     *  Output: false
     */

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = checkPowersOfThree(testCase[i].n);
        printf("Output: %s\n", answer == true ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
