#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numberOfSubstrings(char* s) {
    int retVal = 0;

    int lastPos[3] = {-1, -1, -1};  // Track last position of a, b, c
    int sSize = strlen(s);
    for (int pos = 0; pos < sSize; pos++) {
        // Update last position of current character
        lastPos[s[pos] - 'a'] = pos;

        // Add count of valid substrings ending at current position
        // If any character is missing, min will be -1
        // Else min gives leftmost required character position
        retVal += 1 + fmin(lastPos[0], fmin(lastPos[1], lastPos[2]));
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"abcabc"}, {"aaacb"}, {"abc"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abcabc"
     *  Output: 10
     *
     *  Input: s = "aaacb"
     *  Output: 3
     *
     *  Input: s = "abc"
     *  Output: 1
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = numberOfSubstrings(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
