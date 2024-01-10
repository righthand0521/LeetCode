#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getSum(int a, int b) {
    int retVal = 0;

    unsigned int carry;
    // iterate till there is no carry
    while (b != 0) {
        // carry now contains common set bits of a and b
        carry = a & b;

        // sum of bits of a and b where at least one of the bits is not set
        a = a ^ b;

        // carry is shifted by one so that adding it to a gives the required sum
        b = carry << 1;
    }
    retVal = a;

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int a;
        int b;
    } testCase[] = {{1, 2}, {2, 3}, {-1, 1}, {1, -2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: a = %d, b = %d\n", testCase[i].a, testCase[i].b);

        answer = getSum(testCase[i].a, testCase[i].b);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
