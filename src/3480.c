#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long maxSubarrays(int n, int **conflictingPairs, int conflictingPairsSize, int *conflictingPairsColSize) {
    long long retVal = 0;

    int *bMin1 = (int *)malloc((n + 1) * sizeof(int));
    if (bMin1 == NULL) {
        perror("malloc");
        return retVal;
    }
    int *bMin2 = (int *)malloc((n + 1) * sizeof(int));
    if (bMin2 == NULL) {
        perror("malloc");
        free(bMin1);
        return retVal;
    }
    for (int i = 0; i <= n; i++) {
        bMin1[i] = INT_MAX;
        bMin2[i] = INT_MAX;
    }
    int a, b;
    for (int i = 0; i < conflictingPairsSize; i++) {
        a = fmin(conflictingPairs[i][0], conflictingPairs[i][1]);
        b = fmax(conflictingPairs[i][0], conflictingPairs[i][1]);
        if (bMin1[a] > b) {
            bMin2[a] = bMin1[a];
            bMin1[a] = b;
        } else if (bMin2[a] > b) {
            bMin2[a] = b;
        }
    }

    long long *delCount = (long long *)calloc(n + 1, sizeof(long long));
    if (delCount == NULL) {
        perror("malloc");
        free(bMin1);
        free(bMin2);
        return retVal;
    }
    int ib1 = n;
    int b2 = INT_MAX;
    for (int i = n; i >= 1; i--) {
        if (bMin1[ib1] > bMin1[i]) {
            b2 = fmin(b2, bMin1[ib1]);
            ib1 = i;
        } else {
            b2 = fmin(b2, bMin1[i]);
        }
        retVal += (fmin(bMin1[ib1], n + 1) - i);
        delCount[ib1] += (fmin(fmin(b2, bMin2[ib1]), n + 1) - fmin(bMin1[ib1], n + 1));
    }
    long long max = 0;
    for (int i = 0; i <= n; i++) {
        if (delCount[i] > max) {
            max = delCount[i];
        }
    }
    retVal += max;

    //
    free(bMin1);
    free(bMin2);
    free(delCount);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(2 * 100000)
    struct testCaseType {
        int n;
        int conflictingPairs[MAX_SIZE][2];
        int conflictingPairsSize;
        int conflictingPairsColSize[MAX_SIZE];
    } testCase[] = {{4, {{2, 3}, {1, 4}}, 2, {2, 2}}, {5, {{1, 2}, {2, 5}, {3, 5}}, 3, {2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 4, conflictingPairs = [[2,3],[1,4]]
     *  Output: 9
     *
     *  Input: n = 5, conflictingPairs = [[1,2],[2,5],[3,5]]
     *  Output: 12
     */

    int **pConflictingPairs = NULL;
    long long answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, conflictingPairs = [", testCase[i].n);
        for (j = 0; j < testCase[i].conflictingPairsSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].conflictingPairsColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].conflictingPairs[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pConflictingPairs = (int **)malloc(testCase[i].conflictingPairsSize * sizeof(int *));
        if (pConflictingPairs == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].conflictingPairsSize; ++j) {
            pConflictingPairs[j] = (int *)malloc(testCase[i].conflictingPairsColSize[j] * sizeof(int));
            if (pConflictingPairs[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pConflictingPairs[k]) {
                        free(pConflictingPairs[k]);
                        pConflictingPairs[k] = NULL;
                    }
                }
                free(pConflictingPairs);
                pConflictingPairs = NULL;
                return EXIT_FAILURE;
            }
            memset(pConflictingPairs[j], 0, testCase[i].conflictingPairsColSize[j] * sizeof(int));
            memcpy(pConflictingPairs[j], testCase[i].conflictingPairs[j],
                   testCase[i].conflictingPairsColSize[j] * sizeof(int));
        }
        answer = maxSubarrays(testCase[i].n, pConflictingPairs, testCase[i].conflictingPairsSize,
                              testCase[i].conflictingPairsColSize);

        printf("Output: %lld\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].conflictingPairsSize; ++j) {
            if (pConflictingPairs[j]) {
                free(pConflictingPairs[j]);
                pConflictingPairs[j] = NULL;
            }
        }
        free(pConflictingPairs);
        pConflictingPairs = NULL;
    }

    return EXIT_SUCCESS;
}
