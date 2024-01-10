#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* removeStars(char* s) {
    char* pRetVal = s;

    int len = strlen(s);
    int idx = 0;
    int i;
    for (i = 0; i < len; ++i) {
        if (s[i] != '*') {
            s[idx++] = s[i];
            continue;
        }
        idx = ((idx > 0) ? (idx - 1) : idx);
    }
    s[idx] = 0;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"leet**cod*e"}, {"erase*****"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "leet**cod*e"
     *  Output: "lecoe"
     *
     *  Input: s = "erase*****"
     *  Output: ""
     */

    char* pAnswer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = removeStars(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
