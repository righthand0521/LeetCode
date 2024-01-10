#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxValueOfCoins(int** piles, int pilesSize, int* pilesColSize, int k) {
    int retVal = 0;

    int i, j;

    int** prefixSum = (int**)malloc(pilesSize * sizeof(int*));
    if (prefixSum == NULL) {
        perror("malloc");
        return retVal;
    }
    int len;
    for (i = 0; i < pilesSize; ++i) {
        len = pilesColSize[i] + 1;
        prefixSum[i] = (int*)malloc(len * sizeof(int));
        if (prefixSum[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(prefixSum[j]);
                prefixSum[j] = NULL;
            }
            free(prefixSum);
            prefixSum = NULL;
            return retVal;
        }
        memset(prefixSum[i], 0, (len * sizeof(int)));
    }
    for (i = 0; i < pilesSize; ++i) {
        for (j = 1; j <= pilesColSize[i]; ++j) {
            prefixSum[i][j] = prefixSum[i][j - 1] + piles[i][j - 1];
        }
    }

    int dp[k + 1];
    memset(dp, 0, sizeof(dp));
    int sum_;
    int select;
    for (i = 0; i < pilesSize; ++i) {
        for (j = k; j >= 0; --j) {
            len = pilesColSize[i] + 1;
            for (select = 0; select < len; ++select) {
                sum_ = prefixSum[i][select];
                if (j - select >= 0) {
                    dp[j] = fmax(dp[j], dp[j - select] + sum_);
                }
            }
        }
    }
    retVal = dp[k];

    for (i = 0; i < pilesSize; ++i) {
        free(prefixSum[i]);
        prefixSum[i] = NULL;
    }
    free(prefixSum);
    prefixSum = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int piles[MAX_SIZE][MAX_SIZE];
        int pilesSize;
        int pilesColSize[MAX_SIZE];
        int k;
    } testCase[] = {{{{1, 100, 3}, {7, 8, 9}}, 2, {3, 3}, 2},
                    {{{100}, {100}, {100}, {100}, {100}, {100}, {1, 1, 1, 1, 1, 1, 700}}, 7, {1, 1, 1, 1, 1, 1, 7}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: piles = [[1,100,3],[7,8,9]], k = 2
     *  Output: 101
     *
     *  Input: piles = [[100],[100],[100],[100],[100],[100],[1,1,1,1,1,1,700]], k = 7
     *  Output: 706
     */

    int** pPiles = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: piles = [");
        for (j = 0; j < testCase[i].pilesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].pilesColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].piles[j][k]);
            }
            printf("]");
        }
        printf("], k = %d\n", testCase[i].k);

        pPiles = (int**)malloc(testCase[i].pilesSize * sizeof(int*));
        if (pPiles == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].pilesSize; ++j) {
            pPiles[j] = (int*)malloc(testCase[i].pilesColSize[j] * sizeof(int));
            if (pPiles[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pPiles[k]);
                    pPiles[k] = NULL;
                }
                free(pPiles);
                pPiles = NULL;
                return EXIT_FAILURE;
            }
            memset(pPiles[j], 0, (testCase[i].pilesColSize[j] * sizeof(int)));
            memcpy(pPiles[j], testCase[i].piles[j], (testCase[i].pilesColSize[j] * sizeof(int)));
        }
        answer = maxValueOfCoins(pPiles, testCase[i].pilesSize, testCase[i].pilesColSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].pilesSize; ++j) {
            free(pPiles[j]);
            pPiles[j] = NULL;
        }
        free(pPiles);
        pPiles = NULL;
    }

    return EXIT_SUCCESS;
}
