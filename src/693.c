#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool hasAlternatingBits(int n) {
    bool retVal = false;

    long a = n ^ (n >> 1);
    if ((a & (a + 1)) == 0) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
    int testCase[] = {5, 7, 11};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 5
     *  Output: true
     *
     *  Input: n = 7
     *  Output: false
     *
     *  Input: n = 11
     *  Output: false
     */

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
