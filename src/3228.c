#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxOperations(char* s) {
    int retVal = 0;

    int sSize = strlen(s);

    int countOne = 0;
    int i = 0;
    while (i < sSize) {
        if (s[i] == '0') {
            while ((i + 1 < sSize) && (s[i + 1] == '0')) {
                i++;
            }
            retVal += countOne;
        } else {
            countOne++;
        }

        i++;
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
    } testCase[] = {{"1001101"}, {"00111"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "1001101"
     *  Output: 4
     *
     *  Input: s = "00111"
     *  Output: 0
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = maxOperations(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
