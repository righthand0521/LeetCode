#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* multiply(char* num1, char* num2) {
    char* pRetVal = NULL;

    if ((strcmp(num1, "0") == 0) || (strcmp(num2, "0") == 0)) {
        pRetVal = (char*)malloc(2 * sizeof(char));
        if (pRetVal == NULL) {
            perror("malloc");
            return pRetVal;
        }
        memset(pRetVal, 0, 2 * sizeof(char));
        pRetVal[0] = '0';

        return pRetVal;
    }

    int num1Size = strlen(num1);
    int num2Size = strlen(num2);
    int returnBufSize = num1Size + num2Size;
    int returnBuf[returnBufSize];
    memset(returnBuf, 0, sizeof(returnBuf));
    int multiplicand, multiplier, product, carry;
    int i, j;
    for (i = num1Size - 1; i >= 0; --i) {
        multiplicand = num1[i] - '0';
        for (j = num2Size - 1; j >= 0; --j) {
            multiplier = num2[j] - '0';
            product = multiplicand * multiplier;
            returnBuf[i + j + 1] = returnBuf[i + j + 1] + product;
            carry = returnBuf[i + j + 1] / 10;
            returnBuf[i + j + 1] = (returnBuf[i + j + 1] % 10);
            returnBuf[i + j] = returnBuf[i + j] + carry;
        }
    }

    int returnSize = num1Size + num2Size + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));
    returnSize = 0;
    if (returnBuf[0] != 0) {
        pRetVal[returnSize++] += returnBuf[0] + '0';
    }
    for (i = 1; i < returnBufSize; ++i) {
        pRetVal[returnSize++] += returnBuf[i] + '0';
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* num1;
        char* num2;
    } testCase[] = {{"2", "3"}, {"123", "456"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: num1 = "2", num2 = "3"
     *  Output: "6"
     *
     *  Input: num1 = "123", num2 = "456"
     *  Output: "56088"
     */

    char* pAnswer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num1=\"%s\", num2=\"%s\"\n", testCase[i].num1, testCase[i].num2);

        pAnswer = multiply(testCase[i].num1, testCase[i].num2);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
