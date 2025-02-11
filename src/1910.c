#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool checkMatch(char* stack, int stackTop, char* part, int partLength) {
    bool retVal = true;

    int tmpTop = stackTop;
    char tmp[(stackTop + 1) + 1];
    snprintf(tmp, sizeof(tmp), "%s", stack);
    for (int partIndex = partLength - 1; partIndex >= 0; partIndex--) {
        if (tmp[tmpTop] != part[partIndex]) {
            retVal = false;
            break;
        }
        tmpTop--;
    }

    return retVal;
}
char* removeOccurrences(char* s, char* part) {
    char* pRetVal = "";

    int sSize = strlen(s);
    int partSize = strlen(part);

    int stackTop = -1;
    int returnSize = sSize + 4;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));
    returnSize = 0;

    for (int index = 0; index < sSize; index++) {
        pRetVal[++stackTop] = s[index];
        returnSize = stackTop + 1;

        if ((returnSize < partSize) || (checkMatch(pRetVal, stackTop, part, partSize) == false)) {
            continue;
        }

        for (int j = 0; j < partSize; j++) {
            pRetVal[stackTop--] = '\0';
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char s[MAX_SIZE];
        char part[MAX_SIZE];
    } testCase[] = {{"daabcbaabcbc", "abc"}, {"axxxxyyyyb", "xy"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "daabcbaabcbc", part = "abc"
     *  Output: "dab"
     *
     *  Input: s = "axxxxyyyyb", part = "xy"
     *  Output: "ab"
     */

    char* pAnswer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", part = \"%s\"\n", testCase[i].s, testCase[i].part);

        pAnswer = removeOccurrences(testCase[i].s, testCase[i].part);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
