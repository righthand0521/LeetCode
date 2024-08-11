#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int Directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
struct ArticulationPointInfo {
    bool hasArticulationPoint;
    int time;
};
int** mallocStoreArray(int rowSize, int colSize, int value) {
    int** pRetVal = NULL;

    pRetVal = (int**)malloc(rowSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int i, j;
    for (i = 0; i < rowSize; ++i) {
        pRetVal[i] = (int*)malloc(colSize * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            break;
        }
        memset(pRetVal[i], -1, (colSize * sizeof(int)));
    }

    return pRetVal;
}
void findArticulationPoint(int** grid, int rowSize, int colSize, int row, int col, int** pDiscoveryTime,
                           int** pLowestReachable, int** pParentCell, struct ArticulationPointInfo* pApInfo) {
    pDiscoveryTime[row][col] = pApInfo->time;
    pApInfo->time += 1;
    pLowestReachable[row][col] = pDiscoveryTime[row][col];

    int children = 0;
    int x, y;
    int i;
    for (i = 0; i < 4; ++i) {
        x = row + Directions[i][0];
        y = col + Directions[i][1];
        if ((x < 0) || (x >= rowSize)) {
            continue;
        } else if ((y < 0) || (y >= colSize)) {
            continue;
        } else if (grid[x][y] != 1) {
            continue;
        }

        if (pDiscoveryTime[x][y] == -1) {
            children++;

            pParentCell[x][y] = row * colSize + col;
            findArticulationPoint(grid, rowSize, colSize, x, y, pDiscoveryTime, pLowestReachable, pParentCell, pApInfo);

            // Update lowest reachable time
            pLowestReachable[row][col] = fmin(pLowestReachable[row][col], pLowestReachable[x][y]);
            // Check for articulation point condition
            if ((pLowestReachable[x][y] >= pDiscoveryTime[row][col]) && (pParentCell[row][col] != -1)) {
                pApInfo->hasArticulationPoint = true;
            }
        } else if (x * colSize + y != pParentCell[row][col]) {
            // Update lowest reachable time for back edge
            pLowestReachable[row][col] = fmin(pLowestReachable[row][col], pDiscoveryTime[x][y]);
        }
    }

    // Root of DFS tree is an articulation point if it has more than one child
    if ((pParentCell[row][col] == -1) && (children > 1)) {
        pApInfo->hasArticulationPoint = true;
    }
}
int minDays(int** grid, int gridSize, int* gridColSize) {
    int retVal = 2;  // Need to remove any two land cells

    int rowSize = gridSize;
    int colSize = gridColSize[0];

    // Time when a cell is first discovered
    int** pDiscoveryTime = mallocStoreArray(rowSize, colSize, -1);
    if (pDiscoveryTime == NULL) {
        perror("malloc");
        goto exit;
    }
    // Lowest discovery time reachable from the subtree rooted at this cell
    int** pLowestReachable = mallocStoreArray(rowSize, colSize, -1);
    if (pLowestReachable == NULL) {
        perror("malloc");
        goto exit_pDiscoveryTime;
    }
    // Parent of each cell in DFS tree
    int** pParentCell = mallocStoreArray(rowSize, colSize, -1);
    if (pParentCell == NULL) {
        perror("malloc");
        goto exit_pLowestReachable;
    }

    struct ArticulationPointInfo* pApInfo = NULL;
    pApInfo = (struct ArticulationPointInfo*)malloc(sizeof(struct ArticulationPointInfo));
    if (pApInfo == NULL) {
        perror("malloc");
        goto exit_pParentCell;
    }
    pApInfo->hasArticulationPoint = false;
    pApInfo->time = 0;

    int landCells = 0;
    int islandCount = 0;
    int x, y;
    for (x = 0; x < rowSize; ++x) {
        for (y = 0; y < colSize; ++y) {
            if (grid[x][y] != 1) {
                continue;
            }
            landCells++;

            if (pDiscoveryTime[x][y] != -1) {
                continue;
            }
            findArticulationPoint(grid, rowSize, colSize, x, y, pDiscoveryTime, pLowestReachable, pParentCell, pApInfo);
            islandCount++;
        }
    }
    if ((islandCount == 0) || (islandCount >= 2)) {
        retVal = 0;  // Already disconnected or no land
    } else if (landCells == 1) {
        retVal = 1;  // Only one land cell
    } else if (pApInfo->hasArticulationPoint == true) {
        retVal = 1;  // An articulation point exists
    }

    //
    free(pApInfo);
    pApInfo = NULL;

exit_pParentCell:
    for (int i = 0; i < rowSize; ++i) {
        free(pParentCell[i]);
        pParentCell[i] = NULL;
    }
    free(pParentCell);
    pParentCell = NULL;

exit_pLowestReachable:
    for (int i = 0; i < rowSize; ++i) {
        free(pLowestReachable[i]);
        pLowestReachable[i] = NULL;
    }
    free(pLowestReachable);
    pLowestReachable = NULL;

exit_pDiscoveryTime:
    for (int i = 0; i < rowSize; ++i) {
        free(pDiscoveryTime[i]);
        pDiscoveryTime[i] = NULL;
    }
    free(pDiscoveryTime);
    pDiscoveryTime = NULL;

exit:
    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (30)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {{{{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}, 3, {4, 4, 4}}, {{{1, 1}}, 1, {2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[0,1,1,0],[0,1,1,0],[0,0,0,0]]
     *  Output: 2
     *
     *  Input: grid = [[1,1]]
     *  Output: 2
     */

    int** pGrid = NULL;
    int answer;
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
                    free(pGrid[j]);
                    pGrid[j] = NULL;
                }
                return EXIT_FAILURE;
            }
            memset(pGrid[j], 0, (testCase[i].gridColSize[j] * sizeof(int)));
            memcpy(pGrid[j], testCase[i].grid[j], (testCase[i].gridColSize[j] * sizeof(int)));
        }
        answer = minDays(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
