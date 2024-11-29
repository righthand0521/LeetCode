#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/minimum-time-to-visit-a-cell-in-a-grid/solutions/2521039/zai-wang-ge-tu-zhong-fang-wen-yi-ge-ge-z-l4jw/
#ifndef HEAP_H
#define HEAP_H

#define MERGE_LONG(t, x, y) ((long long)(t) << 32 | (long long)(x) << 16 | (long long)(y))
#define ROW_INT(l) ((l) >> 16 & 0xFFFF)
#define COL_INT(l) ((l) & 0xFFFF)
#define FATHER_NODE(i) (0 == (i) ? -1 : (((i) - 1) >> 1))
#define LEFT_NODE(i) (((i) << 1) + 1)
#define RIGHT_NODE(i) (((i) << 1) + 2)

typedef struct {
    long long *arr;
    int arrSize;
} PriorityQueue;

static void queuePush(PriorityQueue *queue, long long value) {
    int son = queue->arrSize;
    int father = FATHER_NODE(son);

    queue->arrSize++;
    while ((-1 != father) && (value < queue->arr[father])) {
        queue->arr[son] = queue->arr[father];
        son = father;
        father = FATHER_NODE(son);
    }
    queue->arr[son] = value;
}
static void queuePop(PriorityQueue *queue) {
    int father = 0;
    int left = LEFT_NODE(father);
    int right = RIGHT_NODE(father);
    int son = 0;

    queue->arrSize--;
    while (((queue->arrSize > left) && (queue->arr[queue->arrSize] > queue->arr[left])) ||
           ((queue->arrSize > right) && (queue->arr[queue->arrSize] > queue->arr[right]))) {
        son = (queue->arrSize > right && queue->arr[left] > queue->arr[right]) ? right : left;
        queue->arr[father] = queue->arr[son];
        father = son;
        left = LEFT_NODE(father);
        right = RIGHT_NODE(father);
    }
    queue->arr[father] = queue->arr[queue->arrSize];
}

#endif  // HEAP_H
int minimumTime(int **grid, int gridSize, int *gridColSize) {
    int retVal = -1;

    if ((1 < grid[0][1]) && (1 < grid[1][0])) {
        return retVal;
    }

    int rowSize = gridSize;
    int colSize = gridColSize[0];

    int arrive[rowSize][colSize];
    memset(arrive, -1, sizeof(arrive));
    arrive[0][0] = 0;

    int totalSize = rowSize * colSize;
    long long arr[totalSize];
    PriorityQueue queue;
    queue.arr = arr;
    queue.arrSize = 0;
    queuePush(&queue, MERGE_LONG(arrive[0][0], 0, 0));

    const int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int x, y, nextRow, nextCol;
    while ((0 < queue.arrSize) && (-1 == arrive[rowSize - 1][colSize - 1])) {
        x = ROW_INT(queue.arr[0]);
        y = COL_INT(queue.arr[0]);
        queuePop(&queue);

        for (int i = 0; ((i < 4) && (-1 == arrive[rowSize - 1][colSize - 1])); ++i) {
            nextRow = x + directions[i][0];
            nextCol = y + directions[i][1];
            if (nextRow < 0) {
                continue;
            } else if (nextRow >= rowSize) {
                continue;
            } else if (nextCol < 0) {
                continue;
            } else if (nextCol >= colSize) {
                continue;
            } else if (arrive[nextRow][nextCol] != -1) {
                continue;
            }

            if (arrive[x][y] + 1 >= grid[nextRow][nextCol]) {
                arrive[nextRow][nextCol] = arrive[x][y] + 1;
            } else {
                arrive[nextRow][nextCol] = grid[nextRow][nextCol] + ((grid[nextRow][nextCol] - arrive[x][y] + 1) & 1);
            }
            queuePush(&queue, MERGE_LONG(arrive[nextRow][nextCol], nextRow, nextCol));
        }
    }
    retVal = arrive[rowSize - 1][colSize - 1];

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {{{{0, 1, 3, 2}, {5, 1, 2, 5}, {4, 3, 8, 6}}, 3, {4, 4, 4}},
                    {{{0, 2, 4}, {3, 2, 1}, {1, 0, 4}}, 3, {3, 3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[0,1,3,2],[5,1,2,5],[4,3,8,6]]
     *  Output: 7
     *
     *  Input: grid = [[0,2,4],[3,2,1],[1,0,4]]
     *  Output: -1
     */

    int **pGrid = NULL;
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

        pGrid = (int **)malloc(testCase[i].gridSize * sizeof(int *));
        if (pGrid == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].gridSize; ++j) {
            pGrid[j] = (int *)malloc(testCase[i].gridColSize[j] * sizeof(int));
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
        answer = minimumTime(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
