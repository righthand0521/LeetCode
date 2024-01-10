#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* largestOddNumber(char* num) {
    char* pRetVal = "";

    int numSize = strlen(num);
    int i;
    for (i = numSize - 1; i >= 0; --i) {
        if ((num[i] - '0') % 2 == 0) {
            continue;
        }
        pRetVal = num;
        num[i + 1] = '\0';
        break;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char num[MAX_SIZE];
    } testCase[] = {{"52"}, {"4206"}, {"35427"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: num = "52"
     *  Output: "5"
     *
     *  Input: num = "4206"
     *  Output: ""
     *
     *  Input: num = "35427"
     *  Output: "35427"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num = \"%s\"\n", testCase[i].num);

        pAnswer = largestOddNumber(testCase[i].num);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
