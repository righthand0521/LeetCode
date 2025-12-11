#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countCoveredBuildings(int n, int** buildings, int buildingsSize, int* buildingsColSize) {
    int retVal = 0;

    int maxRow[n + 1];
    memset(maxRow, 0, sizeof(maxRow));
    int minRow[n + 1];
    memset(minRow, 0, sizeof(minRow));
    int maxCol[n + 1];
    memset(maxCol, 0, sizeof(maxCol));
    int minCol[n + 1];
    memset(minCol, 0, sizeof(minCol));
    for (int i = 0; i <= n; i++) {
        minRow[i] = n + 1;
        minCol[i] = n + 1;
    }
    for (int i = 0; i < buildingsSize; i++) {
        int x = buildings[i][0];
        int y = buildings[i][1];
        maxRow[y] = fmax(maxRow[y], x);
        minRow[y] = fmin(minRow[y], x);
        maxCol[x] = fmax(maxCol[x], y);
        minCol[x] = fmin(minCol[x], y);
    }

    for (int i = 0; i < buildingsSize; i++) {
        int x = buildings[i][0];
        int y = buildings[i][1];
        if ((x > minRow[y]) && (x < maxRow[y]) && (y > minCol[x]) && (y < maxCol[x])) {
            retVal++;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW_SIZE (int)(1e5)
#define MAX_COL_SIZE (2)
    struct testCaseType {
        int n;
        int buildings[MAX_ROW_SIZE][MAX_COL_SIZE];
        int buildingsSize;
        int buildingsColSize[MAX_ROW_SIZE];
    } testCase[] = {{3, {{1, 2}, {2, 2}, {3, 2}, {2, 1}, {2, 3}}, 5, {2, 2, 2, 2, 2}},
                    {3, {{1, 1}, {1, 2}, {2, 1}, {2, 2}}, 4, {2, 2, 2, 2}},
                    {5, {{1, 3}, {3, 2}, {3, 3}, {3, 5}, {5, 3}}, 5, {2, 2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3, buildings = [[1,2],[2,2],[3,2],[2,1],[2,3]]
     *  Output: 1
     *
     *  Input: n = 3, buildings = [[1,1],[1,2],[2,1],[2,2]]
     *  Output: 0
     *
     *  Input: n = 5, buildings = [[1,3],[3,2],[3,3],[3,5],[5,3]]
     *  Output: 1
     */

    int** pBuildings = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, buildings = [", testCase[i].n);
        for (j = 0; j < testCase[i].buildingsSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].buildingsColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].buildings[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pBuildings = (int**)malloc(testCase[i].buildingsSize * sizeof(int*));
        if (pBuildings == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].buildingsSize; ++j) {
            pBuildings[j] = (int*)malloc(testCase[i].buildingsColSize[j] * sizeof(int));
            if (pBuildings[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pBuildings[k]);
                    pBuildings[k] = NULL;
                }
                free(pBuildings);
                pBuildings = NULL;
                return EXIT_FAILURE;
            }
            memset(pBuildings[j], 0, (testCase[i].buildingsColSize[j] * sizeof(int)));
            memcpy(pBuildings[j], testCase[i].buildings[j], (testCase[i].buildingsColSize[j] * sizeof(int)));
        }
        answer =
            countCoveredBuildings(testCase[i].n, pBuildings, testCase[i].buildingsSize, testCase[i].buildingsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].buildingsSize; ++j) {
            free(pBuildings[j]);
            pBuildings[j] = NULL;
        }
        free(pBuildings);
        pBuildings = NULL;
    }

    return EXIT_SUCCESS;
}
