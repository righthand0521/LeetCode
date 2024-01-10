#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxProfit(int k, int* prices, int pricesSize) {
    int retVal = 0;

    int i, j;

    int buy[k + 1];
    int sell[k + 1];
    for (i = 0; i <= k; ++i) {
        buy[i] = -(prices[0]);
        sell[i] = 0;
    }

    int dpBuy[k + 1];
    int dpSell[k + 1];
    for (i = 1; i < pricesSize; ++i) {
        memset(dpBuy, 0, sizeof(dpBuy));
        memset(dpSell, 0, sizeof(dpSell));
        for (j = 1; j <= k; ++j) {
            dpBuy[j] = fmax(buy[j], sell[j - 1] - prices[i]);
            dpSell[j] = fmax(sell[j], buy[j] + prices[i]);
        }

        for (j = 0; j <= k; ++j) {
            buy[j] = dpBuy[j];
            sell[j] = dpSell[j];
        }
    }
    retVal = sell[k];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int k;
        int prices[MAX_SIZE];
        int pricesSize;
    } testCase[] = {{2, {2, 4, 1}, 3}, {2, {3, 2, 6, 5, 0, 3}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: k = 2, prices = [2,4,1]
     *  Output: 2
     *
     *  Input: k = 2, prices = [3,2,6,5,0,3]
     *  Output: 7
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: k = %d, prices = [", testCase[i].k);
        for (j = 0; j < testCase[i].pricesSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].prices[j]);
        }
        printf("]\n");

        answer = maxProfit(testCase[i].k, testCase[i].prices, testCase[i].pricesSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
