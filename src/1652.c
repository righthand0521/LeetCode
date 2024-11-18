#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *decrypt(int *code, int codeSize, int k, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int *)calloc(codeSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    (*returnSize) = codeSize;

    if (k == 0) {
        return pRetVal;
    }

    int start = 1;
    int end = k;
    if (k < 0) {  // If k < 0, the starting point will be end of the array.
        start = codeSize - abs(k);
        end = codeSize - 1;
    }

    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += code[i];
    }

    // Scan through the code array as i moving to the right, update the window sum.
    for (int i = 0; i < codeSize; i++) {
        pRetVal[i] = sum;
        sum -= code[start % codeSize];
        sum += code[(end + 1) % codeSize];
        start++;
        end++;
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(100)
    struct testCaseType {
        int code[MAX_SIZE];
        int codeSize;
        int k;
        int returnSize;
    } testCase[] = {{{5, 7, 1, 4}, 4, 3, 0}, {{1, 2, 3, 4}, 4, 0, 0}, {{2, 4, 9, 3}, 4, -2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: code = [5,7,1,4], k = 3
     *  Output: [12,10,16,13]
     *
     *  Input: code = [1,2,3,4], k = 0
     *  Output: [0,0,0,0]
     *
     *  Input: code = [2,4,9,3], k = -2
     *  Output: [12,5,6,13]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: code = [");
        for (j = 0; j < testCase[i].codeSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].code[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        pAnswer = decrypt(testCase[i].code, testCase[i].codeSize, testCase[i].k, &testCase[i].returnSize);
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
