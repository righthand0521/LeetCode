#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minLength(char *s) {
    int retVal = 0;

    int sSize = strlen(s);

    int stackTop = -1;
    char stack[sSize];
    memset(stack, 0, sizeof(stack));

    int i;
    for (i = 0; i < sSize; ++i) {
        if (stackTop == -1) {
            stack[++stackTop] = s[i];
        } else if ((s[i] == 'B') && (stack[stackTop] == 'A')) {
            stack[stackTop--] = 0;
        } else if ((s[i] == 'D') && (stack[stackTop] == 'C')) {
            stack[stackTop--] = 0;
        } else {
            stack[++stackTop] = s[i];
        }
    }
    retVal = stackTop + 1;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"ABFCACDB"}, {"ACBBD"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "ABFCACDB"
     *  Output: 2
     *
     *  Input: s = "ACBBD"
     *  Output: 5
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = minLength(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
