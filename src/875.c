#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minEatingSpeed(int *piles, int pilesSize, int h) {
    int retVal = 0;

    int i;

    int left = 1;
    int right = 0;
    for (i = 0; i < pilesSize; ++i) {
        right = fmax(right, piles[i]);
    }

    int useHour;
    int middle;
    while (left < right) {
        middle = left + (right - left) / 2;

        useHour = 0;
        for (i = 0; i < pilesSize; ++i) {
            // ceiling of an integer division
            useHour += ((piles[i] + middle - 1) / middle);
        }
        if (useHour > h) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int piles[MAX_SIZE];
        int pilesSize;
        int h;
    } testCase[] = {{{3, 6, 7, 11}, 4, 8}, {{30, 11, 23, 4, 20}, 5, 5}, {{30, 11, 23, 4, 20}, 5, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: piles = [3,6,7,11], h = 8
     *  Output: 4
     *
     *  Input: piles = [30,11,23,4,20], h = 5
     *  Output: 30
     *
     *  Input: piles = [30,11,23,4,20], h = 6
     *  Output: 23
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: piles = [");
        for (j = 0; j < testCase[i].pilesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].piles[j]);
        }
        printf("], h = %d\n", testCase[i].h);

        answer = minEatingSpeed(testCase[i].piles, testCase[i].pilesSize, testCase[i].h);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
