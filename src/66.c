#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* plusOne(int* digits, int digitsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)malloc((digitsSize + 1) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((digitsSize + 1) * sizeof(int)));
    memcpy(pRetVal, digits, (digitsSize * sizeof(int)));
    (*returnSize) = digitsSize;

    int i;
    for (i = digitsSize - 1; i >= 0; --i) {
        pRetVal[i] += 1;
        if (pRetVal[i] != 10) {
            return pRetVal;
        }
        pRetVal[i] = 0;
    }
    memset(pRetVal, 0, ((digitsSize + 1) * sizeof(int)));
    pRetVal[0] = 1;
    (*returnSize) = digitsSize + 1;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int digits[MAX_SIZE];
        int digitsSize;
        int returnSize;
    } testCase[] = {{{1, 2, 3}, 3, 0}, {{4, 3, 2, 1}, 4, 0}, {{9}, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: digits = [1,2,3]
     *  Output: [1,2,4]
     *
     *  Input: digits = [4,3,2,1]
     *  Output: [4,3,2,2]
     *
     *  Input: digits = [9]
     *  Output: [1,0]
     */

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
