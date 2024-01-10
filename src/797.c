#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dfs(int** pAns, int* stk, int stkSize, int x, int n, int** graph, int* graphColSize, int* returnSize,
         int** returnColumnSizes) {
    if (x == n) {
        int* tmp = malloc(stkSize * sizeof(int));
        if (tmp == NULL) {
            perror("malloc");
            return;
        }
        memcpy(tmp, stk, (stkSize * sizeof(int)));
        pAns[*returnSize] = tmp;
        (*returnColumnSizes)[(*returnSize)++] = stkSize;

        return;
    }

    int y;
    int i;
    for (i = 0; i < graphColSize[x]; ++i) {
        y = graph[x][i];
        stk[stkSize++] = y;
        dfs(pAns, stk, stkSize, y, n, graph, graphColSize, returnSize, returnColumnSizes);
        stkSize--;
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** allPathsSourceTarget(int** graph, int graphSize, int* graphColSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

#define MAX_MALLOC_SIZE (16384)
    pRetVal = (int**)malloc(MAX_MALLOC_SIZE * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    (*returnSize) = 0;
    (*returnColumnSizes) = (int*)malloc(MAX_MALLOC_SIZE * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    int stk[15];
    memset(stk, 0, sizeof(stk));
    int stkSize = 1;
    dfs(pRetVal, stk, stkSize, 0, graphSize - 1, graph, graphColSize, returnSize, returnColumnSizes);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (15)
    struct testCaseType {
        int graph[MAX_SIZE][MAX_SIZE];
        int graphSize;
        int graphColSize[MAX_SIZE];
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{{1, 2}, {3}, {3}, {}}, 4, {2, 1, 1, 0}, 0, NULL},
                    {{{4, 3, 1}, {3, 2, 4}, {3}, {4}, {}}, 5, {3, 3, 1, 1, 0}, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: graph = [[1,2],[3],[3],[]]
     *  Output: [[0,1,3],[0,2,3]]
     *
     *  Input: graph = [[4,3,1],[3,2,4],[3],[4],[]]
     *  Output: [[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]
     */

    int** pGraph = NULL;
    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: graph =  [");
        for (j = 0; j < testCase[i].graphSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].graphColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].graph[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pGraph = (int**)malloc(testCase[i].graphSize * sizeof(int*));
        if (pGraph == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].graphSize; ++j) {
            pGraph[j] = (int*)malloc(testCase[i].graphColSize[j] * sizeof(int));
            if (pGraph[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pGraph[k]) {
                        free(pGraph[k]);
                        pGraph[k] = NULL;
                    }
                }
                free(pGraph);
                pGraph = NULL;
                return EXIT_FAILURE;
            }
            memset(pGraph[j], 0, testCase[i].graphColSize[j] * sizeof(int));
            memcpy(pGraph[j], testCase[i].graph[j], testCase[i].graphColSize[j] * sizeof(int));
        }
        pAnswer = allPathsSourceTarget(pGraph, testCase[i].graphSize, testCase[i].graphColSize, &testCase[i].returnSize,
                                       &testCase[i].returnColumnSizes);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;

        for (j = 0; j < testCase[i].graphSize; ++j) {
            if (pGraph[j]) {
                free(pGraph[j]);
                pGraph[j] = NULL;
            }
        }
        free(pGraph);
        pGraph = NULL;
    }

    return EXIT_SUCCESS;
}
