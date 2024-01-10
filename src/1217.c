#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minCostToMoveChips(int* position, int positionSize) {
    int retVal = 0;

    int odd = 0;
    int even = 0;
    int i;
    for (i = 0; i < positionSize; ++i) {
        if (position[i] % 2 == 0) {
            ++even;
        } else if (position[i] % 2 == 1) {
            ++odd;
        }
    }
    retVal = ((odd < even) ? odd : even);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int position[MAX_SIZE];
        int positionSize;
    } testCase[] = {{{1, 2, 3}, 3}, {{2, 2, 2, 3, 3}, 5}, {{1, 1000000000}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: position = [");
        for (j = 0; j < testCase[i].positionSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].position[j]);
        }
        printf("]\n");

        answer = minCostToMoveChips(testCase[i].position, testCase[i].positionSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}