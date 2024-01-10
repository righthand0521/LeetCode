#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void *pa, const void *pb) {
    const int *a = *(const int **)pa;
    const int *b = *(const int **)pb;
    if (a[1] == b[1]) {
        return b[0] - a[0];
    } else {
        return b[1] - a[1];
    }
}
int maximumUnits(int **boxTypes, int boxTypesSize, int *boxTypesColSize, int truckSize) {
    int retVal = 0;

    qsort(boxTypes, boxTypesSize, sizeof(boxTypes[0]), compareIntArray);

    int i;
    for (i = 0; i < boxTypesSize; ++i) {
        if (truckSize > boxTypes[i][0]) {
            truckSize -= boxTypes[i][0];
            retVal += (boxTypes[i][0] * boxTypes[i][1]);
        } else {
            retVal += (truckSize * boxTypes[i][1]);
            break;
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int boxTypes[MAX_SIZE][MAX_SIZE];
        int boxTypesSize;
        int boxTypesColSize[MAX_SIZE];
        int truckSize;
    } testCase[] = {{{{1, 3}, {2, 2}, {3, 1}}, 3, {2, 2, 2}, 4},
                    {{{5, 10}, {2, 5}, {4, 7}, {3, 9}}, 4, {2, 2, 2, 2}, 10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int **pBoxTypes = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: boxTypes = [");
        for (j = 0; j < testCase[i].boxTypesSize; ++j) {
            printf("[");
            for (k = 0; k < testCase[i].boxTypesColSize[j]; ++k) {
                printf("%d%s", testCase[i].boxTypes[j][k], (k == (testCase[i].boxTypesColSize[j] - 1) ? "" : ","));
            }
            printf("%s", (j == (testCase[i].boxTypesSize - 1) ? "]" : "],"));
        }
        printf("]\n");

        pBoxTypes = (int **)malloc(testCase[i].boxTypesSize * sizeof(int *));
        if (pBoxTypes == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].boxTypesSize; ++j) {
            pBoxTypes[j] = (int *)malloc(testCase[i].boxTypesColSize[j] * sizeof(int));
            if (pBoxTypes[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pBoxTypes[k]);
                    pBoxTypes[k] = NULL;
                }
                free(pBoxTypes);
                pBoxTypes = NULL;
                return EXIT_FAILURE;
            }
            memset(pBoxTypes[j], 0, testCase[i].boxTypesColSize[j] * sizeof(int));
        }
        for (j = 0; j < testCase[i].boxTypesSize; ++j) {
            for (k = 0; k < testCase[i].boxTypesColSize[j]; ++k) {
                pBoxTypes[j][k] = testCase[i].boxTypes[j][k];
            }
        }
        answer = maximumUnits(pBoxTypes, testCase[i].boxTypesSize, testCase[i].boxTypesColSize, testCase[i].truckSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].boxTypesSize; ++j) {
            free(pBoxTypes[j]);
        }
        free(pBoxTypes);
        pBoxTypes = NULL;
    }

    return EXIT_SUCCESS;
}
