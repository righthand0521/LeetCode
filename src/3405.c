#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
#define MAX_NUMBER (int)(1e5)  // 1 <= n <= 10^5, 1 <= m <= 10^5
long long factory[MAX_NUMBER];
long long incertFactory[MAX_NUMBER];
long long qpower(long long x, int n) {
    long long retVal = 1;

    while (n) {
        if (n & 1) {
            retVal = retVal * x % MODULO;
        }
        x = x * x % MODULO;
        n >>= 1;
    }

    return retVal;
}
long long combine(int n, int m) {
    long long retVal = factory[n] * incertFactory[m] % MODULO * incertFactory[n - m] % MODULO;

    return retVal;
}
int countGoodArrays(int n, int m, int k) {
    int retVal = 0;

    if (factory[0] == 0) {
        factory[0] = 1;
        for (int i = 1; i < MAX_NUMBER; i++) {
            factory[i] = factory[i - 1] * i % MODULO;
        }

        incertFactory[MAX_NUMBER - 1] = qpower(factory[MAX_NUMBER - 1], MODULO - 2);
        for (int i = MAX_NUMBER - 1; i > 0; i--) {
            incertFactory[i - 1] = incertFactory[i] * i % MODULO;
        }
    }
    retVal = combine(n - 1, k) * m % MODULO * qpower(m - 1, n - k - 1) % MODULO;

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int m;
        int k;
    } testCase[] = {{3, 2, 1}, {4, 2, 2}, {5, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3, m = 2, k = 1
     *  Output: 4
     *
     *  Input: n = 4, m = 2, k = 2
     *  Output: 6
     *
     *  Input: n = 5, m = 2, k = 0
     *  Output: 2
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, m = %d, k = %d\n", testCase[i].n, testCase[i].m, testCase[i].k);

        answer = countGoodArrays(testCase[i].n, testCase[i].m, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
