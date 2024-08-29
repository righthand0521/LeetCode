#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dfs(int** adjacencyList, int* adjacencyListColSize, bool* visited, int stone) {
    visited[stone] = true;

    int neighbor;
    int i;
    for (i = 0; i < adjacencyListColSize[stone]; ++i) {
        neighbor = adjacencyList[stone][i];
        if (visited[neighbor] == false) {
            dfs(adjacencyList, adjacencyListColSize, visited, neighbor);
        }
    }
}
int removeStones(int** stones, int stonesSize, int* stonesColSize) {
    int retVal = 0;

    int i, j;

    int** adjacencyList = NULL;
    adjacencyList = (int**)malloc(stonesSize * sizeof(int*));
    if (adjacencyList == NULL) {
        perror("malloc");
        return retVal;
    }
    for (i = 0; i < stonesSize; ++i) {
        adjacencyList[i] = (int*)malloc(stonesSize * sizeof(int));
        if (adjacencyList[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(adjacencyList[j]);
                adjacencyList[j] = NULL;
            }
            free(adjacencyList);
            adjacencyList = NULL;
            return retVal;
        }
        memset(adjacencyList[i], 0, (stonesSize * sizeof(int)));
    }
    int* adjacencyListColSize = NULL;
    adjacencyListColSize = (int*)malloc(stonesSize * sizeof(int));
    if (adjacencyListColSize == NULL) {
        perror("malloc");
        for (i = 0; i < stonesSize; ++i) {
            free(adjacencyList[i]);
            adjacencyList[i] = NULL;
        }
        free(adjacencyList);
        adjacencyList = NULL;
        return retVal;
    }
    memset(adjacencyListColSize, 0, (stonesSize * sizeof(int)));
    for (i = 0; i < stonesSize; i++) {
        for (j = i + 1; j < stonesSize; j++) {
            if ((stones[i][0] == stones[j][0]) || (stones[i][1] == stones[j][1])) {
                adjacencyList[i][adjacencyListColSize[i]++] = j;
                adjacencyList[j][adjacencyListColSize[j]++] = i;
            }
        }
    }

    bool visited[stonesSize];
    memset(visited, false, sizeof(visited));
    int numOfConnectedComponents = 0;
    for (i = 0; i < stonesSize; i++) {
        if (visited[i] == false) {
            dfs(adjacencyList, adjacencyListColSize, visited, i);
            numOfConnectedComponents++;
        }
    }

    retVal = stonesSize - numOfConnectedComponents;

    //
    free(adjacencyListColSize);
    adjacencyListColSize = NULL;
    for (i = 0; i < stonesSize; ++i) {
        free(adjacencyList[i]);
        adjacencyList[i] = NULL;
    }
    free(adjacencyList);
    adjacencyList = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int stones[MAX_SIZE][2];
        int stonesSize;
        int stonesColSize;
    } testCase[] = {{{{0, 0}, {0, 1}, {1, 0}, {1, 2}, {2, 1}, {2, 2}}, 6, 2},
                    {{{0, 0}, {0, 2}, {1, 1}, {2, 0}, {2, 2}}, 5, 2},
                    {{{0, 0}}, 1, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
     *  Output: 5
     *
     *  Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
     *  Output: 3
     *
     *  Input: stones = [[0,0]]
     *  Output: 0
     */

    int** pStones = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: stones = [");
        for (j = 0; j < testCase[i].stonesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].stonesColSize; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].stones[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pStones = (int**)malloc(testCase[i].stonesSize * sizeof(int*));
        if (pStones == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].stonesSize; ++j) {
            pStones[j] = (int*)malloc(testCase[i].stonesColSize * sizeof(int));
            if (pStones[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pStones[k]) {
                        free(pStones[k]);
                    }
                }
                free(pStones);
                pStones = NULL;
                return EXIT_FAILURE;
            }
            memset(pStones[j], 0, testCase[i].stonesColSize * sizeof(int));
            memcpy(pStones[j], testCase[i].stones[j], testCase[i].stonesColSize * sizeof(int));
        }
        answer = removeStones(pStones, testCase[i].stonesSize, &testCase[i].stonesColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].stonesSize; ++j) {
            if (pStones[j]) {
                free(pStones[j]);
            }
        }
        free(pStones);
        pStones = NULL;
    }

    return EXIT_SUCCESS;
}
