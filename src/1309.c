#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* freqAlphabets(char* s) {
    char* pRetVal = s;

    int len = strlen(s);
    int index = 0;
    int i;
    for (i = 0; i < len; ++i) {
        if (((i + 2) < len) && (s[i + 2] == '#')) {
            s[index++] = (10 * (s[i] - '0') + (s[i + 1] - '0')) - 1 + 'a';
            i += 2;
        } else {
            s[index++] = (s[i] - '0') - 1 + 'a';
        }
    }
    s[index] = 0;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"10#11#12"}, {"1326#"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = freqAlphabets(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
