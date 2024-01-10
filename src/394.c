#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* decodeString(char* s) {
    char* pRetVal = NULL;

// The test cases are generated so that the length of the output will never exceed 10^5.
#define MAX_OUTPUT_LENGTH (100000)
    pRetVal = (char*)malloc(MAX_OUTPUT_LENGTH * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, MAX_OUTPUT_LENGTH * sizeof(char));
    int returnSize = 0;

    char* pStack = (char*)malloc(MAX_OUTPUT_LENGTH * sizeof(char));
    if (pStack == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset(pStack, 0, MAX_OUTPUT_LENGTH * sizeof(char));
    int stackSize = 0;

    int len = strlen(s);
    char pNumber[len];
    int numberSize;
    int number;
    char tmp[len];

    int i, j;
    for (i = 0; i < len; ++i) {
        if (s[i] != ']') {
            pStack[stackSize++] = s[i];
            continue;
        }

        memset(pRetVal, 0, MAX_OUTPUT_LENGTH * sizeof(char));
        returnSize = 0;
        while (pStack[--stackSize] != '[') {
            pRetVal[returnSize++] = pStack[stackSize];
            pStack[stackSize] = 0;
        }
        pStack[stackSize] = 0;

        memset(pNumber, 0, sizeof(pNumber));
        numberSize = 0;
        while ((stackSize != 0) && (isdigit(pStack[stackSize - 1]))) {
            pNumber[numberSize++] = pStack[--stackSize];
            pStack[stackSize] = 0;
        }
        memset(tmp, 0, sizeof(tmp));
        snprintf(tmp, sizeof(tmp), "%s", pNumber);
        for (j = 0; j < numberSize; ++j) {
            pNumber[numberSize - 1 - j] = tmp[j];
        }
        number = atoi(pNumber);
        while (number--) {
            for (j = returnSize - 1; j >= 0; --j) {
                pStack[stackSize++] = pRetVal[j];
            }
        }
    }
    memset(pRetVal, 0, MAX_OUTPUT_LENGTH * sizeof(char));
    returnSize = stackSize;
    memcpy(pRetVal, pStack, stackSize);

    free(pStack);
    pStack = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (30)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"3[a]2[bc]"}, {"3[a2[c]]"}, {"2[abc]3[cd]ef"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "3[a]2[bc]"
     *  Output: "aaabcbc"
     *
     *  Input: s = "3[a2[c]]"
     *  Output: "accaccacc"
     *
     *  Input: s = "2[abc]3[cd]ef"
     *  Output: "abcabccdcdcdef"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = decodeString(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        if (pAnswer != NULL) {
            free(pAnswer);
            pAnswer = NULL;
        }
    }

    return EXIT_SUCCESS;
}
