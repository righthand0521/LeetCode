#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* minRemoveToMakeValid(char* s) {
    char* pRetVal = s;

    int sSize = strlen(s);

    int parenthesesRight[sSize];
    memset(parenthesesRight, 0, sizeof(parenthesesRight));
    int parenthesesStack[sSize];
    memset(parenthesesStack, 0, sizeof(parenthesesStack));
    int parenthesesStackTop = -1;

    int i, j;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == '(') {
            parenthesesStack[i] = 1;
            parenthesesStackTop = i;
        } else if (s[i] == ')') {
            if (parenthesesStackTop == -1) {
                parenthesesRight[i] = 1;
                continue;
            }

            for (j = parenthesesStackTop; j >= 0; --j) {
                if (parenthesesStack[j] == 1) {
                    parenthesesStack[j] = 0;
                    parenthesesStackTop = j;
                    break;
                }
            }
            for (j = parenthesesStackTop; j >= 0; --j) {
                if (parenthesesStack[j] == 1) {
                    parenthesesStackTop = j;
                    break;
                }
            }
            if (j == -1) {
                parenthesesStackTop = j;
            }
        }
    }

    int idx = 0;
    for (i = 0; i < sSize; ++i) {
        if ((parenthesesRight[i] == 1) || (parenthesesStack[i] == 1)) {
            continue;
        }
        pRetVal[idx++] = s[i];
    }
    pRetVal[idx] = 0;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"lee(t(c)o)de)"}, {"a)b(c)d"}, {"))(("}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "lee(t(c)o)de)"
     *  Output: "lee(t(c)o)de"
     *
     *  Input: s = "a)b(c)d"
     *  Output: "ab(c)d"
     *
     *  Input: s = "))(("
     *  Output: ""
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = minRemoveToMakeValid(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
