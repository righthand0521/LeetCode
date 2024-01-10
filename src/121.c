#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxProfit(int* prices, int pricesSize) {
    int retVal = 0;

    int buy = prices[0];
    int sell = prices[0];
    int i;
    for (i = 1; i < pricesSize; ++i) {
        if (buy > prices[i]) {
            buy = prices[i];
            sell = prices[i];
            continue;
        }

        if (sell < prices[i]) {
            sell = prices[i];
        }

        retVal = fmax(retVal, sell - buy);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        int prices[MAX_SIZE];
        int pricesSize;
    } testCase[] = {{{7, 1, 5, 3, 6, 4}, 6}, {{7, 6, 4, 3, 1}, 5}, {{2, 4, 1}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: prices = [7,1,5,3,6,4]
     *  Output: 5
     *
     *  Input: prices = [7,6,4,3,1]
     *  Output: 0
     *
     *  Input: prices = [2, 4, 1]
     *  Output: 2
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: prices = [");
        for (j = 0; j < testCase[i].pricesSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].prices[j]);
        }
        printf("]\n");

        answer = maxProfit(testCase[i].prices, testCase[i].pricesSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
