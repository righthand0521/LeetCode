#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int smallestNumber(int n) {
    int retVal = 0;

    retVal = (1 << (32 - __builtin_clz(n))) - 1;

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{5}, {10}, {3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 5
     *  Output: 7
     *
     *  Input: n = 10
     *  Output: 15
     *
     *  Input: n = 3
     *  Output: 3
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = smallestNumber(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
