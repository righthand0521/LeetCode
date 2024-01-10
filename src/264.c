#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DYNAMIC_PROGRAMMING (1)  // Assume you have kth ugly number. Then (k+1)th must be Min(L1*2, L2*3, L3*5).
#define DEFINTION (1)            // Time Limit Exceeded
#if (DYNAMIC_PROGRAMMING)
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#elif (DEFINTION)
bool isUgly(int n) {
    bool retVal = false;

    if (n <= 0) {
        return retVal;
    }

    int factors[] = {2, 3, 5};
    int factorsSize = sizeof(factors) / sizeof(factors[0]);

    int i;
    for (i = 0; i < factorsSize; ++i) {
        while (n % factors[i] == 0) {
            n /= factors[i];
        }
    }

    if (n == 1) {
        retVal = true;
    }

    return retVal;
}
#endif
int nthUglyNumber(int n) {
    int retVal = 1;

    if (n == 1) {
        return retVal;
    }

#if (DYNAMIC_PROGRAMMING)
    unsigned int UglyNumberList[n];
    unsigned int next = 1;
    unsigned int idx2 = 0;
    unsigned int next2 = 2;
    unsigned int idx3 = 0;
    unsigned int next3 = 3;
    unsigned int idx5 = 0;
    unsigned int next5 = 5;

    UglyNumberList[0] = next;
    int i;
    for (i = 1; i < n; ++i) {
        next = MIN(next2, MIN(next3, next5));
        UglyNumberList[i] = next;

        if (next == next2) {
            ++idx2;
            next2 = UglyNumberList[idx2] * 2;
        }
        if (next == next3) {
            ++idx3;
            next3 = UglyNumberList[idx3] * 3;
        }
        if (next == next5) {
            ++idx5;
            next5 = UglyNumberList[idx5] * 5;
        }
    }
    retVal = UglyNumberList[n - 1];
#elif (DEFINTION)
    int count = 1;
    while (count < n) {
        ++retVal;
        if (isUgly(retVal) == true) {
            ++count;
        }
    }
#endif

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{10}, {1}, {1690}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = true;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
#if (DYNAMIC_PROGRAMMING)
#elif (DEFINTION)
        if (testCase[i].n > 20) {
            continue;
        }
#endif
        printf("Input: n = %d\n", testCase[i].n);

        answer = nthUglyNumber(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
