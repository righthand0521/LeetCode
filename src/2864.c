#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* maximumOddBinaryNumber(char* s) {
    char* pRetVal = s;

    int sSize = strlen(s);

    int count1 = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == '1') {
            count1++;
        }
    }

    for (i = 0; i < (count1 - 1); ++i) {
        pRetVal[i] = '1';
    }
    for (i = (count1 - 1); i < (sSize - 1); ++i) {
        pRetVal[i] = '0';
    }
    pRetVal[sSize - 1] = '1';

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"010"}, {"0101"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "010"
     *  Output: "001"
     *
     *  Input: s = "0101"
     *  Output: "1001"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = maximumOddBinaryNumber(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
