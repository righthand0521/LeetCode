#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* makeFancyString(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s) + 1;

    pRetVal = (char*)malloc(sSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (sSize * sizeof(char)));
    int returnSize = 0;

    int i;
    for (i = 0; i < sSize; ++i) {
        if ((returnSize >= 2) && (pRetVal[returnSize - 1] == s[i]) && (pRetVal[returnSize - 2] == s[i])) {
            continue;
        }
        pRetVal[returnSize++] = s[i];
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"leeetcode"}, {"aaabaaaa"}, {"aab"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "leeetcode"
     *  Output: "leetcode"
     *
     *  Input: s = "aaabaaaa"
     *  Output: "aabaa"
     *
     *  Input: s = "aab"
     *  Output: "aab"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = makeFancyString(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        if (pAnswer) {
            free(pAnswer);
            pAnswer = NULL;
        }
    }

    return EXIT_SUCCESS;
}
