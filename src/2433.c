#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findArray(int *pref, int prefSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int *)malloc(prefSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (prefSize * sizeof(int)));

    pRetVal[0] = pref[0];  // 1 <= pref.length <= 10^5
    (*returnSize)++;
    int i;
    for (i = 1; i < prefSize; ++i) {
        pRetVal[i] = pref[i - 1] ^ pref[i];
        (*returnSize)++;
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int pref[MAX_SIZE];
        int prefSize;
        int returnSize;
    } testCase[] = {{{5, 2, 0, 3, 1}, 5, 0}, {{13}, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: pref = [5,2,0,3,1]
     *  Output: [5,7,2,3,2]
     *
     *  Input: pref = [13]
     *  Output: [13]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: pref = [");
        for (j = 0; j < testCase[i].prefSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].pref[j]);
        }
        printf("]\n");

        pAnswer = findArray(testCase[i].pref, testCase[i].prefSize, &testCase[i].returnSize);
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
