#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KMP (1)  // https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
#define STRING_CONCATENATION (1)
bool repeatedSubstringPattern(char* s) {
    bool retVal = false;

    int sSize = strlen(s);
#if (KMP)
    printf("Knuth-Morris-Pratt Algorithm\n");

    int next[sSize];
    memset(next, 0, sizeof(next));

    int j = -1;
    next[0] = j;
    int i;
    for (i = 1; i < sSize; ++i) {
        while ((j >= 0) && (s[i] != s[j + 1])) {
            j = next[j];
        }

        if (s[i] == s[j + 1]) {
            ++j;
        }

        next[i] = j;
    }

    if ((next[sSize - 1] != -1) && (sSize % (sSize - next[sSize - 1] - 1) == 0)) {
        retVal = true;
    }
#elif (STRING_CONCATENATION)
    printf("String Concatenation\n");

    char buf[2 * sSize + 1];
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "%s%s", s, s);
    if (strstr(buf + 1, s) - buf != sSize) {
        retVal = true;
    }
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"abab"}, {"aba"}, {"abcabcabcabc"}, {"abac"}, {"bb"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abab"
     *  Output: true
     *
     *  Input: s = "aba"
     *  Output: false
     *
     *  Input: s = "abcabcabcabc"
     *  Output: true
     *
     *  Input: s = "abac"
     *  Output: false
     *
     *  Input: s = "bb"
     *  Output: true
     */

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = repeatedSubstringPattern(testCase[i].s);
        printf("Output: %s\n", answer == true ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
