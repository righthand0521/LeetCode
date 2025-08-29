#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long flowerGame(int n, int m) {
    long long retVal = (long long)m * n / 2;

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int m;
    } testCase[] = {{3, 2}, {1, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3, m = 2
     *  Output: 3
     *
     *  Input: n = 1, m = 1
     *  Output: 0
     */

    long long answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, m = %d\n", testCase[i].n, testCase[i].m);

        answer = flowerGame(testCase[i].n, testCase[i].m);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
