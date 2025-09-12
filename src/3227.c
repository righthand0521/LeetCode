#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool doesAliceWin(char* s) {
    bool retVal = false;

    retVal = (strpbrk(s, "aeiou") != NULL);

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
    } testCase[] = {{"leetcoder"}, {"bbcd"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "leetcoder"
     *  Output: true
     *
     *  Input: s = "bbcd"
     *  Output: false
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = doesAliceWin(testCase[i].s);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
