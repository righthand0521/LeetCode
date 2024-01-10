#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isOneEditDistance(char* s, char* t) {
    bool retVal = false;

    // check the length of difference could not exceed 1
    int lenS = strlen(s);
    int lenT = strlen(t);
    if (abs(lenS - lenT) > 1) {
        return retVal;
    }

    int i;
    int diff = 0;
    // at most one character could different if the length are the same
    if (lenS == lenT) {
        for (i = 0; i < lenS; ++i) {
            if (s[i] != t[i]) {
                ++diff;
            }
        }
        if (diff == 1) {
            retVal = true;
        }

        return retVal;
    }

    int idxS = 0;
    int idxT = 0;
    while ((idxS < lenS) && (idxT < lenT)) {
        // check remaining characters are the same except the only one different character if the length are different
        if (s[idxS] != t[idxT]) {
            if (idxS != idxT) {
                return retVal;
            }
            if (lenS > lenT) {
                ++idxS;
            } else {
                ++idxT;
            }
            continue;
        }

        ++idxS;
        ++idxT;
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        char s[MAX_SIZE];
        char t[MAX_SIZE];
    } testCase[] = {{"ab", "acb"},           {"", ""},     {"pale", "ple"},         {"pales", "pal"},
                    {"islander", "slander"}, {"ab", "bc"}, {"teacher", "treacher"}, {"teacher", "beacher"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", t = \"%s\"\n", testCase[i].s, testCase[i].t);

        answer = isOneEditDistance(testCase[i].s, testCase[i].t);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
