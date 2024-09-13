#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* xorQueries(int* arr, int arrSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int i;

    int prefixSum[arrSize + 1];
    memset(prefixSum, 0, sizeof(prefixSum));
    for (i = 0; i < arrSize; ++i) {
        prefixSum[i + 1] = prefixSum[i] ^ arr[i];
    }

    pRetVal = (int*)malloc(queriesSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (queriesSize * sizeof(int)));
    for (i = 0; i < queriesSize; ++i) {
        pRetVal[i] = prefixSum[queries[i][1] + 1] ^ prefixSum[queries[i][0]];
        (*returnSize) += 1;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(3 * 10000)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
        int queries[MAX_SIZE][2];
        int queriesSize;
        int queriesColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{{1, 3, 4, 8}, 4, {{0, 1}, {1, 2}, {0, 3}, {3, 3}}, 4, {2, 2, 2, 2}, 0},
                    {{4, 8, 2, 10}, 4, {{2, 3}, {1, 3}, {0, 0}, {0, 3}}, 4, {2, 2, 2, 2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [1,3,4,8], queries = [[0,1],[1,2],[0,3],[3,3]]
     *  Output: [2,7,14,8]
     *
     *  Input: arr = [4,8,2,10], queries = [[2,3],[1,3],[0,0],[0,3]]
     *  Output: [8,0,4,4]
     */

    int** pQueries = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("], queries =  [");
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].queriesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].queries[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pQueries = (int**)malloc(testCase[i].queriesSize * sizeof(int*));
        if (pQueries == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            pQueries[j] = (int*)malloc(testCase[i].queriesColSize[j] * sizeof(int));
            if (pQueries[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pQueries[k]) {
                        free(pQueries[k]);
                        pQueries[k] = NULL;
                    }
                }
                free(pQueries);
                pQueries = NULL;
                return EXIT_FAILURE;
            }
            memset(pQueries[j], 0, testCase[i].queriesColSize[j] * sizeof(int));
            memcpy(pQueries[j], testCase[i].queries[j], testCase[i].queriesColSize[j] * sizeof(int));
        }
        pAnswer = xorQueries(testCase[i].arr, testCase[i].arrSize, pQueries, testCase[i].queriesSize,
                             testCase[i].queriesColSize, &testCase[i].returnSize);
        printf("Output:[");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            if (pQueries[j]) {
                free(pQueries[j]);
                pQueries[j] = NULL;
            }
        }
        free(pQueries);
        pQueries = NULL;
    }

    return EXIT_SUCCESS;
}
