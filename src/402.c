#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* removeKdigits(char* num, int k) {
    char* pRetVal = NULL;

    int numSize = strlen(num);

    char numStack[numSize + 1];
    memset(numStack, 0, sizeof(numStack));
    int numStackTop = -1;
    int i;
    for (i = 0; i < numSize; ++i) {
        while ((k > 0) && (numStackTop != -1) && (numStack[numStackTop] > num[i])) {
            numStackTop--;
            k--;
        }
        numStack[++numStackTop] = num[i];
    }

    while (k > 0) {
        numStackTop--;
        k--;
    }

    pRetVal = (char*)malloc((numStackTop + 4) * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((numStackTop + 4) * sizeof(char)));

    int leadingZeros = 1;
    int idx = 0;
    for (i = 0; i <= numStackTop; ++i) {
        if ((leadingZeros == 1) && (numStack[i] == '0')) {
            continue;
        }
        leadingZeros = 0;
        pRetVal[idx++] = numStack[i];
    }
    if (idx == 0) {
        pRetVal[0] = '0';
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char num[MAX_SIZE];
        int k;
    } testCase[] = {{"1432219", 3}, {"10200", 1}, {"10", 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: num = "1432219", k = 3
     *  Output: "1219"
     *
     *  Input: num = "10200", k = 1
     *  Output: "200"
     *
     *  Input: num = "10", k = 2
     *  Output: "0"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num = \"%s\", k = %d\n", testCase[i].num, testCase[i].k);

        pAnswer = removeKdigits(testCase[i].num, testCase[i].k);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
