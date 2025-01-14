#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findThePrefixCommonArray(int* A, int ASize, int* B, int BSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)calloc(ASize, sizeof(int));
    if (pRetVal == NULL) {
        perror("malcallocloc");
        return pRetVal;
    }
    (*returnSize) = ASize;

    int frequency[ASize + 1];
    memset(frequency, 0, sizeof(frequency));
    int commonCount = 0;
    for (int currentIndex = 0; currentIndex < ASize; ++currentIndex) {
        frequency[A[currentIndex]]++;
        if (frequency[A[currentIndex]] == 2) {
            ++commonCount;
        }

        frequency[B[currentIndex]]++;
        if (frequency[B[currentIndex]] == 2) {
            ++commonCount;
        }

        pRetVal[currentIndex] = commonCount;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50)
    struct testCaseType {
        int A[MAX_SIZE];
        int ASize;
        int B[MAX_SIZE];
        int BSize;
        int returnSize;
    } testCase[] = {{{1, 3, 2, 4}, 4, {3, 1, 2, 4}, 4, 0}, {{2, 3, 1}, 3, {3, 1, 2}, 3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: A = [1,3,2,4], B = [3,1,2,4]
     *  Output: [0,2,3,4]
     *
     *  Input: A = [2,3,1], B = [3,1,2]
     *  Output: [0,1,3]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: A = [");
        for (j = 0; j < testCase[i].ASize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].A[j]);
        }
        printf("], B = [");
        for (j = 0; j < testCase[i].BSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].B[j]);
        }
        printf("]\n");

        pAnswer = findThePrefixCommonArray(testCase[i].A, testCase[i].ASize, testCase[i].B, testCase[i].BSize,
                                           &testCase[i].returnSize);
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
