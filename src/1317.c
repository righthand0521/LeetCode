#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getNoZeroIntegers(int n, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    char aStr[16], bStr[16];
    int a, b;
    for (a = 1; a < n; ++a) {
        b = n - a;

        memset(aStr, 0, sizeof(aStr));
        snprintf(aStr, sizeof(aStr), "%d", a);
        memset(bStr, 0, sizeof(bStr));
        snprintf(bStr, sizeof(bStr), "%d", b);
        if ((strchr(aStr, '0') != NULL) || (strchr(bStr, '0') != NULL)) {
            continue;
        }

        pRetVal = (int*)calloc(2, sizeof(int));
        if (pRetVal == NULL) {
            perror("calloc");
            return pRetVal;
        }
        pRetVal[0] = a;
        pRetVal[1] = b;
        (*returnSize) = 2;
        break;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int returnSize;
    } testCase[] = {{2, 0}, {11, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 2
     *  Output: [1,1]
     *
     *  Input: n = 11
     *  Output: [2,9]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        pAnswer = getNoZeroIntegers(testCase[i].n, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
