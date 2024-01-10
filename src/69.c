#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mySqrt(int x) {
    int retVal = 0;

    // Integer square root: Newton's method to find a solution for the equation x^2 - n = 0
    long long root = x;
    while (root * root > x) {
        root = (root + x / root) / 2;
    }
    retVal = (int)root;

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int x;
    } testCase[] = {{4}, {8}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: x = 4
     *  Output: 2
     *
     *  Input: x = 8
     *  Output: 2
     */

    int pAnswer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: x = %d\n", testCase[i].x);

        pAnswer = mySqrt(testCase[i].x);
        printf("Output: %d\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
