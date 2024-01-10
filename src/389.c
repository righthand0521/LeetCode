#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char findTheDifference(char* s, char* t) {
    char retVal = 0;

    while (*s) {
        retVal ^= (*s);
        ++s;
    }

    while (*t) {
        retVal ^= (*t);
        ++t;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char s[MAX_SIZE];
        char t[MAX_SIZE + 1];
    } testCase[] = {{"abcd", "abcde"}, {"", "y"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abcd", t = "abcde"
     *  Output: "e"
     *
     *  Input: s = "", t = "y"
     *  Output: "y"
     */

    char answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", t = \"%s\"\n", testCase[i].s, testCase[i].t);

        answer = findTheDifference(testCase[i].s, testCase[i].t);
        printf("Output: \"%c\"\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
