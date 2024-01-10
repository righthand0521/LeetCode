#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minOperations(char* s) {
    int retVal = 0;

    int sSize = strlen(s);
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] != '0' + (i % 2)) {
            ++retVal;
        }
    }
    retVal = fmin(retVal, (sSize - retVal));

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
    } testCase[] = {{"0100"}, {"10"}, {"1111"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "0100"
     *  Output: 1
     *
     *  Input: s = "10"
     *  Output: 0
     *
     *  Input: s = "1111"
     *  Output: 2
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = minOperations(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
