#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEPTH_FIRST_SEARCH (1)
#define BREADTH_FIRST_SEARCH (0)
#if (DEPTH_FIRST_SEARCH)
void dfs(char** grid, int i, int j, int gridSize, int* gridColSize) {
    grid[i][j] = '0';

    if ((i != 0) && (grid[i - 1][j] == '1')) {
        dfs(grid, i - 1, j, gridSize, gridColSize);
    }

    if (((i + 1) != gridSize) && (grid[i + 1][j] == '1')) {
        dfs(grid, i + 1, j, gridSize, gridColSize);
    }

    if ((j != 0) && (grid[i][j - 1] == '1')) {
        dfs(grid, i, j - 1, gridSize, gridColSize);
    }

    if (((j + 1) != gridColSize[i]) && (grid[i][j + 1] == '1')) {
        dfs(grid, i, j + 1, gridSize, gridColSize);
    }
}
#elif (BREADTH_FIRST_SEARCH)
#endif
int numIslands(char** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

#if (DEPTH_FIRST_SEARCH)
    printf("DEPTH_FIRST_SEARCH\n");

    int i, j;
    for (i = 0; i < gridSize; i++) {
        for (j = 0; j < gridColSize[i]; j++) {
            if (grid[i][j] == '1') {
                retVal++;
                dfs(grid, i, j, gridSize, gridColSize);
            }
        }
    }
#elif (BREADTH_FIRST_SEARCH)
    printf("BREADTH_FIRST_SEARCH\n");
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (300)
    struct testCaseType {
        char grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {
        {{{'1', '1', '1', '1', '0'}, {'1', '1', '0', '1', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '0', '0', '0'}},
         4,
         {5, 5, 5, 5}},
        {{{'1', '1', '0', '0', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '0', '1', '1'}},
         4,
         {5, 5, 5, 5}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char** pGrid = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: grid = [\n");
        for (j = 0; j < testCase[i].gridSize; ++j) {
            printf("%s  [", (j == 0 ? "" : ",\n"));
            for (k = 0; k < testCase[i].gridColSize[j]; ++k) {
                printf("%s\"%c\"", (k == 0 ? "" : ","), testCase[i].grid[j][k]);
            }
            printf("]");
        }
        printf("\n]\n");

        pGrid = malloc(testCase[i].gridSize * sizeof(int*));
        if (pGrid == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].gridSize; ++j) {
            pGrid[j] = malloc(testCase[i].gridColSize[j] * sizeof(int));
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
            memset(pGrid[j], 0, (testCase[i].gridColSize[j] * sizeof(int)));
            memcpy(pGrid[j], testCase[i].grid[j], (testCase[i].gridColSize[j] * sizeof(int)));
        }
        answer = numIslands(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
