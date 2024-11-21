#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void markUnguarded(int row, int col, int** grid, int gridSize, int gridColSize) {
    int x;
    for (x = row - 1; x >= 0; x--) {
        if ((grid[x][col] == 3) || (grid[x][col] == 2)) {
            break;
        }
        grid[x][col] = 1;
    }
    for (x = row + 1; x < gridSize; x++) {
        if ((grid[x][col] == 3) || (grid[x][col] == 2)) {
            break;
        }
        grid[x][col] = 1;
    }

    int y;
    for (y = col - 1; y >= 0; y--) {
        if ((grid[row][y] == 3) || (grid[row][y] == 2)) {
            break;
        }
        grid[row][y] = 1;
    }
    for (y = col + 1; y < gridColSize; y++) {
        if ((grid[row][y] == 3) || (grid[row][y] == 2)) {
            break;
        }
        grid[row][y] = 1;
    }
}
int countUnguarded(int m, int n, int** guards, int guardsSize, int* guardsColSize, int** walls, int wallsSize,
                   int* wallsColSize) {
    int retVal = 0;

    int i, j;

    int** pGrid = (int**)malloc(m * sizeof(int*));
    if (pGrid == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(pGrid, 0, (m * sizeof(int*)));
    for (i = 0; i < m; ++i) {
        pGrid[i] = (int*)malloc(n * sizeof(int));
        if (pGrid[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++i) {
                free(pGrid[j]);
                pGrid[j] = NULL;
            }
            free(pGrid);
            pGrid = NULL;
            return retVal;
        }
        memset(pGrid[i], 0, (n * sizeof(int)));
    }

    for (i = 0; i < guardsSize; ++i) {
        pGrid[guards[i][0]][guards[i][1]] = 2;
    }
    for (i = 0; i < wallsSize; ++i) {
        pGrid[walls[i][0]][walls[i][1]] = 3;
    }

    for (i = 0; i < guardsSize; ++i) {
        markUnguarded(guards[i][0], guards[i][1], pGrid, m, n);
    }

    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            if (pGrid[i][j] == 0) {
                retVal++;
            }
        }
    }

    //
    for (i = 0; i < m; ++i) {
        free(pGrid[i]);
        pGrid[i] = NULL;
    }
    free(pGrid);
    pGrid = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int m;
        int n;
        int guards[MAX_SIZE][2];
        int guardsSize;
        int guardsColSize[MAX_SIZE];
        int walls[MAX_SIZE][2];
        int wallsSize;
        int wallsColSize[MAX_SIZE];
    } testCase[] = {{4, 6, {{0, 0}, {1, 1}, {2, 3}}, 3, {2, 2, 2}, {{0, 1}, {2, 2}, {1, 4}}, 3, {2, 2, 2}},
                    {3, 3, {{1, 1}}, 1, {2}, {{0, 1}, {1, 0}, {2, 1}, {1, 2}}, 4, {2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: m = 4, n = 6, guards = [[0,0],[1,1],[2,3]], walls = [[0,1],[2,2],[1,4]]
     *  Output: 7
     *
     *  Input: m = 3, n = 3, guards = [[1,1]], walls = [[0,1],[1,0],[2,1],[1,2]]
     *  Output: 4
     */

    int** pGuards = NULL;
    int** pWalls = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: m = %d, n = %d, guards = [", testCase[i].m, testCase[i].n);
        for (j = 0; j < testCase[i].guardsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].guardsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].guards[j][k]);
            }
            printf("]");
        }
        printf("], walls = [");
        for (j = 0; j < testCase[i].wallsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].wallsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].walls[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pGuards = (int**)malloc(testCase[i].guardsSize * sizeof(int*));
        if (pGuards == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        memset(pGuards, 0, testCase[i].guardsSize * sizeof(int*));
        for (j = 0; j < testCase[i].guardsSize; ++j) {
            pGuards[j] = (int*)malloc(testCase[i].guardsColSize[j] * sizeof(int));
            if (pGuards[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pGuards[k]);
                    pGuards[k] = NULL;
                }
                free(pGuards);
                pGuards = NULL;
                return EXIT_FAILURE;
            }
            memset(pGuards[j], 0, (testCase[i].guardsColSize[j] * sizeof(int)));
            memcpy(pGuards[j], testCase[i].guards[j], (testCase[i].guardsColSize[j] * sizeof(int)));
        }
        pWalls = (int**)malloc(testCase[i].wallsSize * sizeof(int*));
        if (pWalls == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        memset(pWalls, 0, testCase[i].wallsSize * sizeof(int*));
        for (j = 0; j < testCase[i].wallsSize; ++j) {
            pWalls[j] = (int*)malloc(testCase[i].wallsColSize[j] * sizeof(int));
            if (pWalls[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pWalls[k]);
                    pWalls[k] = NULL;
                }
                free(pWalls);
                pWalls = NULL;
                return EXIT_FAILURE;
            }
            memset(pWalls[j], 0, (testCase[i].wallsColSize[j] * sizeof(int)));
            memcpy(pWalls[j], testCase[i].walls[j], (testCase[i].wallsColSize[j] * sizeof(int)));
        }

        answer = countUnguarded(testCase[i].m, testCase[i].n, pGuards, testCase[i].guardsSize,
                                testCase[i].guardsColSize, pWalls, testCase[i].wallsSize, testCase[i].wallsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].guardsSize; ++j) {
            free(pGuards[j]);
            pGuards[j] = NULL;
        }
        free(pGuards);
        pGuards = NULL;
        for (j = 0; j < testCase[i].wallsSize; ++j) {
            free(pWalls[j]);
            pWalls[j] = NULL;
        }
        free(pWalls);
        pWalls = NULL;
    }

    return EXIT_SUCCESS;
}
