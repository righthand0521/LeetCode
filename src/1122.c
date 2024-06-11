#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* relativeSortArray(int* arr1, int arr1Size, int* arr2, int arr2Size, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)malloc(arr1Size * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (arr1Size * sizeof(int)));

    int i, j;

    int upper = arr1[0];
    for (i = 0; i < arr1Size; ++i) {
        upper = fmax(upper, arr1[i]);
    }

    int frequency[upper + 1];
    memset(frequency, 0, sizeof(frequency));
    for (i = 0; i < arr1Size; ++i) {
        frequency[arr1[i]] += 1;
    }

    for (i = 0; i < arr2Size; ++i) {
        for (j = 0; j < frequency[arr2[i]]; ++j) {
            pRetVal[*(returnSize)] = arr2[i];
            *(returnSize) += 1;
        }
        frequency[arr2[i]] = 0;
    }
    for (i = 0; i < upper + 1; ++i) {
        if (frequency[i] != 0) {
            for (j = 0; j < frequency[i]; ++j) {
                pRetVal[*(returnSize)] = i;
                *(returnSize) += 1;
            }
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int arr1[MAX_SIZE];
        int arr1Size;
        int arr2[MAX_SIZE];
        int arr2Size;
        int returnSize;
    } testCase[] = {{{2, 3, 1, 3, 2, 4, 6, 7, 9, 2, 19}, 11, {2, 1, 4, 3, 9, 6}, 6, 0},
                    {{28, 6, 22, 8, 44, 17}, 6, {22, 28, 8, 6}, 4, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
     *  Output: [2,2,2,1,4,3,3,9,6,7,19]
     *
     *  Input: arr1 = [28,6,22,8,44,17], arr2 = [22,28,8,6]
     *  Output: [22,28,8,6,17,44]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr1 = [");
        for (j = 0; j < testCase[i].arr1Size; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr1[j]);
        }
        printf("], arr2 = [");
        for (j = 0; j < testCase[i].arr2Size; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr2[j]);
        }
        printf("]\n");

        pAnswer = relativeSortArray(testCase[i].arr1, testCase[i].arr1Size, testCase[i].arr2, testCase[i].arr2Size,
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
