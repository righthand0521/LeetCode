#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool hasAlternatingBits(int n) {
    bool retVal = false;

#if 1
    /* right shift 2 bit will become all 2^n
     *    000101010
     *  ^ 000001010
     *  = 000100000
     */
    n ^= (n >> 2);
    unsigned int m = (unsigned int)(n)-1;
    if ((n & m) == 0) {
        retVal = true;
    }
#else
    /* right shift 1 bit will become 2^n-1
     *    000101010
     *  ^ 000010101
     *  = 000111111
     */
    n ^= (n >> 1);
    unsigned int m = (unsigned int)(n) + 1;
    if ((n & m) == 0) {
        retVal = true;
    }
#endif

    return retVal;
}

int main(int argc, char **argv) {
    int testCase[] = {5, 7, 11, 1, 2, 3, 4, 8, 9, INT_MAX};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i]);

        answer = hasAlternatingBits(testCase[i]);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
