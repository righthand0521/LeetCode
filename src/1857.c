#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLORS_MAX_SIZE (26)  // colors consists of lowercase English letters.
struct AdjacentNode {
    int val;
    struct AdjacentNode* next;
};
int largestPathValue(char* colors, int** edges, int edgesSize, int* edgesColSize) {
    int retVal = -1;

    int i, j;
    struct AdjacentNode* pCurrent = NULL;
    struct AdjacentNode* pTemp = NULL;

    //
    int colorsSize = strlen(colors);
    struct AdjacentNode* adjacent[colorsSize];
    for (i = 0; i < colorsSize; ++i) {
        adjacent[i] = (struct AdjacentNode*)malloc(sizeof(struct AdjacentNode));
        if (adjacent[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                pCurrent = adjacent[j];
                while (pCurrent != NULL) {
                    pTemp = pCurrent;
                    pCurrent = pCurrent->next;
                    free(pTemp);
                    pTemp = NULL;
                }
            }
            return retVal;
        }
        adjacent[i]->val = -1;
        adjacent[i]->next = NULL;
    }
    int indegree[colorsSize];
    memset(indegree, 0, sizeof(indegree));
    for (i = 0; i < edgesSize; ++i) {
        ++indegree[edges[i][1]];

        pTemp = (struct AdjacentNode*)malloc(sizeof(struct AdjacentNode));
        if (pTemp == NULL) {
            perror("malloc");
            for (i = 0; i < colorsSize; ++i) {
                pCurrent = adjacent[i];
                while (pCurrent != NULL) {
                    pTemp = pCurrent;
                    pCurrent = pCurrent->next;
                    free(pTemp);
                    pTemp = NULL;
                }
            }
            return retVal;
        }
        pTemp->val = edges[i][1];
        pTemp->next = NULL;
        pCurrent = adjacent[edges[i][0]];
        while (pCurrent->next != NULL) {
            pCurrent = pCurrent->next;
        }
        pCurrent->next = pTemp;
    }

    //
    int colorsFound = 0;
    int colorsRecord[colorsSize][COLORS_MAX_SIZE][1];
    memset(colorsRecord, 0, sizeof(colorsRecord));
    int colorsQueue[colorsSize * 2];
    memset(colorsQueue, 0, sizeof(colorsQueue));
    int colorsQueueFront = 0;
    int colorsQueueRear = 0;
    for (i = 0; i < colorsSize; ++i) {
        if (indegree[i] == 0) {
            colorsQueue[colorsQueueRear] = i;
            ++colorsQueueRear;
        }
    }

    int c, u, v;
    while (colorsQueueFront < colorsQueueRear) {
        u = colorsQueue[colorsQueueFront];
        ++colorsQueueFront;
        ++colorsRecord[u][colors[u] - 'a'][0];
        ++colorsFound;

        pCurrent = adjacent[u]->next;
        while (pCurrent != NULL) {
            v = pCurrent->val;

            --indegree[v];

            for (c = 0; c < COLORS_MAX_SIZE; ++c) {
                colorsRecord[v][c][0] = fmax(colorsRecord[v][c][0], colorsRecord[u][c][0]);
            }

            if (indegree[v] == 0) {
                colorsQueue[colorsQueueRear] = v;
                ++colorsQueueRear;
            }

            pCurrent = pCurrent->next;
        }
    }

    //
    int maxColorsRecord;
    if (colorsFound == colorsSize) {
        retVal = 0;
        for (i = 0; i < colorsSize; ++i) {
            maxColorsRecord = 0;
            for (j = 0; j < COLORS_MAX_SIZE; ++j) {
                maxColorsRecord = fmax(maxColorsRecord, colorsRecord[i][j][0]);
            }

            retVal = fmax(retVal, maxColorsRecord);
        }
    }

    //
    for (i = 0; i < colorsSize; ++i) {
        pCurrent = adjacent[i];
        while (pCurrent != NULL) {
            pTemp = pCurrent;
            pCurrent = pCurrent->next;
            free(pTemp);
            pTemp = NULL;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char colors[MAX_SIZE];
        int edges[MAX_SIZE][2];
        int edgesSize;
        int edgesColSize[MAX_SIZE];
    } testCase[] = {{"abaca", {{0, 1}, {0, 2}, {2, 3}, {3, 4}}, 4, {2, 2, 2, 2}}, {"a", {{0, 0}}, 1, {2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: colors = "abaca", edges = [[0,1],[0,2],[2,3],[3,4]]
     *  Output: 3
     *
     *  Input: colors = "a", edges = [[0,0]]
     *  Output: -1
     */

    int** pEdges = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: colors = \"%s\", edges = [", testCase[i].colors);
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].edgesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].edges[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pEdges = (int**)malloc(testCase[i].edgesSize * sizeof(int*));
        if (pEdges == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            pEdges[j] = (int*)malloc(testCase[i].edgesColSize[j] * sizeof(int));
            if (pEdges[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pEdges[k]);
                    pEdges[k] = NULL;
                }
                free(pEdges);
                pEdges = NULL;
                return EXIT_FAILURE;
            }
            memset(pEdges[j], 0, testCase[i].edgesColSize[j] * sizeof(int));
            memcpy(pEdges[j], testCase[i].edges[j], testCase[i].edgesColSize[j] * sizeof(int));
        }
        answer = largestPathValue(testCase[i].colors, pEdges, testCase[i].edgesSize, testCase[i].edgesColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].edgesSize; ++j) {
            free(pEdges[j]);
            pEdges[j] = NULL;
        }
        free(pEdges);
        pEdges = NULL;
    }

    return EXIT_SUCCESS;
}
