#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int buyChoco(int* prices, int pricesSize, int money) {
    int retVal = money;

    qsort(prices, pricesSize, sizeof(int), compareInteger);
    int leftover = money - (prices[0] + prices[1]);
    if (leftover >= 0) {
        retVal = leftover;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50)
    struct testCaseType {
        int prices[MAX_SIZE];
        int pricesSize;
        int money;
    } testCase[] = {{{1, 2, 2}, 3, 3}, {{3, 2, 3}, 3, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: prices = [1,2,2], money = 3
     *  Output: 0
     *
     *  Input: prices = [3,2,3], money = 3
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: prices = [");
        for (j = 0; j < testCase[i].pricesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].prices[j]);
        }
        printf("], money = %d\n", testCase[i].money);

        answer = buyChoco(testCase[i].prices, testCase[i].pricesSize, testCase[i].money);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
