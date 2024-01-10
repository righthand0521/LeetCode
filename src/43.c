#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* multiply(char* num1, char* num2) {
    unsigned char* pRetVal = NULL;

    if ((strcmp(num1, "0") == 0) || (strcmp(num2, "0") == 0)) {
        pRetVal = (unsigned char*)malloc(2 * sizeof(unsigned char));
        if (pRetVal == NULL) {
            perror("malloc");
            return (char*)(pRetVal);
        }
        memset(pRetVal, 0, 2 * sizeof(unsigned char));
        pRetVal[0] = '0';

        return (char*)(pRetVal);
    }

    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int len = len1 + len2 + 1;
    pRetVal = (unsigned char*)malloc(len * sizeof(unsigned char));
    if (pRetVal == NULL) {
        perror("malloc");
        return (char*)(pRetVal);
    }
    memset(pRetVal, '0', (len - 1) * sizeof(unsigned char));
    pRetVal[len - 1] = 0;

    int multiplicand;
    int multiplier;
    int product = 0;
    int carry = 0;
    int i, j;
    for (i = len1 - 1; i >= 0; --i) {
        multiplicand = num1[i] - '0';
        for (j = len2 - 1; j >= 0; --j) {
            multiplier = num2[j] - '0';
            product = multiplicand * multiplier;

            pRetVal[i + j + 1] = pRetVal[i + j + 1] + product;
            carry = (pRetVal[i + j + 1] - '0') / 10;
            pRetVal[i + j + 1] = ((pRetVal[i + j + 1] - '0') % 10) + '0';
            pRetVal[i + j] = pRetVal[i + j] + carry;

            // printf("(%d,%d)[%d,%d][%d,%d][%s]\n", i,j,multiplicand, multiplier, carry, product, pRetVal);
        }
    }

    if (pRetVal[0] == '0') {
        for (i = 0; i < (len - 2); ++i) {
            pRetVal[i] = pRetVal[i + 1];
        }
        pRetVal[i] = 0;
    }

    return (char*)(pRetVal);
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* num1;
        char* num2;
    } testCase[] = {{"2", "3"},
                    {"123", "456"},
                    {"9", "99"},
                    {"0", "999"},
                    {"99", "0"},
                    {"0", "0"},
                    {"999999999999999999999999999999", "999999999999999999999999999999"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

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
