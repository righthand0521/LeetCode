#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* numberToWords(int num) {
    char* pRetVal = NULL;

    int returnSize = 1000;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    if (num == 0) {
        snprintf(pRetVal, returnSize, "%s", "Zero");
        return pRetVal;
    }

    char* ones[] = {"",         "One",     "Two",     "Three",     "Four",     "Five",    "Six",
                    "Seven",    "Eight",   "Nine",    "Ten",       "Eleven",   "Twelve",  "Thirteen",
                    "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    char* tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    char* thousands[] = {"", "Thousand", "Million", "Billion"};

    int groupResultIdx;
    char groupResult[returnSize];
    int part;
    int groupIndex = 0;
    while (num > 0) {
        if (num % 1000 != 0) {
            groupResultIdx = 0;
            memset(groupResult, 0, sizeof(groupResult));
            part = num % 1000;

            if (part >= 100) {
                groupResultIdx += snprintf(groupResult + groupResultIdx, sizeof(groupResult) - groupResultIdx - 1,
                                           "%s Hundred ", ones[part / 100]);
                part %= 100;
            }

            if (part >= 20) {
                groupResultIdx += snprintf(groupResult + groupResultIdx, sizeof(groupResult) - groupResultIdx - 1,
                                           "%s ", tens[part / 10]);
                part %= 10;
            }

            if (part > 0) {
                groupResultIdx +=
                    snprintf(groupResult + groupResultIdx, sizeof(groupResult) - groupResultIdx - 1, "%s ", ones[part]);
            }

            groupResultIdx += snprintf(groupResult + groupResultIdx, sizeof(groupResult) - groupResultIdx - 1, "%s ",
                                       thousands[groupIndex]);
            groupResultIdx +=
                snprintf(groupResult + groupResultIdx, sizeof(groupResult) - groupResultIdx - 1, "%s", pRetVal);
            snprintf(pRetVal, returnSize, "%s", groupResult);
        }

        num /= 1000;
        groupIndex += 1;
    }

    int i = strlen(pRetVal) - 1;
    while (pRetVal[i] == ' ') {
        pRetVal[i--] = '\0';
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int num;
    } testCase[] = {{123}, {12345}, {1234567}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: num = 123
     *  Output: "One Hundred Twenty Three"
     *
     *  Input: num = 12345
     *  Output: "Twelve Thousand Three Hundred Forty Five"
     *
     *  Input: num = 1234567
     *  Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num  = %d\n", testCase[i].num);

        pAnswer = numberToWords(testCase[i].num);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
