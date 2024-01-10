#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool areNumbersAscending(char* s) {
    bool retVal = false;

    int previous = -1;
    int current = -1;
    int idx = -2;
    int len = strlen(s);
    int i;
    for (i = 0; i < len; ++i) {
        if (isdigit(s[i]) == false) {
            if (current != -1) {
                if (current <= previous) {
                    return retVal;
                }
                previous = current;
                current = -1;
            }
            continue;
        }

        if (i - idx == 1) {
            current = 10 * current + (s[i] - '0');
        } else {
            current = s[i] - '0';
        }
        idx = i;
    }
    if (current != -1) {
        if (current <= previous) {
            return retVal;
        }
        previous = current;
        current = -1;
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"1 box has 3 blue 4 red 6 green and 12 yellow marbles"},
                    {"hello world 5 x 5"},
                    {"sunset is at 7 51 pm overnight lows will be in the low 50 and 60 s"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "1 box has 3 blue 4 red 6 green and 12 yellow marbles"
     *  Output: true
     *
     *  Input: s = "hello world 5 x 5"
     *  Output: false
     *
     *  Input: s = "sunset is at 7 51 pm overnight lows will be in the low 50 and 60 s"
     *  Output: false
     */

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = areNumbersAscending(testCase[i].s);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
