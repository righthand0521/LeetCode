#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int scoreOfString(char* s) {
    int retVal = 0;

    int sSize = strlen(s);
    int i;
    for (i = 1; i < sSize; ++i) {
        retVal += abs(s[i - 1] - s[i]);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"hello"}, {"zaz"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "hello"
     *  Output: 13
     *
     *  Input: s = "zaz"
     *  Output: 50
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = scoreOfString(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
