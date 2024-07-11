#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* reverseParentheses(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);

    int returnSize = sSize + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    int pRetValTop = -1;
    int reverseStackTop;
    char reverseStack[returnSize];
    int i, j;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == ')') {
            reverseStackTop = -1;
            memset(reverseStack, 0, sizeof(reverseStack));

            while ((pRetValTop > -1) && (pRetVal[pRetValTop] != '(')) {
                reverseStackTop++;
                reverseStack[reverseStackTop] = pRetVal[pRetValTop];
                pRetVal[pRetValTop] = '\0';
                pRetValTop--;
            }

            if (pRetValTop > -1) {
                pRetVal[pRetValTop] = '\0';
                pRetValTop--;
            }

            for (j = 0; j <= reverseStackTop; ++j) {
                pRetValTop++;
                pRetVal[pRetValTop] = reverseStack[j];
            }
        } else {
            pRetValTop++;
            pRetVal[pRetValTop] = s[i];
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"(abcd)"}, {"(u(love)i)"}, {"(ed(et(oc))el)"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "(abcd)"
     *  Output: "dcba"
     *
     *  Input: s = "(u(love)i)"
     *  Output: "iloveu"
     *
     *  Input: s = "(ed(et(oc))el)"
     *  Output: "leetcode"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = reverseParentheses(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
