#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* plusOne(int* digits, int digitsSize, int* returnSize) {
    int* pRetVal = NULL;

    if (digitsSize != 0) {
        digits[digitsSize - 1] += 1;
    }
    int i;
    for (i = digitsSize - 1; i > 0; --i) {
        digits[i - 1] += (digits[i] / 10);
        digits[i] %= 10;
    }

    int newDigits = 0;
    if (digitsSize != 0) {
        newDigits = digits[0] / 10;
        digits[0] %= 10;
    } else {
        newDigits = 1;
    }

    *returnSize = digitsSize;
    if (newDigits != 0) {
        *returnSize += 1;
    }
    pRetVal = (int*)malloc(*returnSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    if (newDigits != 0) {
        *pRetVal = newDigits;
        if (digitsSize != 0) {
            memcpy(pRetVal + 1, digits, digitsSize * sizeof(int));
        }
    } else {
        memcpy(pRetVal, digits, digitsSize * sizeof(int));
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_NUMSSIZE 100
    struct testCaseType {
        int digits[MAX_NUMSSIZE];
        int digitsSize;
        int returnSize;
    } testCase[] = {{{1, 2, 3}, 3, 0}, {{4, 3, 2, 1}, 4, 0}, {{9}, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: digits = [");
        for (j = 0; j < testCase[i].digitsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].digits[j]);
        }
        printf("]\n");

        pAnswer = plusOne(testCase[i].digits, testCase[i].digitsSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", *(pAnswer + j));
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
