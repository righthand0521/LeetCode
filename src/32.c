#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestValidParentheses(char* s) {
    int retVal = 0;

    int sSize = strlen(s);

    int stackTop = -1;
    int stack[sSize + 1];
    memset(stack, 0, sizeof(stack));
    stackTop++;
    stack[stackTop] = -1;

    int i;
    for (i = 0; i < sSize; i++) {
        if (s[i] == '(') {
            stackTop++;
            stack[stackTop] = i;
            continue;
        }

        stack[stackTop] = 0;
        stackTop--;
        if (stackTop == -1) {
            stackTop++;
            stack[stackTop] = i;
        } else {
            retVal = fmax(retVal, i - stack[stackTop]);
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3 * 10000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"(()"}, {")()())"}, {""}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "(()"
     *  Output: 2
     *
     *  Input: s = ")()())"
     *  Output: 4
     *
     *  Input: s = ""
     *  Output: 0
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = longestValidParentheses(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
