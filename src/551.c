#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool checkRecord(char* s) {
    bool retVal = true;

    int sSize = strlen(s);
    int late = 0;
    int absent = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == 'A') {
            late = 0;
            absent++;
            if (absent >= 2) {
                retVal = false;
                break;
            }
        } else if (s[i] == 'L') {
            late++;
            if (late >= 3) {
                retVal = false;
                break;
            }
        } else {
            late = 0;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
    } testCase[] = {{"PPALLP"}, {"PPALLL"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "PPALLP"
     *  Output: true
     *
     *  Input: s = "PPALLL"
     *  Output: false
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = checkRecord(testCase[i].s);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
