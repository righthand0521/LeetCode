#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOWERCASE_MAX_SIZE (26)
int longestContinuousSubstring(char *s) {
    int retVal = 1;

    int count = 1;
    int len = strlen(s);
    int i;
    for (i = 1; i < len; ++i) {
        if (s[i] - s[i - 1] == 1) {
            ++count;
            retVal = (retVal > count) ? retVal : count;
        } else {
            count = 1;
        }

#if 1
        if (retVal == LOWERCASE_MAX_SIZE) {
            break;
        }
#endif
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"abacaba"}, {"abcde"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = longestContinuousSubstring(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
