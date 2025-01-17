#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool doesValidArrayExist(int* derived, int derivedSize) {
    bool retVal = false;

    int XOR = 0;
    for (int i = 0; i < derivedSize; ++i) {
        XOR = XOR ^ derived[i];
    }
    if (XOR == 0) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int derived[MAX_SIZE];
        int derivedSize;
    } testCase[] = {{{1, 1, 0}, 3}, {{1, 1}, 2}, {{1, 0}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: derived = [1,1,0]
     *  Output: true
     *
     *  Input: derived = [1,1]
     *  Output: true
     *
     *  Input: derived = [1,0]
     *  Output: false
     */

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: derived = [");
        for (j = 0; j < testCase[i].derivedSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].derived[j]);
        }
        printf("]\n");

        answer = doesValidArrayExist(testCase[i].derived, testCase[i].derivedSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
