#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int numSub(char* s) {
    int retVal = 0;

    long long total = 0;
    long long consecutiveOneCount = 0;
    int sSize = strlen(s);
    for (int i = 0; i < sSize; ++i) {
        if (s[i] == '1') {
            ++consecutiveOneCount;
        } else {
            total += (consecutiveOneCount * (consecutiveOneCount + 1) / 2);
            total %= MODULO;
            consecutiveOneCount = 0;
        }
    }
    total += (consecutiveOneCount * (consecutiveOneCount + 1) / 2);
    total %= MODULO;

    retVal = (int)total;

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
    } testCase[] = {{"0110111"}, {"101"}, {"111111"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "0110111"
     *  Output: 9
     *
     *  Input: s = "101"
     *  Output: 2
     *
     *  Input: s = "111111"
     *  Output: 21
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = numSub(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
