#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long coloredCells(int n) {
    long long retVal = 0;

    /*    1 + (4×1) + (4×2) + ... + (4×(n−1))
     *  = 1 + 4 x (1 + 2 + ... + (n-1))
     *  = 1 + 4 x (n x (n-1) / 2)
     *  = 1 + 2 x n x (n-1)
     */
    retVal = 1 + (long long)(2) * (long long)(n) * (long long)(n - 1);

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{1}, {2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 1
     *  Output: 1
     *
     *  Input: n = 2
     *  Output: 5
     */

    long long answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = coloredCells(testCase[i].n);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
