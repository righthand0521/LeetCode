#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxProfit(int* prices, int pricesSize, int fee) {
    int retVal = 0;

    int dpSell = 0;
    int dpBuy = -(prices[0]);
    int tmpSell, tmpBuy;
    int i;
    for (i = 1; i < pricesSize; ++i) {
        tmpSell = fmax(dpSell, (dpBuy + prices[i] - fee));
        tmpBuy = fmax(dpBuy, (dpSell - prices[i]));
        dpSell = tmpSell;
        dpBuy = tmpBuy;
    }
    retVal = dpSell;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int prices[MAX_SIZE];
        int pricesSize;
        int fee;
    } testCase[] = {{{1, 3, 2, 8, 4, 9}, 6, 2}, {{1, 3, 7, 5, 10, 3}, 6, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: prices = [1,3,2,8,4,9], fee = 2
     *  Output: 8
     *
     *  Input: prices = [1,3,7,5,10,3], fee = 3
     *  Output: 6
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: prices = [");
        for (j = 0; j < testCase[i].pricesSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].prices[j]);
        }
        printf("], fee = %d\n", testCase[i].fee);

        answer = maxProfit(testCase[i].prices, testCase[i].pricesSize, testCase[i].fee);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
