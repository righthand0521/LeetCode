#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxBottlesDrunk(int numBottles, int numExchange) {
    int retVal = numBottles;

    for (int empty = numBottles; empty >= numExchange; numExchange++) {
        retVal++;
        empty -= (numExchange - 1);
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int numBottles;
        int numExchange;
    } testCase[] = {{13, 6}, {10, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: numBottles = 13, numExchange = 6
     *  Output: 15
     *
     *  Input: numBottles = 10, numExchange = 3
     *  Output: 13
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: numBottles = %d, numExchange = %d\n", testCase[i].numBottles, testCase[i].numExchange);

        answer = maxBottlesDrunk(testCase[i].numBottles, testCase[i].numExchange);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
