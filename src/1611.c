#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumOneBitOperations(int n) {
    int retVal = 0;

    int k = 0;
    int mask = 1;
    while (mask <= n) {
        if ((n & mask) != 0) {
            retVal = (1 << (k + 1)) - 1 - retVal;
        }
        mask <<= 1;
        k++;
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{3}, {6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3
     *  Output: 2
     *
     *  Input: n = 6
     *  Output: 4
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = minimumOneBitOperations(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
