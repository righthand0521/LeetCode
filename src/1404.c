#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numSteps(char* s) {
    int retVal = 0;

    int sSize = strlen(s);
    int operations = 0;
    int carry = 0;
    int i;
    for (i = sSize - 1; i > 0; i--) {
        if (((s[i] - '0') + carry) % 2) {
            operations += 2;
            carry = 1;
        } else {
            operations++;
        }
    }
    retVal = operations + carry;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"1101"}, {"10"}, {"1"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "1101"
     *  Output: 6
     *
     *  Input: s = "10"
     *  Output: 1
     *
     *  Input: s = "1"
     *  Output: 0
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = numSteps(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
