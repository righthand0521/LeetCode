#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxScore(char* s) {
    int retVal = 0;

    int sSize = strlen(s);
    int i;

    int ones = 0;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == '1') {
            ones++;
        }
    }

    int zeros = 0;
    for (i = 0; i < sSize - 1; ++i) {
        if (s[i] == '0') {
            zeros++;
        } else {
            ones--;
        }

        retVal = fmax(retVal, (zeros + ones));
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"011101"}, {"00111"}, {"1111"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "011101"
     *  Output: 5
     *
     *  Input: s = "00111"
     *  Output: 5
     *
     *  Input: s = "1111"
     *  Output: 3
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = maxScore(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
