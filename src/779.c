#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int kthGrammar(int n, int k) {
    int retVal = 0;

#if (0)  // Recursion
    /*
     *  0
     *  0 1
     *  0 1 1 0
     *  0 1 1 0 1 0 0 1
     *  0 1 1 0 1 0 0 1 1 0 0 1 0 1 1 0
     */
    if (k == 1) {
        return retVal;
    }
    if (k > (1 << (n - 2))) {
        retVal = 1 ^ (kthGrammar(n - 1, k - (1 << (n - 2))));
        return retVal;
    }
    retVal = kthGrammar(n - 1, k);
#else  // Bit Manipulation: 0->01, 1-> 10.
    /*
     *  +-------------------------------+
     *  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
     *  +-------------------------------+
     *  | 0 | 1 | 1 | 0 | 1 | 0 | 0 | 1 |
     *  +-------------------------------+
     *  | 0 | 1 |   |   |   |   |   |   |
     *  |   | 1 | 1 | 0 |   |   |   |   |
     *  |   |   | 1 |   | 1 | 0 |   |   |
     *  |   |   |   | 0 |   |   | 0 | 1 |
     *  +-------------------------------+
     */
    // retVal = __builtin_popcount(k - 1) & 1;
    k--;
    while (k > 0) {
        k &= (k - 1);
        retVal ^= 1;
    }
#endif

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int k;
    } testCase[] = {{1, 1}, {2, 1}, {2, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 1, k = 1
     *  Output: 0
     *
     *  Input: n = 2, k = 1
     *  Output: 0
     *
     *  Input: n = 2, k = 2
     *  Output: 1
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, k = %d\n", testCase[i].n, testCase[i].k);

        answer = kthGrammar(testCase[i].n, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
