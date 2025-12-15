#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long getDescentPeriods(int* prices, int pricesSize) {
    long long retVal = 1;  // total number of smooth descending periods, initial value is dp[0]

    // total number of smooth descending periods ending with the previous element, initial value is dp[0]
    int prev = 1;
    // traverse the array starting from 1, and update prev and the total res according to the recurrence relation
    for (int i = 1; i < pricesSize; ++i) {
        if (prices[i] == prices[i - 1] - 1) {
            ++prev;
        } else {
            prev = 1;
        }
        retVal += prev;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int prices[MAX_SIZE];
        int pricesSize;
    } testCase[] = {{{3, 2, 1, 4}, 4}, {{8, 6, 7, 7}, 4}, {{1}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: prices = [3,2,1,4]
     *  Output: 7
     *
     *  Input: prices = [8,6,7,7]
     *  Output: 4
     *
     *  Input: prices = [1]
     *  Output: 1
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: prices = [");
        for (j = 0; j < testCase[i].pricesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].prices[j]);
        }
        printf("]\n");

        answer = getDescentPeriods(testCase[i].prices, testCase[i].pricesSize);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
