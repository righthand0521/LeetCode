#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void methodStack(char* s, char* returnS) {
    int sSize = strlen(s);
    int idx = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] != '#') {
            returnS[idx++] = s[i];
        } else if (idx > 0) {
            returnS[--idx] = 0;
        }
    }
}
bool methodTwoPointer(char* s, char* t) {
    bool retVal = false;

    int skipS = 0;
    int skipT = 0;

    int i = strlen(s) - 1;
    int j = strlen(t) - 1;
    while ((i >= 0) || (j >= 0)) {
        while (i >= 0) {
            if (s[i] == '#') {
                skipS += 1;
                i--;
            } else if (skipS > 0) {
                skipS -= 1;
                i--;
            } else {
                break;
            }
        }

        while (j >= 0) {
            if (t[j] == '#') {
                skipT += 1;
                j--;
            } else if (skipT > 0) {
                skipT -= 1;
                j--;
            } else {
                break;
            }
        }

        if ((i >= 0) && (j >= 0)) {
            if (s[i] != t[j]) {
                return retVal;
            }
        } else if ((i >= 0) || (j >= 0)) {
            return retVal;
        }

        i--;
        j--;
    }
    retVal = true;

    return retVal;
}
bool backspaceCompare(char* s, char* t) {
    bool retVal = false;

#if (0)
    int sSize = strlen(s);
    char stackS[sSize + 1];
    memset(stackS, 0, sizeof(stackS));
    methodStack(s, stackS);

    int tSize = strlen(t);
    char stackT[tSize + 1];
    memset(stackT, 0, sizeof(stackT));
    methodStack(t, stackT);

    if (strcmp(stackS, stackT) == 0) {
        retVal = true;
    }
#else
    retVal = methodTwoPointer(s, t);
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (200 + 4)
    struct testCaseType {
        char s[MAX_SIZE];
        char t[MAX_SIZE];
    } testCase[] = {{"ab#c", "ad#c"}, {"ab##", "c#d#"}, {"a#c", "b"}, {"a##c", "#a#c"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "ab#c", t = "ad#c"
     *  Output: true
     *
     *  Input: s = "ab##", t = "c#d#"
     *  Output: true
     *
     *  Input: s = "a#c", t = "b"
     *  Output: false
     *
     *  Input: s = "a##c", t = "#a#c"
     *  Output: true
     */

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", t = \"%s\"\n", testCase[i].s, testCase[i].t);

        answer = backspaceCompare(testCase[i].s, testCase[i].t);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
