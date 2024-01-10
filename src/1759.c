#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int countHomogenous(char* s) {
    int retVal = 1;  // 1 <= s.length <= 10^5

    int sSize = strlen(s);
    int homogenous = 1;
    int i;
    for (i = 1; i < sSize; ++i) {
        if (s[i - 1] == s[i]) {
            homogenous += 1;
        } else {
            homogenous = 1;
        }

        retVal += homogenous;
        retVal %= MODULO;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"abbcccaa"}, {"xy"}, {"zzzzz"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abbcccaa"
     *  Output: 13
     *
     *  Input: s = "xy"
     *  Output: 2
     *
     *  Input: s = "zzzzz"
     *  Output: 15
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = countHomogenous(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
