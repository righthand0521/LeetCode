#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numWaterBottles(int numBottles, int numExchange) {
    int retVal = 0;

    int times;
    int consumedBottles = 0;
    while (numBottles >= numExchange) {
        times = numBottles / numExchange;
        consumedBottles += (numExchange * times);
        numBottles -= (numExchange * times);
        numBottles += times;
    }
    retVal = consumedBottles + numBottles;

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int numBottles;
        int numExchange;
    } testCase[] = {{9, 3}, {15, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: numBottles = 9, numExchange = 3
     *  Output: 13
     *
     *  Input: numBottles = 15, numExchange = 4
     *  Output: 19
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: numBottles = %d, numExchange = %d\n", testCase[i].numBottles, testCase[i].numExchange);

        answer = numWaterBottles(testCase[i].numBottles, testCase[i].numExchange);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
