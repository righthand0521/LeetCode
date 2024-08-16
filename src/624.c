#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxDistance(int** arrays, int arraysSize, int* arraysColSize) {
    int retVal = 0;

    int minValue = arrays[0][0];
    int maxValue = arrays[0][arraysColSize[0] - 1];
    int diff1, diff2;
    int i;
    for (i = 1; i < arraysSize; ++i) {
        diff1 = abs(arrays[i][arraysColSize[i] - 1] - minValue);
        diff2 = abs(maxValue - arrays[i][0]);
        retVal = fmax(retVal, fmax(diff1, diff2));

        minValue = fmin(minValue, arrays[i][0]);
        maxValue = fmax(maxValue, arrays[i][arraysColSize[i] - 1]);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e3)
    struct testCaseType {
        int arrays[MAX_SIZE][500];
        int arraysSize;
        int arraysColSize[MAX_SIZE];
    } testCase[] = {{{{1, 2, 3}, {4, 5}, {1, 2, 3}}, 3, {3, 2, 3}}, {{{1}, {1}}, 2, {1, 1}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arrays = [[1,2,3],[4,5],[1,2,3]]
     *  Output: 4
     *
     *  Input: arrays = [[1],[1]]
     *  Output: 0
     */

    int** pArrays = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("arrays = [");
        for (j = 0; j < testCase[i].arraysSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].arraysColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].arrays[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pArrays = (int**)malloc(testCase[i].arraysSize * sizeof(int*));
        if (pArrays == NULL) {
            perror("calloc");
            return EXIT_FAILURE;
        }
        memset(pArrays, 0, testCase[i].arraysSize * sizeof(int*));
        for (j = 0; j < testCase[i].arraysSize; ++j) {
            pArrays[j] = (int*)malloc(testCase[i].arraysColSize[j] * sizeof(int));
            if (pArrays[j] == NULL) {
                perror("calloc");
                for (k = 0; k < j; ++k) {
                    free(pArrays[k]);
                    pArrays[k] = NULL;
                }
                free(pArrays);
                pArrays = NULL;
            }
            memset(pArrays[j], 0, (testCase[i].arraysColSize[j] * sizeof(int)));
            memcpy(pArrays[j], testCase[i].arrays[j], (testCase[i].arraysColSize[j] * sizeof(int)));
        }
        answer = maxDistance(pArrays, testCase[i].arraysSize, testCase[i].arraysColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].arraysSize; ++j) {
            free(pArrays[j]);
            pArrays[j] = NULL;
        }
        free(pArrays);
        pArrays = NULL;
    }

    return EXIT_SUCCESS;
}
