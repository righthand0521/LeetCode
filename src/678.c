#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool checkValidString(char* s) {
    bool retVal = false;

    int sSize = strlen(s);
    int leftParenthesis = 0;
    int rightParenthesis = 0;
    int left, right;
    for (left = 0; left < sSize; ++left) {
        if ((s[left] == '(') || (s[left] == '*')) {
            leftParenthesis++;
        } else if (s[left] == ')') {
            leftParenthesis--;
        }

        right = sSize - 1 - left;
        if ((s[right] == ')') || (s[right] == '*')) {
            rightParenthesis++;
        } else if (s[right] == '(') {
            rightParenthesis--;
        }

        if ((leftParenthesis < 0) || (rightParenthesis < 0)) {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"()"}, {"(*)"}, {"(*))"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "()"
     *  Output: true
     *
     *  Input: s = "(*)"
     *  Output: true
     *
     *  Input: s = "(*))"
     *  Output: true
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = checkValidString(testCase[i].s);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
