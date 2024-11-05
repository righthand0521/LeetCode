#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minChanges(char* s) {
    int retVal = 0;

    int sSize = strlen(s);
    int i;
    for (i = 1; i < sSize; i += 2) {
        if (s[i - 1] != s[i]) {
            retVal++;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"1001"}, {"10"}, {"0000"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "1001"
     *  Output: 2
     *
     *  Input: s = "10"
     *  Output: 1
     *
     *  Input: s = "0000"
     *  Output: 0
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = minChanges(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
