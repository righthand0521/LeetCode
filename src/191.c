#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hammingWeight(uint32_t n) {
    int retVal = 0;

    while (n) {
        if (n & 1) {
            ++retVal;
        }
        n >>= 1;
    }

    return retVal;
}

int main(int argc, char** argv) {
    char* testCase[] = {"00000000000000000000000000001011", "00000000000000000000000010000000",
                        "11111111111111111111111111111101"};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 00000000000000000000000000001011
     *  Output: 3
     *
     *  Input: n = 00000000000000000000000010000000
     *  Output: 1
     *
     *  Input: n = 11111111111111111111111111111101
     *  Output: 31
     */

    uint32_t n = 0;
    int pAnswer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %s\n", testCase[i]);

        n = strtol(testCase[i], NULL, 2);
        pAnswer = hammingWeight(n);
        printf("Output: %d\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
