#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* toLowerCase(char* s) {
    char* pRetVal = s;

    while (*s) {
        if (((*s) >= 65) && ((*s) <= 90)) {
            (*s) ^= 32;
        }
        ++s;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"Hello"}, {"here"}, {"LOVELY"}, {"al&phaBET"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = toLowerCase(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
