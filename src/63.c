#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize) {
    int retVal = 0;

    if (obstacleGrid[0][0] == 1) {
        return retVal;
    }

    int i, j;
    int row = obstacleGridSize;
    int col = obstacleGridColSize[0];

    /* Example
     *    | 0 1 2 | 0 1 2
     *  --+-------+-------
     *  0 | 0 0 0 | 1 1 1
     *  1 | 0 1 0 | 1 0 1
     *  2 | 0 0 0 | 1 1 2
     */
    obstacleGrid[0][0] = 1;
    for (i = 1; i < row; ++i) {
        obstacleGrid[i][0] = (((obstacleGrid[i][0] == 0) && (obstacleGrid[i - 1][0] == 1)) ? (1) : (0));
    }
    for (i = 1; i < col; ++i) {
        obstacleGrid[0][i] = (((obstacleGrid[0][i] == 0) && (obstacleGrid[0][i - 1] == 1)) ? (1) : (0));
    }

    for (i = 1; i < row; ++i) {
        for (j = 1; j < col; ++j) {
            obstacleGrid[i][j] = ((obstacleGrid[i][j] == 0) ? (obstacleGrid[i - 1][j] + obstacleGrid[i][j - 1]) : (0));
        }
    }
    retVal = obstacleGrid[row - 1][col - 1];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int obstacleGrid[MAX_SIZE][MAX_SIZE];
        int obstacleGridSize;
        int obstacleGridColSize[MAX_SIZE];
    } testCase[] = {{{{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}, 3, {3, 3, 3}}, {{{0, 1}, {0, 0}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
     *  Output: 2
     *
     *  Input: obstacleGrid = [[0,1],[0,0]]
     *  Output: 1
     */

    int** pObstacleGrid = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("obstacleGrid = [");
        for (j = 0; j < testCase[i].obstacleGridSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].obstacleGridColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].obstacleGrid[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pObstacleGrid = (int**)malloc(testCase[i].obstacleGridSize * sizeof(int*));
        if (pObstacleGrid == NULL) {
            perror("calloc");
            return EXIT_FAILURE;
        }
        memset(pObstacleGrid, 0, testCase[i].obstacleGridSize * sizeof(int*));
        for (j = 0; j < testCase[i].obstacleGridSize; ++j) {
            pObstacleGrid[j] = (int*)malloc(testCase[i].obstacleGridColSize[j] * sizeof(int));
            if (pObstacleGrid[j] == NULL) {
                perror("calloc");
                for (k = 0; k < j; ++k) {
                    free(pObstacleGrid[k]);
                    pObstacleGrid[k] = NULL;
                }
                free(pObstacleGrid);
                pObstacleGrid = NULL;
            }
            memset(pObstacleGrid[j], 0, (testCase[i].obstacleGridColSize[j] * sizeof(int)));
            memcpy(pObstacleGrid[j], testCase[i].obstacleGrid[j], (testCase[i].obstacleGridColSize[j] * sizeof(int)));
        }
        answer = uniquePathsWithObstacles(pObstacleGrid, testCase[i].obstacleGridSize, testCase[i].obstacleGridColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].obstacleGridSize; ++j) {
            free(pObstacleGrid[j]);
            pObstacleGrid[j] = NULL;
        }
        free(pObstacleGrid);
        pObstacleGrid = NULL;
    }

    return EXIT_SUCCESS;
}
