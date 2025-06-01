#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int distributeCandies(int n, int limit) {
    int retVal = 0;

    int minLimit = fmin(limit, n);
    for (int i = 0; i <= minLimit; i++) {
        if ((n - i) > (2 * limit)) {
            continue;
        }
        retVal += (fmin(n - i, limit) - fmax(0, n - i - limit) + 1);
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int limit;
    } testCase[] = {{5, 2}, {3, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 5, limit = 2
     *  Output: 3
     *
     *  Input: n = 3, limit = 3
     *  Output: 10
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, limit = %d\n", testCase[i].n, testCase[i].limit);

        answer = distributeCandies(testCase[i].n, testCase[i].limit);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
