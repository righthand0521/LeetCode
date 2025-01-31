#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int dfs(int** grid, int gridSize, int* gridColSize, int islandId, int row, int col) {
    int retVal = 0;

    int rowSize = gridSize;
    int colSize = gridColSize[0];
    if ((row < 0) || (row >= rowSize) || (col < 0) || (col >= colSize)) {
        return retVal;
    }

    if (grid[row][col] != 1) {
        return retVal;
    }
    grid[row][col] = islandId;

    retVal = 1;
    retVal += dfs(grid, gridSize, gridColSize, islandId, row + 1, col);
    retVal += dfs(grid, gridSize, gridColSize, islandId, row - 1, col);
    retVal += dfs(grid, gridSize, gridColSize, islandId, row, col + 1);
    retVal += dfs(grid, gridSize, gridColSize, islandId, row, col - 1);

    return retVal;
}
int largestIsland(int** grid, int gridSize, int* gridColSize) {
    int retVal = 1;

    int rowSize = gridSize;
    int colSize = gridColSize[0];

    // // Step 1: Mark all islands and calculate their sizes
    struct hashTable* pIslandSizes = NULL;
    struct hashTable* pTemp;
    int islandId = 2;
    for (int row = 0; row < rowSize; ++row) {
        for (int col = 0; col < colSize; ++col) {
            if (grid[row][col] != 1) {
                continue;
            }

            pTemp = NULL;
            HASH_FIND_INT(pIslandSizes, &islandId, pTemp);
            if (pTemp == NULL) {
                pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
                if (pTemp == NULL) {
                    perror("malloc");
                    freeAll(pIslandSizes);
                    return retVal;
                }
                pTemp->key = islandId;
                pTemp->value = dfs(grid, gridSize, gridColSize, islandId, row, col);
                HASH_ADD_INT(pIslandSizes, key, pTemp);
            } else {
                pTemp->value = dfs(grid, gridSize, gridColSize, islandId, row, col);
            }
            ++islandId;
        }
    }

    int islandSizesSize = HASH_COUNT(pIslandSizes);
    if (islandSizesSize == 0) {  // If there are no islands, return 1
        return retVal;
    } else if (islandSizesSize == 1) {  // If the entire grid is one island, return its size or size + 1
        --islandId;

        pTemp = NULL;
        HASH_FIND_INT(pIslandSizes, &islandId, pTemp);
        if (pTemp != NULL) {
            retVal = pTemp->value;
            if (pTemp->value != rowSize * colSize) {
                retVal += 1;
            }
        }
        freeAll(pIslandSizes);

        return retVal;
    }

    // Step 2: Try converting every 0 to 1 and calculate the resulting island size
    const int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    struct hashTable* pNeighboringIslands = NULL;
    struct hashTable *pCurrent, *pNext;
    int x, y, gridValue = 0;
    int currentIslandSize;
    for (int row = 0; row < rowSize; ++row) {
        for (int col = 0; col < colSize; ++col) {
            if (grid[row][col] != 0) {
                continue;
            }

            for (int i = 0; i < 4; ++i) {
                x = row + directions[i][0];
                y = col + directions[i][1];
                if ((x < 0) || (x >= rowSize) || (y < 0) || (y >= colSize)) {
                    continue;
                } else if (grid[x][y] <= 1) {
                    continue;
                }
                gridValue = grid[x][y];

                pTemp = NULL;
                HASH_FIND_INT(pNeighboringIslands, &gridValue, pTemp);
                if (pTemp == NULL) {
                    pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
                    if (pTemp == NULL) {
                        perror("malloc");
                        freeAll(pNeighboringIslands);
                        freeAll(pIslandSizes);
                        return retVal;
                    }
                    pTemp->key = gridValue;
                    pTemp->value = gridValue;
                    HASH_ADD_INT(pNeighboringIslands, key, pTemp);
                }
            }

            // Sum the sizes of all unique neighboring islands
            currentIslandSize = 1;
            HASH_ITER(hh, pNeighboringIslands, pCurrent, pNext) {
                islandId = pNeighboringIslands->key;
                HASH_DEL(pNeighboringIslands, pCurrent);
                free(pCurrent);

                pTemp = NULL;
                HASH_FIND_INT(pIslandSizes, &islandId, pTemp);
                if (pTemp != NULL) {
                    currentIslandSize += pTemp->value;
                }
            }

            retVal = fmax(retVal, currentIslandSize);
        }
    }

    //
    freeAll(pIslandSizes);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (500)
#define MAX_COLUMN (500)
    struct testCaseType {
        int grid[MAX_ROW][MAX_COLUMN];
        int gridSize;
        int gridColSize[MAX_ROW];
    } testCase[] = {{{{1, 0}, {0, 1}}, 2, {2, 2}}, {{{1, 1}, {1, 0}}, 2, {2, 2}}, {{{1, 1}, {1, 1}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[1,0],[0,1]]
     *  Output: 3
     *
     *  Input: grid = [[1,1],[1,0]]
     *  Output: 4
     *
     *  Input: grid = [[1,1],[1,1]]
     *  Output: 4
     */

    int** pGrid = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: grid = [");
        for (j = 0; j < testCase[i].gridSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].gridColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].grid[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pGrid = (int**)malloc(testCase[i].gridSize * sizeof(int*));
        if (pGrid == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].gridSize; ++j) {
            pGrid[j] = (int*)malloc(testCase[i].gridColSize[j] * sizeof(int));
            if (pGrid[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pGrid[k]);
                    pGrid[k] = NULL;
                }
                free(pGrid);
                pGrid = NULL;
                return EXIT_FAILURE;
            }
            memset(pGrid[j], 0, testCase[i].gridColSize[j] * sizeof(int));
            memcpy(pGrid[j], testCase[i].grid[j], testCase[i].gridColSize[j] * sizeof(int));
        }
        answer = largestIsland(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].gridSize; ++j) {
            free(pGrid[j]);
            pGrid[j] = NULL;
        }
        free(pGrid);
        pGrid = NULL;
    }

    return EXIT_SUCCESS;
}
