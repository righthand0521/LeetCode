#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumMoves(char* s) {
    int retVal = 0;

    int len = strlen(s);

#define CONTINUE_COUNT (3)
#define CONTINUE_CHAR 'X'
    int count = 0;
    int i;
    for (i = 0; i < len; ++i) {
        if (s[i] == CONTINUE_CHAR) {
            ++count;
        } else {
            if (count != 0) {
                ++count;
            }
        }

        if (count == CONTINUE_COUNT) {
            ++retVal;
            count = 0;
        }
    }
    if (count != 0) {
        ++retVal;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"XXX"}, {"XXOX"}, {"OOOO"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = minimumMoves(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}