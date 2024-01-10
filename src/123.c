#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxProfit(int* prices, int pricesSize) {
    int retVal = 0;

    int buy1 = -(prices[0]);
    int sell1 = 0;
    int buy2 = -(prices[0]);
    int sell2 = 0;
    int i;
    for (i = 1; i < pricesSize; ++i) {
        int dpBuy1 = fmax(buy1, -(prices[i]));
        int dpSell1 = fmax(sell1, buy1 + prices[i]);
        int dpBuy2 = fmax(buy2, sell1 - prices[i]);
        int dpSell2 = fmax(sell2, buy2 + prices[i]);

        buy1 = dpBuy1;
        sell1 = dpSell1;
        buy2 = dpBuy2;
        sell2 = dpSell2;
    }
    retVal = sell2;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        int prices[MAX_SIZE];
        int pricesSize;
    } testCase[] = {{{3, 3, 5, 0, 0, 3, 1, 4}, 8}, {{1, 2, 3, 4, 5}, 5}, {{7, 6, 4, 3, 1}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: prices = [3,3,5,0,0,3,1,4]
     *  Output: 6
     *
     *  Input: prices = [1,2,3,4,5]
     *  Output: 4
     *
     *  Input: prices = [7,6,4,3,1]
     *  Output: 0
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
