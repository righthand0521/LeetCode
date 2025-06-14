#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minMaxDifference(int num) {
    int retVal = 0;

#define MAX_NUM_SIZE (16)  // - 1 <= num <= 10^8

    char numMaxStr[MAX_NUM_SIZE];
    memset(numMaxStr, 0, sizeof(numMaxStr));
    snprintf(numMaxStr, sizeof(numMaxStr), "%d", num);
    int idx = 0;
    while ((numMaxStr[idx] != '\0') && (numMaxStr[idx] == '9')) {
        idx++;
    }
    if (numMaxStr[idx] != '\0') {
        char a = numMaxStr[idx];
        for (int i = 0; numMaxStr[i] != '\0'; i++) {
            if (numMaxStr[i] == a) {
                numMaxStr[i] = '9';
            }
        }
    }

    char numMinStr[MAX_NUM_SIZE];
    memset(numMinStr, 0, sizeof(numMinStr));
    snprintf(numMinStr, sizeof(numMinStr), "%d", num);
    char b = numMinStr[0];
    for (int i = 0; numMinStr[i] != '\0'; i++) {
        if (numMinStr[i] == b) {
            numMinStr[i] = '0';
        }
    }

    retVal = atoi(numMaxStr) - atoi(numMinStr);

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int num;
    } testCase[] = {{11891}, {90}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: num = 11891
     *  Output: 99009
     *
     *  Input: num = 90
     *  Output: 99
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num = %d\n", testCase[i].num);

        answer = minMaxDifference(testCase[i].num);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
