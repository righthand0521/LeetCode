#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int titleToNumber(char *columnTitle) {
    int retVal = 0;

    int multiple = 26;
    int columnTitleSize = strlen(columnTitle);
    int i;
    for (i = 0; i < columnTitleSize; ++i) {
        retVal *= multiple;
        retVal += columnTitle[i] - 'A' + 1;
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (8)
    struct testCaseType {
        char columnTitle[MAX_SIZE];
    } testCase[] = {{"A"}, {"AB"}, {"ZY"}, {"FXSHRXW"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: columnTitle = "A"
     *  Output: 1
     *
     *  Input: columnTitle = "AB"
     *  Output: 28
     *
     *  Input: columnTitle = "ZY"
     *  Output: 701
     *
     *  Input: columnTitle = "FXSHRXW"
     *  Output: 2147483647
     */

    int pAnswer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: columnTitle = \"%s\"\n", testCase[i].columnTitle);

        pAnswer = titleToNumber(testCase[i].columnTitle);
        printf("Output: %d\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
