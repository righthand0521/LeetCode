#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countSubstrings(char* s) {
    int retVal = 0;

    int sSize = strlen(s);

    int left, right;
    int i;
    for (i = 0; i < (2 * sSize - 1); ++i) {
        left = i / 2;
        right = i / 2 + i % 2;
        while ((left >= 0) && (right < sSize) && (s[left] == s[right])) {
            --left;
            ++right;
            ++retVal;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"abc"}, {"aaa"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abc"
     *  Output: 3
     *
     *  Input: s = "aaa"
     *  Output: 6
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = countSubstrings(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
