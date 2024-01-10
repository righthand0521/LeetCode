#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numberOfMatches(int n) {
    int retVal = 0;

    int next;
    while (n > 1) {
        next = n >> 1;
        n -= next;
        retVal += next;
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{7}, {14}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 7
     *  Output: 6
     *
     *  Input: n = 14
     *  Output: 13
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = numberOfMatches(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
