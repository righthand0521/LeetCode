#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Check if we can place 'm' balls at 'position' with each ball having at least 'x' gap.
bool canPlaceBalls(int x, int* position, int positionSize, int m) {
    bool retVal = false;

    // Place the first ball at the first position.
    int prevBallPos = position[0];
    int ballsPlaced = 1;

    // Iterate on each 'position' and place a ball there if we can place it.
    int currPos;
    int i;
    for (i = 1; i < positionSize && ballsPlaced < m; ++i) {
        currPos = position[i];

        // Check if we can place the ball at the current position.
        if (currPos - prevBallPos >= x) {
            ballsPlaced += 1;
            prevBallPos = currPos;
        }
    }
    // If all 'm' balls are placed, return 'true'.
    if (ballsPlaced == m) {
        retVal = true;
    }

    return retVal;
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maxDistance(int* position, int positionSize, int m) {
    int retVal = 0;

    qsort(position, positionSize, sizeof(int), compareInteger);

    // Initial search space.
    int middle;
    int low = 1;
    int high = ceil(position[positionSize - 1] / (m - 1.0));
    while (low <= high) {
        middle = low + (high - low) / 2;

        // If we can place all balls having a gap at least 'mid',
        if (canPlaceBalls(middle, position, positionSize, m)) {
            retVal = middle;   // then 'mid' can be our answer,
            low = middle + 1;  // and discard the left half search space.
        } else {
            high = middle - 1;  // Discard the right half search space.
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int position[MAX_SIZE];
        int positionSize;
        int m;
    } testCase[] = {{{1, 2, 3, 4, 7}, 5, 3}, {{5, 4, 3, 2, 1, 1000000000}, 6, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: position = [1,2,3,4,7], m = 3
     *  Output: 3
     *
     *  Input: position = [5,4,3,2,1,1000000000], m = 2
     *  Output: 999999999
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: position = [");
        for (j = 0; j < testCase[i].positionSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].position[j]);
        }
        printf("], m = %d\n", testCase[i].m);

        answer = maxDistance(testCase[i].position, testCase[i].positionSize, testCase[i].m);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
