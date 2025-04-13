#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
long long quickmul(int x, long long y) {
    long long retVal = 1;

    long long mul = x;
    while (y > 0) {
        if (y % 2 == 1) {
            retVal = (retVal * mul) % MODULO;
        }
        mul = (mul * mul) % MODULO;
        y /= 2;
    }

    return retVal;
}
int countGoodNumbers(long long n) {
    int retVal = 0;

    retVal = (int)(quickmul(5, (n + 1) / 2) * quickmul(4, n / 2) % MODULO);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        long long n;
    } testCase[] = {{1}, {4}, {50}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 1
     *  Output: 5
     *
     *  Input: n = 4
     *  Output: 400
     *
     *  Input: n = 50
     *  Output: 564908303
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %lld\n", testCase[i].n);

        answer = countGoodNumbers(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
