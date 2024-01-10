#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int compareIntArray(const void* pa, const void* pb) {
    const int* a = *(const int**)pa;
    const int* b = *(const int**)pb;

    // ascending order
    if ((a[0] == b[0]) && (a[1] == b[1])) {
        return a[2] - b[2];
    } else if (a[0] == b[0]) {
        return a[1] - b[1];
    } else {
        return a[0] - b[0];
    }
}
int maxHeight(int** cuboids, int cuboidsSize, int* cuboidsColSize) {
    int retVal = 0;

    int i, j;

    for (i = 0; i < cuboidsSize; ++i) {
        qsort(cuboids[i], cuboidsColSize[i], sizeof(int), compareInteger);
    }
    qsort(cuboids, cuboidsSize, sizeof(cuboids[0]), compareIntArray);

    int dp[cuboidsSize];
    memset(dp, 0, sizeof(dp));
    for (i = 0; i < cuboidsSize; ++i) {
        for (j = 0; j < i; ++j) {
            if ((cuboids[j][1] <= cuboids[i][1]) && (cuboids[j][2] <= cuboids[i][2])) {
                dp[i] = fmax(dp[i], dp[j]);
            }
        }
        dp[i] += cuboids[i][2];
        retVal = fmax(retVal, dp[i]);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int cuboids[MAX_SIZE][MAX_SIZE];
        int cuboidsSize;
        int cuboidsColSize[MAX_SIZE];
    } testCase[] = {
        {{{50, 45, 20}, {95, 37, 53}, {45, 23, 12}}, 3, {3, 3, 3}},
        {{{38, 25, 45}, {76, 35, 3}}, 2, {3, 3}},
        {{{7, 11, 17}, {7, 17, 11}, {11, 7, 17}, {11, 17, 7}, {17, 7, 11}, {17, 11, 7}}, 6, {3, 3, 3, 3, 3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pCuboids = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: cuboids = [");
        for (j = 0; j < testCase[i].cuboidsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].cuboidsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].cuboids[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pCuboids = (int**)malloc(testCase[i].cuboidsSize * sizeof(int*));
        if (pCuboids == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].cuboidsSize; ++j) {
            pCuboids[j] = (int*)malloc(testCase[i].cuboidsColSize[j] * sizeof(int));
            if (pCuboids[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pCuboids[k]);
                    pCuboids[k] = NULL;
                }
                free(pCuboids);
                pCuboids = NULL;
                return EXIT_FAILURE;
            }
            memset(pCuboids[j], 0, testCase[i].cuboidsColSize[j] * sizeof(int));
            memcpy(pCuboids[j], testCase[i].cuboids[j], testCase[i].cuboidsColSize[j] * sizeof(int));
        }
        answer = maxHeight(pCuboids, testCase[i].cuboidsSize, testCase[i].cuboidsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].cuboidsSize; ++j) {
            free(pCuboids[j]);
        }
        free(pCuboids);
        pCuboids = NULL;
    }

    return EXIT_SUCCESS;
}
