#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENHANCE (1)
char* makeGood(char* s) {
    char* pRetVal = NULL;

    int len = strlen(s);
    int top = -1;
    int i;
#if (ENHANCE)
    printf("Time Complexity: O(n), Space Complexity: O(1).\n");

    for (i = 0; i < len; ++i) {
        if ((top != -1) && (s[top] == (s[i] ^ 32))) {
            --top;
        } else {
            s[++top] = s[i];
        }
    }
    s[++top] = 0;

    pRetVal = s;
#else
    printf("Time Complexity: O(n), Space Complexity: O(n).\n");

    pRetVal = (char*)malloc((len + 1) * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((len + 1) * sizeof(char)));

    for (i = 0; i < len; ++i) {
        if ((top != -1) && (pRetVal[top] == (s[i] ^ 32))) {
            pRetVal[top--] = 0;
        } else {
            pRetVal[++top] = s[i];
        }
    }
#endif

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"leEeetcode"}, {"abBAcC"}, {"s"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = makeGood(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

#if (!ENHANCE)
        if (pAnswer) {
            free(pAnswer);
            pAnswer = NULL;
        }
#endif
    }

    return EXIT_SUCCESS;
}
