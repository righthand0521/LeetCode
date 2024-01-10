#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minFlips(int a, int b, int c) {
    int retVal = 0;

    while ((a > 0) || (b > 0) || (c > 0)) {
        if (c & 1) {
            retVal += ((~((a & 1) | (b & 1))) & 1);
        } else {
            retVal += ((a & 1) + (b & 1));
        }

        a >>= 1;
        b >>= 1;
        c >>= 1;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int a;
        int b;
        int c;
    } testCase[] = {{2, 6, 5}, {4, 2, 7}, {1, 2, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: a = 2, b = 6, c = 5
     *  Output: 3
     *
     *  Input: a = 4, b = 2, c = 7
     *  Output: 1
     *
     *  Input: a = 1, b = 2, c = 3
     *  Output: 0
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: a = %d, b = %d, c = %d\n", testCase[i].a, testCase[i].b, testCase[i].c);

        answer = minFlips(testCase[i].a, testCase[i].b, testCase[i].c);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
