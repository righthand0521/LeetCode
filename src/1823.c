#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findTheWinner(int n, int k) {
    int retVal = 1;

    if (n == 1) {
        return retVal;
    }
    retVal = (k + findTheWinner(n - 1, k) - 1) % n + 1;

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int k;
    } testCase[] = {{5, 2}, {6, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 5, k = 2
     *  Output: 3
     *
     *  Input: n = 6, k = 5
     *  Output: 1
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, k = %d\n", testCase[i].n, testCase[i].k);

        answer = findTheWinner(testCase[i].n, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
