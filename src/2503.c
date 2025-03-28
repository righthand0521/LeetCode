#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/maximum-number-of-points-from-grid-queries/solutions/2017183/ju-zhen-cha-xun-ke-huo-de-by-heng-deng-s-lcyx/
#define BITS_SHIFT (32)
#define BITS_MASK (0xFFFFFFFF)
#define INVALID_VALUE (-1)
#define FATHER_NODE(x) ((0 == (x)) ? INVALID_VALUE : (((x) - 1) >> 1))
#define LEFT_NODE(x) (((x) << 1) + 1)
#define RIGHT_NODE(x) (((x) << 1) + 2)
#define IN_RANGE(x, y, m, n) ((0 <= (x)) && (m > (x)) && (0 <= y) && (n > (y)))
typedef struct {
    long int *array;
    int arraySize;
} HeapNode;
int findParent(int *parent, int index) {
    int retVal = 0;

    while (parent[index] != index) {
        parent[index] = parent[parent[index]];
        index = parent[index];
    }
    retVal = index;

    return retVal;
}
void heapPush(HeapNode *heap, long int t) {
    int son = heap->arraySize;
    int father = FATHER_NODE(son);

    heap->arraySize++;

    while ((INVALID_VALUE != father) && (heap->array[father] > t)) {
        heap->array[son] = heap->array[father];
        son = father;
        father = FATHER_NODE(son);
    }
    heap->array[son] = t;
}
void heapPop(HeapNode *heap) {
    int father = 0;
    int left = LEFT_NODE(father);
    int right = RIGHT_NODE(father);
    int son = 0;
    long int t = heap->array[heap->arraySize - 1];

    heap->arraySize--;

    while (((heap->arraySize > left) && (heap->array[left] < t)) ||
           ((heap->arraySize > right) && (heap->array[right] < t))) {
        son = ((heap->arraySize > right) && (heap->array[right] < heap->array[left])) ? right : left;
        heap->array[father] = heap->array[son];
        father = son;
        left = LEFT_NODE(father);
        right = RIGHT_NODE(father);
    }
    heap->array[father] = t;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *maxPoints(int **grid, int gridSize, int *gridColSize, int *queries, int queriesSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int *)calloc(queriesSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    (*returnSize) = queriesSize;

    int rowSize = gridSize;
    int colSize = gridColSize[0];
    int totalCells = rowSize * colSize;
    int gridIndex = 0;

    int parent[totalCells];
    int counter[totalCells];
    long int array1[totalCells];
    HeapNode gridHeap;
    gridHeap.array = array1;
    gridHeap.arraySize = 0;
    for (int x = 0; x < rowSize; x++) {
        for (int y = 0; y < colSize; y++) {
            parent[gridIndex] = gridIndex;
            counter[gridIndex] = 0;

            long int t = ((long int)grid[x][y] << BITS_SHIFT) + gridIndex;
            heapPush(&gridHeap, t);

            gridIndex++;
        }
    }

    long int array2[queriesSize];
    HeapNode queriesHeap;
    queriesHeap.array = array2;
    queriesHeap.arraySize = 0;
    for (int x = 0; x < queriesSize; x++) {
        long int t = ((long int)queries[x] << BITS_SHIFT) + x;
        heapPush(&queriesHeap, t);
    }

    const int direction[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int parentIndex;
    while (0 < queriesHeap.arraySize) {
        int value = queriesHeap.array[0] >> BITS_SHIFT;
        int queriesIndex = queriesHeap.array[0] & BITS_MASK;
        heapPop(&queriesHeap);

        while ((0 < gridHeap.arraySize) && (gridHeap.array[0] >> BITS_SHIFT < value)) {
            gridIndex = gridHeap.array[0] & BITS_MASK;
            heapPop(&gridHeap);

            int x = gridIndex / colSize;
            int y = gridIndex % colSize;
            counter[gridIndex] = 1;
            for (int i = 0; i < 4; i++) {
                int newX = x + direction[i][0];
                int newY = y + direction[i][1];
                int newIndex = newX * colSize + newY;
                if ((newX < 0) || (newX >= rowSize) || (newY < 0) || (newY >= colSize)) {
                    continue;
                } else if (counter[newIndex] <= 0) {
                    continue;
                }

                parentIndex = findParent(parent, newIndex);
                if (parentIndex != gridIndex) {
                    parent[parentIndex] = gridIndex;
                    counter[gridIndex] += counter[parentIndex];
                }
            }
        }

        parentIndex = findParent(parent, 0);
        pRetVal[queriesIndex] = counter[parentIndex];
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_GRID_SIZE (1000)
#define MAX_QUERIES_SIZE (int)(1e4)
    struct testCaseType {
        int grid[MAX_GRID_SIZE][MAX_GRID_SIZE];
        int gridSize;
        int gridColSize[MAX_GRID_SIZE];
        int queries[MAX_QUERIES_SIZE];
        int queriesSize;
        int returnSize;
    } testCase[] = {{{{1, 2, 3}, {2, 5, 7}, {3, 5, 1}}, 3, {3, 3, 3}, {5, 6, 2}, 3, 0},
                    {{{5, 2, 1}, {1, 1, 2}}, 2, {3, 3}, {3}, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[1,2,3],[2,5,7],[3,5,1]], queries = [5,6,2]
     *  Output: [5,8,1]
     *
     *  Input: grid = [[5,2,1],[1,1,2]], queries = [3]
     *  Output: [0]
     */

    int **pGrid = NULL;
    int *pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: grid = [");
        for (j = 0; j < testCase[i].gridSize; ++j) {
            printf("[");
            for (k = 0; k < testCase[i].gridColSize[j]; ++k) {
                printf("%d%s", testCase[i].grid[j][k], (k == (testCase[i].gridColSize[j] - 1) ? "" : ","));
            }
            printf("%s", (j == (testCase[i].gridSize - 1) ? "]" : "],"));
        }
        printf("], queries = [");
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            printf("%d%s", testCase[i].queries[j], (j == (testCase[i].queriesSize - 1) ? "]" : ","));
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
        }
        for (j = 0; j < testCase[i].gridSize; ++j) {
            for (k = 0; k < testCase[i].gridColSize[j]; ++k) {
                pGrid[j][k] = testCase[i].grid[j][k];
            }
        }
        pAnswer = maxPoints(pGrid, testCase[i].gridSize, testCase[i].gridColSize, testCase[i].queries,
                            testCase[i].queriesSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].gridSize; ++j) {
            free(pGrid[j]);
        }
        free(pGrid);
        pGrid = NULL;

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
