#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bitwiseComplement(int n) {
    int retVal = n;

    // 0 <= n < 10^9
    if (n == 0) {
        retVal = 1;
        return retVal;
    }

    int i = 31;
    while ((retVal & ((uint32_t)1 << i)) == 0) {
        i--;
    }

    while (i >= 0) {
        retVal ^= (1 << i--);
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{5}, {7}, {10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 5
     *  Output: 2
     *
     *  Input: n = 7
     *  Output: 0
     *
     *  Input: n = 10
     *  Output: 5
     */

    uint32_t answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = bitwiseComplement(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
