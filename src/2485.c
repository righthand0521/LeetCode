#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pivotInteger(int n) {
    int retVal = -1;

    /* 1 + 2 + ... + x = x + ... + n
     * => x * (x+1) / 2 = (n-x+1) * (n+x) / 2
     * => 2 * x^2 = n^2 + n
     * => x = ((n^2 + n) / 2)^(1/2)
     * => x = ((n * (n+1) / 2))^(1/2)
     */
    int sum = n * (n + 1) / 2;
    int x = sqrt(sum);
    if (x * x == sum) {
        retVal = x;
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{8}, {1}, {4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 8
     *  Output: 6
     *
     *  Input: n = 1
     *  Output: 1
     *
     *  Input: n = 4
     *  Output: -1
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = pivotInteger(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
