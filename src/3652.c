#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long maxProfit(int* prices, int pricesSize, int* strategy, int strategySize, int k) {
    long long retVal = 0;

    long long profitSum[pricesSize + 1];
    memset(profitSum, 0, sizeof(profitSum));
    long long priceSum[pricesSize + 1];
    memset(priceSum, 0, sizeof(priceSum));

    for (int i = 0; i < pricesSize; i++) {
        profitSum[i + 1] = profitSum[i] + (long long)prices[i] * strategy[i];
        priceSum[i + 1] = priceSum[i] + prices[i];
    }
    retVal = profitSum[pricesSize];

    long long leftProfit, rightProfit, changeProfit, total;
    for (int i = k - 1; i < pricesSize; i++) {
        leftProfit = profitSum[i - k + 1];
        rightProfit = profitSum[pricesSize] - profitSum[i + 1];
        changeProfit = priceSum[i + 1] - priceSum[i - k / 2 + 1];
        total = leftProfit + changeProfit + rightProfit;
        if (total > retVal) {
            retVal = total;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int prices[MAX_SIZE];
        int pricesSize;
        int strategy[MAX_SIZE];
        int strategySize;
        int k;
    } testCase[] = {{{4, 2, 8}, 3, {-1, 0, 1}, 3, 2}, {{5, 4, 3}, 3, {1, 1, 0}, 3, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: prices = [4,2,8], strategy = [-1,0,1], k = 2
     *  Output: 10
     *
     *  Input: prices = [5,4,3], strategy = [1,1,0], k = 2
     *  Output: 9
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: prices = [");
        for (j = 0; j < testCase[i].pricesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].prices[j]);
        }
        printf("], strategy = [");
        for (j = 0; j < testCase[i].strategySize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].strategy[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = maxProfit(testCase[i].prices, testCase[i].pricesSize, testCase[i].strategy, testCase[i].strategySize,
                           testCase[i].k);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
