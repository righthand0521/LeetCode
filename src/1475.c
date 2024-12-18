#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *finalPrices(int *prices, int pricesSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int *)malloc(pricesSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (pricesSize * sizeof(int)));
    memcpy(pRetVal, prices, (pricesSize * sizeof(int)));
    (*returnSize) = pricesSize;

    int monotonicStackTop = -1;
    int monotonicStack[pricesSize];
    memset(monotonicStack, 0, sizeof(monotonicStack));
    for (int i = 0; i < pricesSize; ++i) {
        // Process items that can be discounted by current price
        while ((monotonicStackTop != -1) && (prices[monotonicStack[monotonicStackTop]] >= prices[i])) {
            // Apply discount to previous item using current price
            pRetVal[monotonicStack[monotonicStackTop]] -= prices[i];
            monotonicStack[monotonicStackTop--] = 0;
        }

        // Add current index to monotonicStack
        monotonicStack[++monotonicStackTop] = i;
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int prices[MAX_SIZE];
        int pricesSize;
        int returnSize;
    } testCase[] = {{{8, 4, 6, 2, 3}, 5, 0}, {{1, 2, 3, 4, 5}, 5, 0}, {{10, 1, 1, 6}, 4, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: prices = [8,4,6,2,3]
     *  Output: [4,2,4,2,3]
     *
     *  Input: prices = [1,2,3,4,5]
     *  Output: [1,2,3,4,5]
     *
     *  Input: prices = [10,1,1,6]
     *  Output: [9,0,1,6]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: prices = [");
        for (j = 0; j < testCase[i].pricesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].prices[j]);
        }
        printf("]\n");

        pAnswer = finalPrices(testCase[i].prices, testCase[i].pricesSize, &testCase[i].returnSize);
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
