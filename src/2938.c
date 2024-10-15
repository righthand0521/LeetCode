#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long minimumSteps(char* s) {
    long long retVal = 0;

    int sum = 0;
    int sSize = strlen(s);
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == '1') {
            sum++;
        } else {
            retVal += sum;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"101"}, {"100"}, {"0111"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "101"
     *  Output: 1
     *
     *  Input: s = "100"
     *  Output: 2
     *
     *  Input: s = "0111"
     *  Output: 0
     */

    long long answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = minimumSteps(testCase[i].s);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
