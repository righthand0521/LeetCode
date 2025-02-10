#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* clearDigits(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);
    int returnSize = sSize + 1;

    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    returnSize = 0;
    for (int i = 0; i < sSize; ++i) {
        if ((isdigit(s[i]) != 0) && (returnSize > 0)) {
            pRetVal[--returnSize] = 0;
        } else {
            pRetVal[returnSize++] = s[i];
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"abc"}, {"cb34"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abc"
     *  Output: "abc"
     *
     *  Input: s = "cb34"
     *  Output: ""
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = clearDigits(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
