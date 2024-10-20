#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool parseBoolExpr(char* expression) {
    bool retVal = false;

    int expressionSize = strlen(expression);

    int stackTop = -1;
    char stack[expressionSize + 1];
    memset(stack, 0, sizeof(stack));

    bool hasTrue, hasFalse;
    char c, topValue, op;
    int i;
    for (i = 0; i < expressionSize; ++i) {
        c = expression[i];
        if ((c == ',') || (c == '(')) {
            continue;
        } else if ((c == 't') || (c == 'f') || (c == '!') || (c == '&') || (c == '|')) {
            stack[++stackTop] = c;
        } else if (c == ')') {
            hasTrue = false;
            hasFalse = false;
            while (stackTop >= 0) {
                if ((stack[stackTop] == '!') || (stack[stackTop] == '&') || (stack[stackTop] == '|')) {
                    break;
                }
                topValue = stack[stackTop--];
                if (topValue == 't') {
                    hasTrue = true;
                } else if (topValue == 'f') {
                    hasFalse = true;
                }
            }

            op = (stackTop >= 0) ? stack[stackTop--] : '0';
            if (op == '!') {
                stack[++stackTop] = (hasTrue == true) ? 'f' : 't';
            } else if (op == '&') {
                stack[++stackTop] = (hasFalse == true) ? 'f' : 't';
            } else {
                stack[++stackTop] = (hasTrue == true) ? 't' : 'f';
            }
        }
    }
    if ((stackTop >= 0) && (stack[stackTop] == 't')) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(2 * 10000)
    struct testCaseType {
        char expression[MAX_SIZE];
    } testCase[] = {{"&(|(f))"}, {"|(f,f,f,t)"}, {"!(&(f,t))"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: expression = "&(|(f))"
     *  Output: false
     *
     *  Input: expression = "|(f,f,f,t)"
     *  Output: true
     *
     *  Input: expression = "!(&(f,t))"
     *  Output: true
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: expression = \"%s\"\n", testCase[i].expression);

        answer = parseBoolExpr(testCase[i].expression);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
