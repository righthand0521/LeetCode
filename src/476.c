#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findComplement(int num) {
    int retVal = num;

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
        int num;
    } testCase[] = {{5}, {1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: num = 5
     *  Output: 2
     *
     *  Input: num = 1
     *  Output: 0
     */

    uint32_t answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num = %d\n", testCase[i].num);

        answer = findComplement(testCase[i].num);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
