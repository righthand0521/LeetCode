#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxDepth(char* s) {
    int retVal = 0;

    int sSize = strlen(s);
    int count = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == '(') {
            count++;
        } else if (s[i] == ')') {
            count--;
        }
        retVal = fmax(retVal, count);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"(1+(2*3)+((8)/4))+1"}, {"(1)+((2))+(((3)))"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "(1+(2*3)+((8)/4))+1"
     *  Output: 3
     *
     *  Input: s = "(1)+((2))+(((3)))"
     *  Output: 3
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = maxDepth(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
