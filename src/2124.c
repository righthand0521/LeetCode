#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool checkString(char* s) {
    bool retVal = true;

    bool isChanged = false;
    int sSize = strlen(s);
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == 'a') {
            if (isChanged == true) {
                retVal = false;
                return retVal;
            }
            continue;
        }

        isChanged = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"aaabbb"}, {"abab"}, {"bbb"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "aaabbb"
     *  Output: true
     *
     *  Input: s = "abab"
     *  Output: false
     *
     *  Input: s = "bbb"
     *  Output: true
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = checkString(testCase[i].s);
        printf("Output: %s\n", answer == true ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
