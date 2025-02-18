#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* smallestNumber(char* pattern) {
    char* pRetVal = NULL;

    int patternSize = strlen(pattern);

    int returnSize = patternSize + 2;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));
    returnSize = 0;

    int numStack[2 * patternSize];
    memset(numStack, 0, sizeof(numStack));
    int numStackTop = -1;
    for (int index = 0; index <= patternSize; index++) {
        // Push the next number onto the stack
        numStack[++numStackTop] = index + 1;

        if ((index != patternSize) && (pattern[index] != 'I')) {
            continue;
        }

        // If 'I' is encountered or we reach the end, pop all stack elements
        while (numStackTop >= 0) {
            pRetVal[returnSize++] = numStack[numStackTop] + '0';
            numStack[numStackTop--] = 0;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (16)
    struct testCaseType {
        char pattern[MAX_SIZE];
    } testCase[] = {{"IIIDIDDD"}, {"DDD"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: pattern = "IIIDIDDD"
     *  Output: "123549876"
     *
     *  Input: pattern = "DDD"
     *  Output: "4321"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: pattern = \"%s\"\n", testCase[i].pattern);

        pAnswer = smallestNumber(testCase[i].pattern);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
