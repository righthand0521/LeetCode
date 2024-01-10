#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int getMostSignificantBit(unsigned int n) {
    unsigned int count = 0;

    while (n >>= 1) {
        ++count;
    }

    return count;
}
int concatenatedBinary(int n) {
    int retVal = 0;

    /* A few distributive properties of modulo are as follows:
     *  1. ( a + b ) % c = ( ( a % c ) + ( b % c ) ) % c
     *  2. ( a * b ) % c = ( ( a % c ) * ( b % c ) ) % c
     *  3. ( a – b ) % c = ( ( a % c ) - ( b % c ) ) % c ( see notes at bottom )
     *  4. ( a / b ) % c NOT EQUAL TO ( ( a % c ) / ( b % c ) ) % c
     */
    int modulo = 1000000000 + 7;
#if 1
    unsigned int shift;
    long ans = 0;
    int i;
    for (i = 1; i <= n; ++i) {
        shift = getMostSignificantBit(i) + 1;
        ans = (((ans << shift) % modulo) + i) % modulo;
    }
    retVal = ans;
#else
    unsigned int shift;
    unsigned int shiftTotal = 0;
    unsigned int tmp = 0;
    int i, j;
    for (i = n; i >= 1; --i) {
        shift = getMostSignificantBit(i) + 1;

        tmp = i;
        for (j = 0; j < shiftTotal; ++j) {
            tmp = ((tmp % modulo) * (2 % modulo)) % modulo;
        }
        retVal += (tmp % modulo);
        retVal %= modulo;

        shiftTotal += shift;
    }
#endif

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{1}, {3}, {12}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = concatenatedBinary(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
