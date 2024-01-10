#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isValid(char *s) {
    bool retVal = false;

    // s consists of parentheses only '()[]{}'.
    struct Parentheses_t {
        char open;
        char close;
    } parenthesesMap[] = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
    int numberOfParentheses = sizeof(parenthesesMap) / sizeof(parenthesesMap[0]);

    int sSize = strlen(s);
    char stack[sSize];
    memset(stack, 0, sizeof(stack));
    int stackHead = 0;
    int i, j;
    for (i = 0; i < sSize; ++i) {
        for (j = 0; j < numberOfParentheses; ++j) {
            if (s[i] == parenthesesMap[j].open) {
                stack[stackHead++] = parenthesesMap[j].close;
                break;
            }

            if (s[i] == parenthesesMap[j].close) {
                if (stackHead == 0) {
                    return retVal;
                }

                if (s[i] != stack[--stackHead]) {
                    return retVal;
                }
                stack[stackHead] = '\0';
            }
        }
    }
    if (stackHead == 0) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"()"}, {"()[]{}"}, {"(]"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "()"
     *  Output: true
     *
     *  Input: s = "()[]{}"
     *  Output: true
     *
     *  Input: s = "(]"
     *  Output: false
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = isValid(testCase[i].s);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
