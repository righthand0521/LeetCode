#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int numOfWays(int n) {
    int retVal = 0;

    long long fi0New, fi1New;
    long long fi0 = 6;
    long long fi1 = 6;
    for (int i = 2; i <= n; ++i) {
        fi0New = (2 * fi0 + 2 * fi1) % MODULO;
        fi1New = (2 * fi0 + 3 * fi1) % MODULO;
        fi0 = fi0New;
        fi1 = fi1New;
    }
    retVal = (fi0 + fi1) % MODULO;

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{1}, {5000}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 1
     *  Output: 12
     *
     *  Input: n = 5000
     *  Output: 30228214
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = numOfWays(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
