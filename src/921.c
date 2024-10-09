#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minAddToMakeValid(char* s) {
    int retVal = 0;

    int sSize = strlen(s);
    int openBrackets = 0;
    int minAddsRequired = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == '(') {
            openBrackets++;
        } else {
            // If open bracket exists, match it with the closing one. If not, we need to add a open bracket.
            (openBrackets > 0) ? (openBrackets--) : (minAddsRequired++);
        }
    }

    // Add the remaining open brackets as closing brackets would be required.
    retVal = minAddsRequired + openBrackets;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"())"}, {"((("}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "())"
     *  Output: 1
     *
     *  Input: s = "((("
     *  Output: 3
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = minAddToMakeValid(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
