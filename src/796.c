#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool rotateString(char* s, char* goal) {
    bool retVal = false;

    int lenS = strlen(s);
    int lenGoal = strlen(goal);
    if (lenS != lenGoal) {
        return retVal;
    }

    char buf[lenS + 1];
    int i;
    for (i = 0; i < lenS; ++i) {
        if (*(s + i) == *(goal)) {
            memset(buf, 0, sizeof(buf));
            strncpy(buf, s + i, lenS - i);
            strncat(buf, s, i);
            if (strcmp(buf, goal) == 0) {
                retVal = true;
                return retVal;
            }
        }
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
