#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countBinarySubstrings(char* s) {
    int retVal = 0;

    int sSize = strlen(s);

    int current = 1;
    int previous = 0;
    for (int i = 1; i < sSize; ++i) {
        if (s[i] != s[i - 1]) {
            retVal += fmin(current, previous);
            previous = current;
            current = 1;
        } else {
            ++current;
        }
    }
    retVal += fmin(current, previous);

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
    } testCase[] = {{"00110011"}, {"10101"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "00110011"
     *  Output: 6
     *
     *  Input: s = "10101"
     *  Output: 4
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = countBinarySubstrings(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
