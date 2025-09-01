#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* grayCode(int n, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 1 << n;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    for (int i = 0; i < (*returnSize); i++) {
        pRetVal[i] = (i >> 1) ^ i;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int returnSize;
    } testCase[] = {{2, 0}, {1, 0}, {3, 0}, {4, 0}, {5, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 2
     *  Output: [0,1,3,2]
     *
     *  Input: n = 1
     *  Output: [0,1]
     *
     *  Input: n = 3
     *  Output: [0,1,3,2,6,7,5,4]
     *
     *  Input: n = 4
     *  Output: [0,1,3,2,6,7,5,4,12,13,15,14,10,11,9,8]
     *
     *  Input: n = 5
     *  Output: [0,1,3,2,6,7,5,4,12,13,15,14,10,11,9,8,24,25,27,26,30,31,29,28,20,21,23,22,18,19,17,16]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        pAnswer = grayCode(testCase[i].n, &testCase[i].returnSize);
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
