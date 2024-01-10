#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int row;
    int col;
    int step;
};
int nearestExit(char** maze, int mazeSize, int* mazeColSize, int* entrance, int entranceSize) {
    int retVal = -1;

    int mazeRow = mazeSize;
    int mazeCol = mazeColSize[0];
    int queueSize = mazeRow * mazeCol + 1;
    struct node* pQueue = (struct node*)malloc(queueSize * sizeof(struct node));
    if (pQueue == NULL) {
        perror("malloc");
        return retVal;
    }

    // Start BFS from the entrance, and use a queue to store all the cells to be visited.
    int front = 0;
    int rear = 0;
    pQueue[rear].row = entrance[0];
    pQueue[rear].col = entrance[1];
    pQueue[rear++].step = 0;

    // Mark the entrance as visited since its not a exit.
    maze[entrance[0]][entrance[1]] = '+';

#define BFS_DIMENSIONAL (2)
#define BFS_DIRECTION (BFS_DIMENSIONAL * BFS_DIMENSIONAL)
    int direction[BFS_DIRECTION][BFS_DIMENSIONAL] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    int i = 0;
    struct node pCurrent;
    int nextRow, nextCol;
    while (front != rear) {
        pCurrent = pQueue[front];
        front = (front + 1) % queueSize;

        // For the current cell, check its four neighbor cells.
        for (i = 0; i < BFS_DIRECTION; ++i) {
            nextRow = pCurrent.row + direction[i][0];
            nextCol = pCurrent.col + direction[i][1];
            if ((nextRow >= mazeRow) || (nextCol >= mazeCol) || (nextRow < 0) || (nextCol < 0)) {
                continue;
            }

            if (maze[nextRow][nextCol] == '+') {
                continue;
            }

            // If there exists an unvisited empty neighbor
            if (maze[nextRow][nextCol] == '.') {
                // If this empty cell is an exit, return step + 1.
                if ((nextRow == mazeRow - 1) || (nextCol == mazeCol - 1) || (nextRow == 0) || (nextCol == 0)) {
                    retVal = pCurrent.step + 1;
                    free(pQueue);
                    pQueue = NULL;
                    return retVal;
                }

                // Otherwise, add this cell to 'queue' and mark it as visited.
                maze[nextRow][nextCol] = '+';
                pQueue[rear].row = nextRow;
                pQueue[rear].col = nextCol;
                pQueue[(rear++) % queueSize].step = pCurrent.step + 1;
            }
        }
    }
    free(pQueue);
    pQueue = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char maze[MAX_SIZE][MAX_SIZE];
        int mazeSize;
        int mazeColSize[MAX_SIZE];
        int entrance[MAX_SIZE];
        int entranceSize;
    } testCase[] = {{{{'+', '+', '.', '+'}, {'.', '.', '.', '+'}, {'+', '+', '+', '.'}}, 3, {4, 4, 4}, {1, 2}, 2},
                    {{{'+', '+', '+'}, {'.', '.', '.'}, {'+', '+', '+'}}, 3, {3, 3, 3}, {1, 0}, 2},
                    {{{'.', '+'}}, 1, {2}, {0, 0}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: maze = [["+","+",".","+"],[".",".",".","+"],["+","+","+","."]], entrance = [1,2]
     *  Output: 1
     *
     *  Input: maze = [["+","+","+"],[".",".","."],["+","+","+"]], entrance = [1,0]
     *  Output: 2
     *
     *  Input: maze = [[".","+"]], entrance = [0,0]
     *  Output: -1
     */

    char** pMaze = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: maze = [");
        for (j = 0; j < testCase[i].mazeSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].mazeColSize[j]; ++k) {
                printf("%s\"%c\"", (k == 0) ? "" : ",", testCase[i].maze[j][k]);
            }
            printf("]");
        }
        printf("], entrance = [");
        for (j = 0; j < testCase[i].entranceSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].entrance[j]);
        }
        printf("]\n");

        pMaze = (char**)malloc(testCase[i].mazeSize * sizeof(char*));
        if (pMaze == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (k = 0; k < testCase[i].mazeSize; ++k) {
            pMaze[k] = (char*)malloc(testCase[i].mazeColSize[k] * sizeof(char));
            if (pMaze[k] == NULL) {
                perror("malloc");
                for (k = 0; k < testCase[i].mazeSize; ++k) {
                    if (pMaze[k]) {
                        free(pMaze[k]);
                    }
                }
                free(pMaze);
                pMaze = NULL;
                return EXIT_FAILURE;
            }
            memset(pMaze[k], 0, testCase[i].mazeColSize[k] * sizeof(char));
            memcpy(pMaze[k], testCase[i].maze[k], testCase[i].mazeColSize[k] * sizeof(char));
        }
        answer = nearestExit(pMaze, testCase[i].mazeSize, testCase[i].mazeColSize, testCase[i].entrance,
                             testCase[i].entranceSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (k = 0; k < testCase[i].mazeSize; ++k) {
            if (pMaze[k]) {
                free(pMaze[k]);
            }
        }
        free(pMaze);
        pMaze = NULL;
    }

    return EXIT_SUCCESS;
}
