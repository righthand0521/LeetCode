#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countSeniors(char **details, int detailsSize) {
    int retVal = 0;

    int age;
    int i;
    for (i = 0; i < detailsSize; ++i) {
        age = 10 * (details[i][11] - '0') + (details[i][12] - '0');
        if (age > 60) {
            retVal++;
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char *details[MAX_SIZE];
        int detailsSize;
    } testCase[] = {{{"7868190130M7522", "5303914400F9211", "9273338290F4010"}, 3},
                    {{"1313579440F2036", "2921522980M5644"}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: details = ["7868190130M7522","5303914400F9211","9273338290F4010"]
     *  Output: 2
     *
     *  Input: details = ["1313579440F2036","2921522980M5644"]
     *  Output: 0
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: details = [");
        for (j = 0; j < testCase[i].detailsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].details[j]);
        }
        printf("]\n");

        answer = countSeniors(testCase[i].details, testCase[i].detailsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
