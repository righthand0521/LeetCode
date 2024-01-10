#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* reverseWords(char* s) {
    char* pRetVal = NULL;

    // malloc return string
    int len = strlen(s) + 1;
    pRetVal = (char*)malloc(len * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, len * sizeof(char));

    // record return string length
    int idx = 0;
    // record head and tail index of word in the input string
    int head = (len - 1) - 1;
    int tail = (len - 1) - 1;
    for (head = ((len - 1) - 1); head >= 0; --head) {
        if (s[head] != ' ') {
            continue;
        }

        if (head != tail) {
            // add separated space for reverse words
            if (idx != 0) {
                idx += snprintf(pRetVal + idx, len - idx, "%s", " ");
            }
            idx += snprintf(pRetVal + idx, len - idx, "%s", s + head + 1);
        }
        tail = head - 1;
        s[head] = 0;
    }
    // add separated space for reverse words
    if ((idx != 0) && (strlen(s + head + 1) > 0)) {
        idx += snprintf(pRetVal + idx, len - idx, "%s", " ");
    }
    idx += snprintf(pRetVal + idx, len - idx, "%s", s + head + 1);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"the sky is blue"}, {"  hello world  "}, {"a good   example"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "the sky is blue"
     *  Output: "blue is sky the"
     *
     *  Input: s = "  hello world  "
     *  Output: "world hello"
     *
     *  Input: s = "a good   example"
     *  Output: "example good a"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = reverseWords(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        if (pAnswer) {
            free(pAnswer);
            pAnswer = NULL;
        }
    }

    return EXIT_SUCCESS;
}
