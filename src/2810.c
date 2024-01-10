#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* finalString(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);

    int left, right;
    char tmp;
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] != 'i') {
            continue;
        }

        left = 0;
        right = i - 1;
        while (left < right) {
            tmp = s[left];
            s[left++] = s[right];
            s[right--] = tmp;
        }
    }

    int returnSize = sSize + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    int idx = 0;
    for (i = 0; i < sSize; ++i) {
        if (s[i] != 'i') {
            pRetVal[idx++] = s[i];
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"string"}, {"poiinter"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "string"
     *  Output: "rtsng"
     *
     *  Input: s = "poiinter"
     *  Output: "ponter"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = finalString(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
