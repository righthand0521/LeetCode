#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check(int* tops, int topsSize, int* bottoms, int bottomsSize, int x) {
    int retVal = -1;

    int rotationsTops = 0;
    int rotationsBottoms = 0;
    for (int i = 0; i < topsSize; i++) {
        if ((tops[i] != x) && (bottoms[i] != x)) {  // rotations couldn't be done
            return retVal;
        }

        if (tops[i] != x) {  // tops[i] != x and bottoms[i] == x
            rotationsTops++;
        } else if (bottoms[i] != x) {  // tops[i] == x and bottoms[i] != x
            rotationsBottoms++;
        }
    }
    // min number of rotations to have all elements equal to x in tops or bottoms
    retVal = fmin(rotationsTops, rotationsBottoms);

    return retVal;
}
int minDominoRotations(int* tops, int topsSize, int* bottoms, int bottomsSize) {
    int retVal = 0;

    int rotations = check(tops, topsSize, bottoms, bottomsSize, tops[0]);
    // If one could make all elements in tops or bottoms equal to tops[0]
    // Else one could make all elements in tops or bottoms equal to bottoms[0]
    if ((rotations != -1) || (tops[0] == bottoms[0])) {
        return rotations;
    } else {
        retVal = check(tops, topsSize, bottoms, bottomsSize, bottoms[0]);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(2 * 10000)
    struct testCaseType {
        int tops[MAX_SIZE];
        int topsSize;
        int bottoms[MAX_SIZE];
        int bottomsSize;
    } testCase[] = {{{2, 1, 2, 4, 2, 2}, 6, {5, 2, 6, 2, 3, 2}, 6}, {{3, 5, 1, 2, 3}, 5, {3, 6, 3, 3, 4}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
     *  Output: 2
     *
     *  Input: tops = [3,5,1,2,3], bottoms = [3,6,3,3,4]
     *  Output: -1
     */

    int i, j;
    int answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: tops = [");
        for (j = 0; j < testCase[i].topsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].tops[j]);
        }
        printf("], bottoms = [");
        for (j = 0; j < testCase[i].bottomsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].bottoms[j]);
        }
        printf("]\n");

        answer =
            minDominoRotations(testCase[i].tops, testCase[i].topsSize, testCase[i].bottoms, testCase[i].bottomsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
