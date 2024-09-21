#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *lexicalOrder(int n, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int *)malloc(n * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (n * sizeof(int)));

    int currentNumber = 1;
    int i;
    for (i = 0; i < n; ++i) {
        pRetVal[(*returnSize)++] = currentNumber;

        if (currentNumber * 10 <= n) {
            currentNumber *= 10;
            continue;
        }

        while ((currentNumber % 10) == 9 || (currentNumber >= n)) {
            currentNumber /= 10;
        }
        currentNumber += 1;
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(5 * 10000)
    struct testCaseType {
        int n;
        int returnSize;
    } testCase[] = {{13, 0}, {2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 13
     *  Output: [1,10,11,12,13,2,3,4,5,6,7,8,9]
     *
     *  Input: n = 2
     *  Output: [1,2]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        pAnswer = lexicalOrder(testCase[i].n, &testCase[i].returnSize);
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
