#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxProfit(int* prices, int pricesSize) {
    int retVal = 0;

    if (pricesSize == 0) {
        return retVal;
    }

    int dpBuy = -(prices[0]);
    int dpCooldown = 0;
    int dpSell = 0;
    int tmpBuy, tmpCooldown, tmpSell;
    int i;
    for (i = 1; i < pricesSize; ++i) {
        tmpBuy = fmax(dpBuy, dpSell - prices[i]);
        tmpCooldown = dpBuy + prices[i];
        tmpSell = fmax(dpCooldown, dpSell);

        dpBuy = tmpBuy;
        dpCooldown = tmpCooldown;
        dpSell = tmpSell;
    }
    retVal = fmax(dpCooldown, dpSell);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5000)
    struct testCaseType {
        int prices[MAX_SIZE];
        int pricesSize;
    } testCase[] = {{{1, 2, 3, 0, 2}, 5}, {{1}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: prices = [1,2,3,0,2]
     *  Output: 3
     *
     *  Input: prices = [1]
     *  Output: 0
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = [");
        for (j = 0; j < testCase[i].pricesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].prices[j]);
        }
        printf("]\n");

        answer = maxProfit(testCase[i].prices, testCase[i].pricesSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
