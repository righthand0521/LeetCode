#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countAsterisks(char* s) {
    int retVal = 0;

    int verticalBars = 0;
    int len = strlen(s);
    int i;
    for (i = 0; i < len; ++i) {
        if (s[i] == '|') {
            ++verticalBars;
            continue;
        }

        if (verticalBars % 2 == 1) {
            continue;
        }

        if (s[i] == '*') {
            ++retVal;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"l|*e*et|c**o|*de|"}, {"iamprogrammer"}, {"yo|uar|e**|b|e***au|tifu|l"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = countAsterisks(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
