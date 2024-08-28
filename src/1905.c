#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool dfs(int x, int y, int** grid1, int** grid2, int grid2Size, int* grid2ColSize, int** visited) {
    bool retVal = true;

    if (grid1[x][y] != 1) {
        retVal = false;
    }

    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int rowSize = grid2Size;
    int colSize = grid2ColSize[0];
    int nextX, nextY;
    bool nextCellIsPartOfSubIsland;
    int i;
    for (i = 0; i < 4; ++i) {
        nextX = x + directions[i][0];
        nextY = y + directions[i][1];
        if ((nextX < 0) || (nextX >= rowSize)) {
            continue;
        } else if ((nextY < 0) || (nextY >= colSize)) {
            continue;
        }

        if (visited[nextX][nextY] == 1) {
            continue;
        } else if (grid2[nextX][nextY] != 1) {
            continue;
        }

        visited[nextX][nextY] = 1;
        nextCellIsPartOfSubIsland = dfs(nextX, nextY, grid1, grid2, grid2Size, grid2ColSize, visited);
        retVal = retVal && nextCellIsPartOfSubIsland;
    }

    return retVal;
}
int countSubIslands(int** grid1, int grid1Size, int* grid1ColSize, int** grid2, int grid2Size, int* grid2ColSize) {
    int retVal = 0;

    int rowSize = grid2Size;
    int colSize = grid2ColSize[0];
    int x, y;

    int** visited = (int**)malloc(rowSize * sizeof(int*));
    if (visited == NULL) {
        perror("malloc");
        return retVal;
    }
    for (x = 0; x < rowSize; ++x) {
        visited[x] = (int*)malloc(colSize * sizeof(int));
        if (visited[x] == NULL) {
            perror("malloc");
            for (y = 0; y < x; ++y) {
                free(visited[y]);
                visited[y] = NULL;
            }
            free(visited);
            visited = NULL;
            return retVal;
        }
        memset(visited[x], 0, (colSize * sizeof(int)));
    }

    for (x = 0; x < rowSize; ++x) {
        for (y = 0; y < colSize; ++y) {
            if (visited[x][y] == 1) {
                continue;
            } else if (grid2[x][y] != 1) {
                continue;
            }

            visited[x][y] = 1;
            if (dfs(x, y, grid1, grid2, grid2Size, grid2ColSize, visited) == true) {
                retVal += 1;
            }
        }
    }

    //
    for (x = 0; x < rowSize; ++x) {
        free(visited[x]);
        visited[x] = NULL;
    }
    free(visited);
    visited = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int grid1[MAX_SIZE][MAX_SIZE];
        int grid1Size;
        int grid1ColSize[MAX_SIZE];
        int grid2[MAX_SIZE][MAX_SIZE];
        int grid2Size;
        int grid2ColSize[MAX_SIZE];
    } testCase[] = {{{{1, 1, 1, 0, 0}, {0, 1, 1, 1, 1}, {0, 0, 0, 0, 0}, {1, 0, 0, 0, 0}, {1, 1, 0, 1, 1}},
                     5,
                     {5, 5, 5, 5, 5},
                     {{1, 1, 1, 0, 0}, {0, 0, 1, 1, 1}, {0, 1, 0, 0, 0}, {1, 0, 1, 1, 0}, {0, 1, 0, 1, 0}},
                     5,
                     {5, 5, 5, 5, 5}},
                    {{{1, 0, 1, 0, 1}, {1, 1, 1, 1, 1}, {0, 0, 0, 0, 0}, {1, 1, 1, 1, 1}, {1, 0, 1, 0, 1}},
                     5,
                     {5, 5, 5, 5, 5},
                     {{0, 0, 0, 0, 0}, {1, 1, 1, 1, 1}, {0, 1, 0, 1, 0}, {0, 1, 0, 1, 0}, {1, 0, 0, 0, 1}},
                     5,
                     {5, 5, 5, 5, 5}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid1 = [[1,1,1,0,0],[0,1,1,1,1],[0,0,0,0,0],[1,0,0,0,0],[1,1,0,1,1]],
     *  grid2 = [[1,1,1,0,0],[0,0,1,1,1],[0,1,0,0,0],[1,0,1,1,0],[0,1,0,1,0]]
     *  Output: 3
     *
     *  Input: grid1 = [[1,0,1,0,1],[1,1,1,1,1],[0,0,0,0,0],[1,1,1,1,1],[1,0,1,0,1]],
     *  grid2 = [[0,0,0,0,0],[1,1,1,1,1],[0,1,0,1,0],[0,1,0,1,0],[1,0,0,0,1]]
     *  Output: 2
     */

    int** pGrid1 = NULL;
    int** pGrid2 = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: grid1 = [");
        for (j = 0; j < testCase[i].grid1Size; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].grid1ColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].grid1[j][k]);
            }
            printf("]");
        }
        printf("], grid2 = [");
        for (j = 0; j < testCase[i].grid2Size; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].grid2ColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].grid2[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pGrid1 = (int**)malloc(testCase[i].grid1Size * sizeof(int*));
        if (pGrid1 == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].grid1Size; ++j) {
            pGrid1[j] = malloc(testCase[i].grid1ColSize[j] * sizeof(int));
            if (pGrid1[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pGrid1[k]);
                    pGrid1[k] = NULL;
                }
                free(pGrid1);
                pGrid1 = NULL;
                return EXIT_FAILURE;
            }
            memset(pGrid1[j], 0, (testCase[i].grid1ColSize[j] * sizeof(int)));
            memcpy(pGrid1[j], testCase[i].grid1[j], (testCase[i].grid1ColSize[j] * sizeof(int)));
        }
        pGrid2 = (int**)malloc(testCase[i].grid2Size * sizeof(int*));
        if (pGrid2 == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].grid2Size; ++j) {
            pGrid2[j] = malloc(testCase[i].grid2ColSize[j] * sizeof(int));
            if (pGrid2[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pGrid2[k]);
                    pGrid2[k] = NULL;
                }
                free(pGrid2);
                pGrid2 = NULL;
                return EXIT_FAILURE;
            }
            memset(pGrid2[j], 0, (testCase[i].grid2ColSize[j] * sizeof(int)));
            memcpy(pGrid2[j], testCase[i].grid2[j], (testCase[i].grid2ColSize[j] * sizeof(int)));
        }
        answer = countSubIslands(pGrid1, testCase[i].grid1Size, testCase[i].grid1ColSize, pGrid2, testCase[i].grid2Size,
                                 testCase[i].grid2ColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].grid1Size; ++j) {
            free(pGrid1[j]);
            pGrid1[j] = NULL;
        }
        free(pGrid1);
        pGrid1 = NULL;
        for (j = 0; j < testCase[i].grid2Size; ++j) {
            free(pGrid2[j]);
            pGrid2[j] = NULL;
        }
        free(pGrid2);
        pGrid2 = NULL;
    }

    return EXIT_SUCCESS;
}
