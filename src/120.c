#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumTotal(int** triangle, int triangleSize, int* triangleColSize) {
    int retVal = 0;

    int dp[triangleSize][triangleSize];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = triangle[0][0];
    int i, j;
    for (i = 1; i < triangleSize; ++i) {
        dp[i][0] = dp[i - 1][0] + triangle[i][0];
        for (j = 1; j < i; ++j) {
            dp[i][j] = fmin(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
        }
        dp[i][i] = dp[i - 1][i - 1] + triangle[i][i];
    }

    retVal = dp[triangleSize - 1][0];
    for (i = 1; i < triangleSize; i++) {
        retVal = fmin(retVal, dp[triangleSize - 1][i]);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        int triangle[MAX_SIZE][MAX_SIZE];
        int triangleSize;
        int triangleColSize[MAX_SIZE];
    } testCase[] = {{{{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}}, 4, {1, 2, 3, 4}}, {{{-10}}, 1, {1}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pTriangle = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: triangle =  [");
        for (j = 0; j < testCase[i].triangleSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].triangleColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].triangle[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pTriangle = (int**)malloc(testCase[i].triangleSize * sizeof(int*));
        if (pTriangle == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].triangleSize; ++j) {
            pTriangle[j] = (int*)malloc(testCase[i].triangleColSize[j] * sizeof(int));
            if (pTriangle[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pTriangle[k]) {
                        free(pTriangle[k]);
                        pTriangle[k] = NULL;
                    }
                }
                free(pTriangle);
                pTriangle = NULL;
                return EXIT_FAILURE;
            }
            memset(pTriangle[j], 0, testCase[i].triangleColSize[j] * sizeof(int));
            memcpy(pTriangle[j], testCase[i].triangle[j], testCase[i].triangleColSize[j] * sizeof(int));
        }
        answer = minimumTotal(pTriangle, testCase[i].triangleSize, testCase[i].triangleColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].triangleSize; ++j) {
            if (pTriangle[j]) {
                free(pTriangle[j]);
                pTriangle[j] = NULL;
            }
        }
        free(pTriangle);
        pTriangle = NULL;
    }

    return EXIT_SUCCESS;
}
