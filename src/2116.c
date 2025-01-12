#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool canBeValid(char* s, char* locked) {
    bool retVal = false;

    int sSize = strlen(s);
    if (sSize % 2 == 1) {
        return retVal;
    }

    int openBracketsStackTop = -1;
    int openBracketsStack[sSize];
    memset(openBracketsStack, -1, sizeof(openBracketsStack));
    int unlockedStackTop = -1;
    int unlockedStack[sSize];
    memset(unlockedStack, -1, sizeof(unlockedStack));
    for (int i = 0; i < sSize; i++) {
        if (locked[i] == '0') {
            unlockedStack[++unlockedStackTop] = i;
        } else if (s[i] == '(') {
            openBracketsStack[++openBracketsStackTop] = i;
        } else if (s[i] == ')') {
            if (openBracketsStackTop != -1) {
                openBracketsStack[openBracketsStackTop--] = 0;
            } else if (unlockedStackTop != -1) {
                unlockedStack[unlockedStackTop--] = 0;
            } else {
                return retVal;
            }
        }
    }

    while ((openBracketsStackTop != -1) && (unlockedStackTop != -1) &&
           (openBracketsStack[openBracketsStackTop] < unlockedStack[unlockedStackTop])) {
        openBracketsStack[openBracketsStackTop--] = 0;
        unlockedStack[unlockedStackTop--] = 0;
    }
    if (openBracketsStackTop == -1) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
        char locked[MAX_SIZE];
    } testCase[] = {{"))()))", "010100"}, {"()()", "0000"}, {")", "0"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "))()))", locked = "010100"
     *  Output: true
     *
     *  Input: s = "()()", locked = "0000"
     *  Output: true
     *
     *  Input: s = ")", locked = "0"
     *  Output: false
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; i++) {
        printf("Input: s = \"%s\", locked = \"%s\"\n", testCase[i].s, testCase[i].locked);

        answer = canBeValid(testCase[i].s, testCase[i].locked);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
