#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* help(char* pSequence) {
    char* pRetVal = NULL;

    int len = strlen(pSequence);
    int returnSize = 2 * len * sizeof(char) + 1;
    pRetVal = (char*)malloc(returnSize);
    if (pRetVal == NULL) {
        perror("malloc");
        free(pSequence);
        return pRetVal;
    }
    memset(pRetVal, 0, returnSize);

    int idx = 0;
    char digit = pSequence[0];
    int count = 0;
    int i;
    for (i = 0; i < len; ++i) {
        if (digit != pSequence[i]) {
            idx += snprintf(pRetVal + idx, returnSize - idx, "%d%c", count, digit);
            digit = pSequence[i];
            count = 1;
            continue;
        }
        ++count;
    }
    idx += snprintf(pRetVal + idx, returnSize - idx, "%d%c", count, digit);
    free(pSequence);

    return pRetVal;
}
char* countAndSay(int n) {
    char* pRetVal = NULL;

    pRetVal = (char*)malloc(2 * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, 2 * sizeof(char));
    snprintf(pRetVal, 2 * sizeof(char), "%d", 1);

    if (n == 1) {
        return pRetVal;
    }

    int i;
    for (i = 2; i <= n; ++i) {
        pRetVal = help(pRetVal);
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define BOARD_SIZE (9)
    struct testCaseType {
        int n;
    } testCase[] = {{1}, {4}, {30}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        pAnswer = countAndSay(testCase[i].n);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
