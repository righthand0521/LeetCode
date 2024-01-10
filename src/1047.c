#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* removeDuplicates(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);
    pRetVal = (char*)calloc(sSize + 1, sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    int stackHead = 0;

    int i;
    for (i = 0; i < sSize; ++i) {
        if (stackHead == 0) {
            pRetVal[stackHead++] = s[i];
            continue;
        }

        if (pRetVal[stackHead - 1] == s[i]) {
            pRetVal[--stackHead] = 0;
        } else {
            pRetVal[stackHead++] = s[i];
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"abbaca"}, {"azxxzy"}, {"bbaacaab"}, {"xrjjjjjrp"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abbaca"
     *  Output: "ca"
     *
     *  Input: s = "azxxzy"
     *  Output: "ay"
     *
     *  Input: s = "bbaacaab"
     *  Output: "cb"
     *
     *  Input: s = "xrjjjjjrp"
     *  Output: "xrjrp"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = removeDuplicates(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
