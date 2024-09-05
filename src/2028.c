#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *missingRolls(int *rolls, int rollsSize, int mean, int n, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    int total = mean * (rollsSize + n);
    int i;
    for (i = 0; i < rollsSize; ++i) {
        total -= rolls[i];
    }
    if ((total > (6 * n)) || (total < n)) {
        return pRetVal;
    }

    int average = total / n;
    int index = total % n;

    pRetVal = (int *)malloc(n * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (n * sizeof(int)));
    for (i = 0; i < n; ++i) {
        pRetVal[i] = average;
        if (i < index) {
            pRetVal[i] += 1;
        }
    }
    (*returnSize) = n;

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int rolls[MAX_SIZE];
        int rollsSize;
        int mean;
        int n;
        int returnSize;
    } testCase[] = {{{3, 2, 4, 3}, 4, 4, 2, 0}, {{1, 5, 6}, 3, 3, 4, 0}, {{1, 2, 3, 4}, 4, 6, 4, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: rolls = [3,2,4,3], mean = 4, n = 2
     *  Output: [6,6]
     *
     *  Input: rolls = [1,5,6], mean = 3, n = 4
     *  Output: [2,3,2,2]
     *
     *  Input: rolls = [1,2,3,4], mean = 6, n = 4
     *  Output: []
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: rolls = [");
        for (j = 0; j < testCase[i].rollsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].rolls[j]);
        }
        printf("], mean = %d, n = %d\n", testCase[i].mean, testCase[i].n);

        pAnswer = missingRolls(testCase[i].rolls, testCase[i].rollsSize, testCase[i].mean, testCase[i].n,
                               &testCase[i].returnSize);
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
