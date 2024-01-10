#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isSubsequence(char* s, char* t) {
    bool retVal = false;

    while (*s && *t) {
        if (*s == *t) {
            ++s;
        }
        ++t;
    }

    if (!(*s)) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_S_SIZE (100)
#define MAX_T_SIZE (int)(1e4)
    struct testCaseType {
        char s[MAX_S_SIZE];
        char t[MAX_T_SIZE];
    } testCase[] = {{"abc", "ahbgdc"}, {"axc", "ahbgdc"}, {"acb", "ahbgdc"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abc", t = "ahbgdc"
     *  Output: true
     *
     *  Input: s = "axc", t = "ahbgdc"
     *  Output: false
     */

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", t = \"%s\"\n", testCase[i].s, testCase[i].t);

        answer = isSubsequence(testCase[i].s, testCase[i].t);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
