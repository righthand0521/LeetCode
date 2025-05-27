#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int differenceOfSums(int n, int m) {
    int retVal = 0;

    for (int i = 1; i <= n; ++i) {
        if (i % m == 0) {
            retVal -= i;
        } else {
            retVal += i;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int m;
    } testCase[] = {{10, 3}, {5, 6}, {5, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 10, m = 3
     *  Output: 19
     *
     *  Input: n = 5, m = 6
     *  Output: 15
     *
     *  Input: n = 5, m = 1
     *  Output: -15
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, m = %d\n", testCase[i].n, testCase[i].m);

        answer = differenceOfSums(testCase[i].n, testCase[i].m);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
