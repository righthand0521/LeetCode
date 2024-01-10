#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/snakes-and-ladders/solutions/86815/cyu-yan-bfsni-zhi-de-yong-you-by-dave-19-2/
int getNextBoardValue(int** board, int boardSize, int num) {
    int retVal = -1;

    if (board == NULL) {
        return retVal;
    }

    int n = boardSize;
    int x = (num - 1) / n;
    int y = (num - 1) % n;

    if (x % 2 != 0) {
        y = (n - 1) - y;
    }
    x = (n - 1) - x;
    retVal = board[x][y];

    return retVal;
}
int snakesAndLadders(int** board, int boardSize, int* boardColSize) {
    int retVal = -1;

    if ((board == NULL) || (boardSize == 0) || (boardColSize == NULL)) {
        return retVal;
    }

    int n = boardSize;

    int queue[n * n];
    memset(queue, 0, sizeof(queue));
    int rear = 0;
    int front = 0;
    queue[rear++] = 1;

    int visited[n * n + 1];
    memset(visited, 0, sizeof(visited));

    int cur = 0;
    int next = 0;
    int minStep = 0;
    int layerNum = 0;
    int i, j;
    while (rear != front) {
        layerNum = rear - front;
        for (i = 0; i < layerNum; ++i) {
            cur = queue[front++];
            if (cur == n * n) {
                retVal = minStep;
                return retVal;
            }

            for (j = 1; j <= 6 && cur + j <= n * n; ++j) {
                next = getNextBoardValue(board, boardSize, cur + j);
                if (next == -1) {
                    next = cur + j;
                }

                if (visited[next]) {
                    continue;
                }
                visited[next] = true;
                queue[rear++] = next;
            }
        }

        minStep++;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (20)
    struct testCaseType {
        int board[MAX_SIZE][MAX_SIZE];
        int boardSize;
        int boardColSize[MAX_SIZE];
    } testCase[] = {{{{-1, -1, -1, -1, -1, -1},
                      {-1, -1, -1, -1, -1, -1},
                      {-1, -1, -1, -1, -1, -1},
                      {-1, 35, -1, -1, 13, -1},
                      {-1, -1, -1, -1, -1, -1},
                      {-1, 15, -1, -1, -1, -1}},
                     6,
                     {6, 6, 6, 6, 6, 6}},
                    {{{-1, -1}, {-1, 3}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pBoard = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: board = [");
        for (j = 0; j < testCase[i].boardSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].boardColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].board[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pBoard = (int**)malloc(testCase[i].boardSize * sizeof(int*));
        if (pBoard == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].boardSize; ++j) {
            pBoard[j] = (int*)malloc(testCase[i].boardColSize[j] * sizeof(int));
            if (pBoard[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pBoard[k]) {
                        free(pBoard[k]);
                        pBoard[k] = NULL;
                    }
                }
                free(pBoard);
                pBoard = NULL;
                return EXIT_FAILURE;
            }
            memset(pBoard[j], 0, testCase[i].boardColSize[j] * sizeof(int));
            memcpy(pBoard[j], testCase[i].board[j], testCase[i].boardColSize[j] * sizeof(int));
        }
        answer = snakesAndLadders(pBoard, testCase[i].boardSize, testCase[i].boardColSize);

        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].boardSize; ++j) {
            if (pBoard[j]) {
                free(pBoard[j]);
                pBoard[j] = NULL;
            }
        }
        free(pBoard);
        pBoard = NULL;
    }

    return EXIT_SUCCESS;
}
