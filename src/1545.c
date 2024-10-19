#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char findKthBit(int n, int k) {
    char retVal = '0';

    if (n == 1) {
        return retVal;
    }

    char correspondingBit;
    int length = 1 << n;
    if (k < length / 2) {
        retVal = findKthBit(n - 1, k);
    } else if (k == length / 2) {
        retVal = '1';
    } else {
        correspondingBit = findKthBit(n - 1, length - k);
        retVal = (correspondingBit == '0') ? '1' : '0';
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
        int k;
    } testCase[] = {{3, 1}, {4, 11}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3, k = 1
     *  Output: "0"
     *
     *  Input: n = 4, k = 11
     *  Output: "1"
     */

    char answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, k = %d\n", testCase[i].n, testCase[i].k);

        answer = findKthBit(testCase[i].n, testCase[i].k);
        printf("Output: \"%c\"\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
