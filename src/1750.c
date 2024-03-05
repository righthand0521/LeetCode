#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumLength(char* s) {
    int retVal = 0;

    char equal;
    int left = 0;
    int right = strlen(s) - 1;
    while ((left < right) && (s[left] == s[right])) {
        equal = s[left];
        while ((left <= right) && (s[left] == equal)) {
            ++left;
        }
        while ((left <= right) && (s[right] == equal)) {
            --right;
        }
    }
    retVal = right - left + 1;

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
    } testCase[] = {{"ca"}, {"cabaabac"}, {"aabccabba"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "ca"
     *  Output: 2
     *
     *  Input: s = "cabaabac"
     *  Output: 0
     *
     *  Input: s = "aabccabba"
     *  Output: 3
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = minimumLength(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
