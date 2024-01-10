#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* decodeAtIndex(char* s, int k) {
    char* pRetVal = NULL;

    pRetVal = (char*)malloc(2 * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (2 * sizeof(char)));

    int sSize = strlen(s);

    int i;
    long size = 0;
    for (i = 0; i < sSize; ++i) {
        if (isdigit(s[i]) != 0) {
            size *= (s[i] - '0');
        } else {
            size++;
        }
    }

    for (i = sSize - 1; i >= 0; --i) {
        k %= size;
        if ((k == 0) && (isalpha(s[i]) != 0)) {
            pRetVal[0] = s[i];
            break;
        }

        if (isdigit(s[i]) != 0) {
            size /= (s[i] - '0');
        } else {
            size--;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
        int k;
    } testCase[] = {{"leet2code3", 10}, {"ha22", 5}, {"a2345678999999999999999", 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "leet2code3", k = 10
     *  Output: "o"
     *
     *  Input: s = "ha22", k = 5
     *  Output: "h"
     *
     *  Input: s = "a2345678999999999999999", k = 1
     *  Output: "a"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", k = %d\n", testCase[i].s, testCase[i].k);

        pAnswer = decodeAtIndex(testCase[i].s, testCase[i].k);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
