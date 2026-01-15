#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maximizeSquareHoleArea(int n, int m, int* hBars, int hBarsSize, int* vBars, int vBarsSize) {
    int retVal = 0;

    qsort(hBars, hBarsSize, sizeof(int), compareInteger);
    int hmax = 1;
    int hcur = 1;
    for (int i = 1; i < hBarsSize; i++) {
        if (hBars[i] == hBars[i - 1] + 1) {
            hcur++;
        } else {
            hcur = 1;
        }
        hmax = fmax(hmax, hcur);
    }

    qsort(vBars, vBarsSize, sizeof(int), compareInteger);
    int vmax = 1;
    int vcur = 1;
    for (int i = 1; i < vBarsSize; i++) {
        if (vBars[i] == vBars[i - 1] + 1) {
            vcur++;
        } else {
            vcur = 1;
        }
        vmax = fmax(vmax, vcur);
    }

    int side = fmin(hmax, vmax) + 1;
    retVal = side * side;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int n;
        int m;
        int hBars[MAX_SIZE];
        int hBarsSize;
        int vBars[MAX_SIZE];
        int vBarsSize;
    } testCase[] = {{2, 1, {2, 3}, 2, {2}, 1}, {1, 1, {2}, 1, {2}, 1}, {2, 3, {2, 3}, 2, {2, 4}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 2, m = 1, hBars = [2,3], vBars = [2]
     *  Output: 4
     *
     *  Input: n = 1, m = 1, hBars = [2], vBars = [2]
     *  Output: 4
     *
     *  Input: n = 2, m = 3, hBars = [2,3], vBars = [2,4]
     *  Output: 4
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, m = %d, hBars = [", testCase[i].n, testCase[i].m);
        for (j = 0; j < testCase[i].hBarsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].hBars[j]);
        }
        printf("], vBars = [");
        for (j = 0; j < testCase[i].vBarsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].vBars[j]);
        }
        printf("]\n");

        answer = maximizeSquareHoleArea(testCase[i].n, testCase[i].m, testCase[i].hBars, testCase[i].hBarsSize,
                                        testCase[i].vBars, testCase[i].vBarsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
