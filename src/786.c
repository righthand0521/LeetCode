#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *kthSmallestPrimeFraction(int *arr, int arrSize, int k, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 2;
    pRetVal = (int *)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    int i, j;
    double maxFraction, fraction;
    int totalSmallerFractions, numeratorIdx, denominatorIdx;
    double middle;
    double left = 0;
    double right = 1.0;
    while (left < right) {
        middle = (left + right) / 2;

        maxFraction = 0.0;
        totalSmallerFractions = 0;
        numeratorIdx = 0;
        denominatorIdx = 0;
        j = 1;
        for (i = 0; i < (arrSize - 1); ++i) {
            while ((j < arrSize) && (arr[i] >= middle * arr[j])) {
                j += 1;
            }

            totalSmallerFractions += (arrSize - j);

            if (j == arrSize) {
                break;
            }

            fraction = (double)(arr[i]) / arr[j];
            if (fraction > maxFraction) {
                numeratorIdx = i;
                denominatorIdx = j;
                maxFraction = fraction;
            }
        }

        if (totalSmallerFractions == k) {
            pRetVal[0] = arr[numeratorIdx];
            pRetVal[1] = arr[denominatorIdx];
            break;
        } else if (totalSmallerFractions > k) {
            right = middle;
        } else {
            left = middle;
        }
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
        int k;
        int returnSize;
    } testCase[] = {{{1, 2, 3, 5}, 4, 3, 0}, {{1, 7}, 2, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [1,2,3,5], k = 3
     *  Output: [2,5]
     *
     *  Input: arr = [1,7], k = 1
     *  Output: [1,7]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        pAnswer =
            kthSmallestPrimeFraction(testCase[i].arr, testCase[i].arrSize, testCase[i].k, &testCase[i].returnSize);
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
