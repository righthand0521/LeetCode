#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isOneBitCharacter(int* bits, int bitsSize) {
    bool retVal = false;

    int i = bitsSize - 2;
    while ((i >= 0) && (bits[i] > 0)) {
        i--;
    }
    retVal = ((bitsSize - i) % 2 == 0);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int bits[MAX_SIZE];
        int bitsSize;
    } testCase[] = {{{1, 0, 0}, 3}, {{1, 1, 1, 0}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example:
     *  Input: bits = [1,0,0]
     *  Output: true
     *
     *  Input: bits = [1,1,1,0]
     *  Output: false
     */

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: bits = [");
        for (j = 0; j < testCase[i].bitsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].bits[j]);
        }
        printf("]\n");

        answer = isOneBitCharacter(testCase[i].bits, testCase[i].bitsSize);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
