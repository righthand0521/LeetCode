#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countTriples(int n) {
    int retVal = 0;

    int c;
    for (int a = 1; a <= n; ++a) {
        for (int b = 1; b <= n; ++b) {
            c = (int)sqrt(a * a + b * b + 1.0);
            if ((c <= n) && (c * c == a * a + b * b)) {
                ++retVal;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{5}, {10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 5
     *  Output: 2
     *
     *  Input: n = 10
     *  Output: 4
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = countTriples(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
