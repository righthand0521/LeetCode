#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double champagneTower(int poured, int query_row, int query_glass) {
    double retVal = 0;

    int glassSize = 0;
    double glass[query_row + 2];
    memset(glass, 0, sizeof(glass));
    glass[glassSize++] = poured;

    double nextGlass[query_row + 2];
    double volume;
    int row, col;
    for (row = 0; row < query_row; ++row) {
        memset(nextGlass, 0, sizeof(nextGlass));
        for (col = 0; col < glassSize; ++col) {
            volume = glass[col];
            if (volume <= 1) {
                continue;
            }
            nextGlass[col] += (volume - 1) / 2;
            nextGlass[col + 1] += (volume - 1) / 2;
        }
        memset(glass, 0, sizeof(glass));
        memcpy(glass, nextGlass, sizeof(glass));
        glassSize++;
    }
    retVal = fmin(1.0, glass[query_glass]);

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int poured;
        int query_row;
        int query_glass;
    } testCase[] = {{1, 1, 1}, {2, 1, 1}, {100000009, 33, 17}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: poured = 1, query_row = 1, query_glass = 1
     *  Output: 0.00000
     *
     *  Input: poured = 2, query_row = 1, query_glass = 1
     *  Output: 0.50000
     *
     *  Input: poured = 100000009, query_row = 33, query_glass = 17
     *  Output: 1.00000
     */

    int i;
    double answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: poured = %d, query_row = %d, query_glass = %d\n", testCase[i].poured, testCase[i].query_row,
               testCase[i].query_glass);

        answer = champagneTower(testCase[i].poured, testCase[i].query_row, testCase[i].query_glass);
        printf("Output: %.5f\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
