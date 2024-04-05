#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* makeGood(char* s) {
    char* pRetVal = s;

    int sSize = strlen(s);
    int top = -1;
    int i;
    for (i = 0; i < sSize; ++i) {
        if ((top != -1) && (pRetVal[top] == (pRetVal[i] ^ 32))) {
            --top;
        } else {
            pRetVal[++top] = pRetVal[i];
        }
    }
    pRetVal[++top] = 0;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"leEeetcode"}, {"abBAcC"}, {"s"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "leEeetcode"
     *  Output: "leetcode"
     *
     *  Input: s = "abBAcC"
     *  Output: ""
     *
     *  Input: s = "s"
     *  Output: "s"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = makeGood(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
