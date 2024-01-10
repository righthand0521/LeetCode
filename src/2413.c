#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int smallestEvenMultiple(int n) {
    int retVal = 0;

#if (1)
    retVal = n << (n & 1);
#else
    retVal = n;
    if (n % 2 == 1) {
        retVal = n * 2;
    }
#endif

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{5}, {6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 5
     *  Output: 10
     *
     *  Input: n = 6
     *  Output: 6
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n  = %d\n", testCase[i].n);

        answer = smallestEvenMultiple(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
