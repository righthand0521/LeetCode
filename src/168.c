#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* convertToTitle(int columnNumber) {
    char* pRetVal = NULL;

    int returnSize = 8;  // 1 <= columnNumber <= 2^31 - 1
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    char buf[returnSize];
    memset(buf, 0, sizeof(buf));
    int idx = 0;
    int multiple = 26;
    int remainder;
    while (columnNumber > 0) {
        --columnNumber;
        remainder = columnNumber % multiple;
        buf[idx++] = remainder + 'A';
        columnNumber /= multiple;
    }
    returnSize = 0;
    while (idx > 0) {
        pRetVal[returnSize++] = buf[--idx];
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int columnNumber;
    } testCase[] = {{1}, {28}, {701}, {2147483647}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: columnNumber = 1
     *  Output: "A"
     *
     *  Input: columnNumber = 28
     *  Output: "AB"
     *
     *  Input: columnNumber = 701
     *  Output: "ZY"
     *
     *  Input: columnNumber = 2147483647
     *  Output: "FXSHRXW"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: columnNumber = %d\n", testCase[i].columnNumber);

        pAnswer = convertToTitle(testCase[i].columnNumber);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
