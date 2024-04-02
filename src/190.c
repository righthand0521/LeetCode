#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t reverseBits(uint32_t n) {
    uint32_t retVal = 0;

#if (1)
    int i;
    for (i = 0; i < 32; ++i) {
        retVal = (retVal << 1) | (n & 0x1);
        n >>= 1;
    }
#else
#define M1 (0x55555555)
#define M2 (0x33333333)
#define M4 (0x0f0f0f0f)
#define M8 (0x00ff00ff)

    n = ((n >> 1) & M1) | ((n & M1) << 1);
    n = ((n >> 2) & M2) | ((n & M2) << 2);
    n = ((n >> 4) & M4) | ((n & M4) << 4);
    n = ((n >> 8) & M8) | ((n & M8) << 8);
    retVal = ((n >> 16) | (n << 16));
#endif

    return retVal;
}

int main(int argc, char **argv) {
    uint32_t testCase[] = {43261596, 4294967293};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 00000010100101000001111010011100
     *  Output:    964176192 (00111001011110000010100101000000)
     *
     *  Input: n = 11111111111111111111111111111101
     *  Output:   3221225471 (10111111111111111111111111111111)
     */

    uint32_t answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = ");
        for (j = 31; j >= 0; --j) {
            printf("%d", ((testCase[i] & (1 << j)) >> j));
        }
        printf("\n");

        answer = reverseBits(testCase[i]);
        printf("Output: %12u (", answer);
        for (j = 31; j >= 0; --j) {
            printf("%d", ((answer & (1 << j)) >> j));
        }
        printf(")\n");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
