#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/build-a-matrix-with-conditions/solutions/2544099/gei-ding-tiao-jian-xia-gou-zao-ju-zhen-t-kra5/
struct LinkedNode {
    int dest;
    struct LinkedNode *next;
};
struct BinodeQueue {
    int *arr;
    int arrHead;
    int arrSize;
};
static void queuePush(struct BinodeQueue *queue, int x) {
    queue->arr[queue->arrHead + queue->arrSize] = x;
    queue->arrSize++;
}
static void queuePop(struct BinodeQueue *queue) {
    queue->arrHead++;
    queue->arrSize--;
}
static int topology(int **conditions, int conditionsSize, int k, struct LinkedNode *list, int *sites) {
    int retVal = 0;

    int i;

    int degreeSize = k + 1;
    int degree[degreeSize];
    memset(degree, 0, sizeof(degree));

    struct LinkedNode *head[k + 1];
    memset(head, 0, sizeof(head));

    int arr[k];
    memset(arr, 0, sizeof(arr));
    struct BinodeQueue degreeQueue;
    degreeQueue.arr = arr;
    degreeQueue.arrHead = 0;
    degreeQueue.arrSize = 0;

    for (i = 0; conditionsSize > i; ++i) {
        degree[conditions[i][1]]++;

        list[retVal].dest = conditions[i][1];
        list[retVal].next = head[conditions[i][0]];

        head[conditions[i][0]] = &list[retVal];

        retVal++;
    }

    for (i = 1; i < degreeSize; ++i) {
        if (degree[i] == 0) {
            queuePush(&degreeQueue, i);
        }
    }

    retVal = 0;
    struct LinkedNode *node = NULL;
    while (0 < degreeQueue.arrSize) {
        i = degreeQueue.arr[degreeQueue.arrHead];
        sites[i] = retVal;
        retVal++;
        queuePop(&degreeQueue);

        for (node = head[i]; node != NULL; node = node->next) {
            degree[node->dest]--;
            if (degree[node->dest] == 0) {
                queuePush(&degreeQueue, node->dest);
            }
        }
    }

    return retVal;
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **buildMatrix(int k, int **rowConditions, int rowConditionsSize, int *rowConditionsColSize, int **colConditions,
                  int colConditionsSize, int *colConditionsColSize, int *returnSize, int **returnColumnSizes) {
    int **pRetVal = NULL;

    //
    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    //
    int buffSize = fmax(rowConditionsSize, colConditionsSize);
    struct LinkedNode list[buffSize];
    int sitesSize = k + 1;
    int sites[2][sitesSize];
    int ret = 0;
    ret = topology(rowConditions, rowConditionsSize, k, list, &sites[0][0]);
    if (ret != k) {
        return pRetVal;
    }
    ret = topology(colConditions, colConditionsSize, k, list, &sites[1][0]);
    if (ret != k) {
        return pRetVal;
    }

    //
    pRetVal = (int **)malloc(k * sizeof(int *));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    (*returnColumnSizes) = (int *)malloc(k * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    //
    int i, j;
    for (i = 0; i < k; ++i) {
        pRetVal[i] = (int *)calloc(k, sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("calloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        (*returnColumnSizes)[i] = k;
        (*returnSize) += 1;
    }
    for (i = 1; i < sitesSize; ++i) {
        pRetVal[sites[0][i]][sites[1][i]] = i;
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_ROW (int)(1e4)
#define MAX_COLUMN (2)
    struct testCaseType {
        int k;
        int rowConditions[MAX_ROW][MAX_COLUMN];
        int rowConditionsSize;
        int rowConditionsColSize[MAX_ROW];
        int colConditions[MAX_ROW][MAX_COLUMN];
        int colConditionsSize;
        int colConditionsColSize[MAX_ROW];
        int returnSize;
        int *returnColumnSizes;
    } testCase[] = {{3, {{1, 2}, {3, 2}}, 2, {2, 2}, {{2, 1}, {3, 2}}, 2, {2, 2}, 0, NULL},
                    {3, {{1, 2}, {2, 3}, {3, 1}, {2, 3}}, 4, {2, 2, 2, 2}, {{2, 1}}, 1, {2}, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: k = 3, rowConditions = [[1,2],[3,2]], colConditions = [[2,1],[3,2]]
     *  Output: [[3,0,0],[0,0,1],[0,2,0]]
     *
     *  Input: k = 3, rowConditions = [[1,2],[2,3],[3,1],[2,3]], colConditions = [[2,1]]
     *  Output: []
     */

    int **pRowConditions = NULL;
    int freeRowConditions = 0;
    int **pColConditions = NULL;
    int freeColConditions = 0;
    int **pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: k = %d, rowConditions = [", testCase[i].k);
        for (j = 0; j < testCase[i].rowConditionsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].rowConditionsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].rowConditions[j][k]);
            }
            printf("]");
        }
        printf("], colConditions = [");
        for (j = 0; j < testCase[i].colConditionsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].colConditionsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].colConditions[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pRowConditions = (int **)malloc(testCase[i].rowConditionsSize * sizeof(int *));
        if (pRowConditions == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].rowConditionsSize; ++j) {
            pRowConditions[j] = (int *)malloc(testCase[i].rowConditionsColSize[j] * sizeof(int));
            if (pRowConditions[j] == NULL) {
                perror("malloc");
                freeRowConditions = j;
                goto exit_rowConditions;
            }
            memset(pRowConditions[j], 0, (testCase[i].rowConditionsColSize[j] * sizeof(int)));
            memcpy(pRowConditions[j], testCase[i].rowConditions[j],
                   (testCase[i].rowConditionsColSize[j] * sizeof(int)));
        }
        freeRowConditions = testCase[i].rowConditionsSize;
        pColConditions = (int **)malloc(testCase[i].colConditionsSize * sizeof(int *));
        if (pColConditions == NULL) {
            perror("malloc");
            goto exit_rowConditions;
        }
        for (j = 0; j < testCase[i].colConditionsSize; ++j) {
            pColConditions[j] = (int *)malloc(testCase[i].colConditionsColSize[j] * sizeof(int));
            if (pColConditions[j] == NULL) {
                perror("malloc");
                freeColConditions = j;
                goto exit_colConditions;
            }
            memset(pColConditions[j], 0, (testCase[i].colConditionsColSize[j] * sizeof(int)));
            memcpy(pColConditions[j], testCase[i].colConditions[j],
                   (testCase[i].colConditionsColSize[j] * sizeof(int)));
        }
        freeColConditions = testCase[i].colConditionsSize;

        pAnswer =
            buildMatrix(testCase[i].k, pRowConditions, testCase[i].rowConditionsSize, testCase[i].rowConditionsColSize,
                        pColConditions, testCase[i].colConditionsSize, testCase[i].colConditionsColSize,
                        &testCase[i].returnSize, &(testCase[i].returnColumnSizes));
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), pAnswer[j][k]);
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
        for (j = 0; j < testCase[i].rowConditionsSize; ++j) {
            free(pRowConditions[j]);
            pRowConditions[j] = NULL;
        }
        free(pRowConditions);
        pRowConditions = NULL;
        for (j = 0; j < testCase[i].colConditionsSize; ++j) {
            free(pColConditions[j]);
            pColConditions[j] = NULL;
        }
        free(pColConditions);
        pColConditions = NULL;
    }

    return EXIT_SUCCESS;

exit_colConditions:
    for (k = 0; k < freeColConditions; ++k) {
        free(pColConditions[k]);
        pColConditions[k] = NULL;
    }
    free(pColConditions);
    pColConditions = NULL;

exit_rowConditions:
    for (k = 0; k < freeRowConditions; ++k) {
        free(pRowConditions[k]);
        pRowConditions[k] = NULL;
    }
    free(pRowConditions);
    pRowConditions = NULL;

    return EXIT_FAILURE;
}
