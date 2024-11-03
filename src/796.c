#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool rotateString(char* s, char* goal) {
    bool retVal = false;

    int sSize = strlen(s);
    int goalSize = strlen(goal);
    if (sSize != goalSize) {
        return retVal;
    }

    char doubleS[sSize * 2 + 1];
    memset(doubleS, 0, sizeof(doubleS));
    snprintf(doubleS, sizeof(doubleS), "%s%s", s, s);
    if (strstr(doubleS, goal) != NULL) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
        char goal[MAX_SIZE];
    } testCase[] = {{"abcde", "cdeab"},
                    {"abcde", "abced"},
                    {"a", "aa"},
                    {"bbbacddceeb", "ceebbbbacdd"},
                    {"waterbottle", "erbottlewat"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abcde", goal = "cdeab"
     *  Output: true
     *
     *  Input: s = "abcde", goal = "abced"
     *  Output: false
     */

    bool pAnswer = true;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", goal = \"%s\"\n", testCase[i].s, testCase[i].goal);

        pAnswer = rotateString(testCase[i].s, testCase[i].goal);
        printf("Output: %s\n", pAnswer ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
