#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculate(char* s) {
    int retVal = 0;

    int sSize = strlen(s);

    int stack[sSize];
    int top = 0;
    int sign = 1;
    int num = 0;
    char ch;
    int i = 0;
    for (i = 0; i < sSize; ++i) {
        ch = s[i];

        if (isdigit(ch)) {
            num = num * 10 + (ch - '0');
        } else if ((ch == '+') || (ch == '-')) {
            retVal += (sign * num);
            num = 0;
            sign = (ch == '+') ? 1 : -1;
        } else if (ch == '(') {
            stack[top++] = retVal;
            stack[top++] = sign;
            retVal = 0;
            sign = 1;
        } else if (ch == ')') {
            retVal += (sign * num);
            num = 0;
            retVal *= stack[--top];
            retVal += stack[--top];
        }
    }
    retVal += (sign * num);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3 * 100000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"1 + 1"}, {" 2-1 + 2 "}, {"(1+(4+5+2)-3)+(6+8)"}, {"1-(     -2)"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "1 + 1"
     *  Output: 2
     *
     *  Input: s = " 2-1 + 2 "
     *  Output: 3
     *
     *  Input: s = "(1+(4+5+2)-3)+(6+8)"
     *  Output: 23
     *
     *  Input: s = "1-(     -2)"
     *  Output: 3
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = calculate(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
