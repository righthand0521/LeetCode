#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumTime(int n, int** relations, int relationsSize, int* relationsColSize, int* time, int timeSize) {
    int retVal = 0;

    int i;

    //
    int count[n + 1];
    memset(count, 0, sizeof(count));
    for (i = 0; i < relationsSize; ++i) {
        count[relations[i][0]]++;
    }
    int graphMaxSize = 1;
    for (i = 0; i <= n; ++i) {
        graphMaxSize = fmax(graphMaxSize, count[i]);
    }

    int graph[n][graphMaxSize];
    memset(graph, -1, sizeof(graph));
    int graphColSize[n];
    memset(graphColSize, 0, sizeof(graphColSize));

    int indegree[n];
    memset(indegree, 0, sizeof(indegree));

    int x, y;
    for (i = 0; i < relationsSize; ++i) {
        x = relations[i][0] - 1;
        y = relations[i][1] - 1;
        graph[x][graphColSize[x]++] = y;
        indegree[y]++;
    }
#if (0)
    printf("indegree: ");
    for (i = 0; i < n; ++i) {
        printf("%d ", indegree[i]);
    }
    printf("\n");
    for (i = 0; i < n; ++i) {
        printf("graph[%d]: ", i);
        for (int j = 0; j < graphColSize[i]; ++j) {
            printf("%2d ", graph[i][j]);
        }
        printf(": %d\n", graphColSize[i]);
    }
#endif

    //
    int maxTime[n];
    memset(maxTime, 0, sizeof(maxTime));

#define MAX_QUEUE_SIZE ((n)*2)
    int topologicalSortQueueHead = 0;
    int topologicalSortQueueTail = 0;
    int topologicalSortQueue[MAX_QUEUE_SIZE];

    for (i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            topologicalSortQueue[topologicalSortQueueTail++] = i;
            maxTime[i] = time[i];
        }
    }
#if (0)
    printf("maxTime: ");
    for (i = 0; i < n; ++i) {
        printf("%d ", maxTime[i]);
    }
    printf("\n");
    for (i = 0; i < (topologicalSortQueueTail - topologicalSortQueueHead); ++i) {
        printf("%d ", topologicalSortQueue[i]);
    }
    printf("\n");
#endif

    // Topological Sort Using Kahn's Algorithm
    int node, neighbor;
    while (topologicalSortQueueHead < topologicalSortQueueTail) {
        node = topologicalSortQueue[topologicalSortQueueHead++];

        for (i = 0; i < graphColSize[node]; ++i) {
            neighbor = graph[node][i];

            maxTime[neighbor] = fmax(maxTime[neighbor], maxTime[node] + time[neighbor]);
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                topologicalSortQueue[topologicalSortQueueTail++] = neighbor;
            }
        }
    }

    for (i = 0; i < n; i++) {
        retVal = fmax(retVal, maxTime[i]);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_RELATIONSSIZE (int)(5 * 10000)
#define MAX_TIMESIZE (int)(5 * 10000)
    struct testCaseType {
        int n;
        int relations[MAX_RELATIONSSIZE][2];
        int relationsSize;
        int relationsColSize[MAX_RELATIONSSIZE];
        int time[MAX_TIMESIZE];
        int timeSize;
    } testCase[] = {{3, {{1, 3}, {2, 3}}, 2, {2, 2}, {3, 2, 5}, 5},
                    {5, {{1, 5}, {2, 5}, {3, 5}, {3, 4}, {4, 5}}, 5, {2, 2, 2, 2, 2}, {1, 2, 3, 4, 5}, 5},
                    {1, {}, 0, {}, {1}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3, relations = [[1,3],[2,3]], time = [3,2,5]
     *  Output: 8
     *
     *  Input: n = 5, relations = [[1,5],[2,5],[3,5],[3,4],[4,5]], time = [1,2,3,4,5]
     *  Output: 12
     *
     *  Input: n = 1, relations = [], time = [1]
     *  Output: 1
     */

    int** pRelations = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, relations = [", testCase[i].n);
        for (j = 0; j < testCase[i].relationsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].relationsColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].relations[j][k]);
            }
            printf("]");
        }
        printf("], time = [");
        for (j = 0; j < testCase[i].timeSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].time[j]);
        }
        printf("]\n");

        pRelations = (int**)malloc(testCase[i].relationsSize * sizeof(int*));
        if (pRelations == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].relationsSize; ++j) {
            pRelations[j] = (int*)malloc(testCase[i].relationsColSize[j] * sizeof(int));
            if (pRelations[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pRelations[k]) {
                        free(pRelations[k]);
                        pRelations[k] = NULL;
                    }
                }
                free(pRelations);
                pRelations = NULL;
                return EXIT_FAILURE;
            }
            memset(pRelations[j], 0, testCase[i].relationsColSize[j] * sizeof(int));
            memcpy(pRelations[j], testCase[i].relations[j], testCase[i].relationsColSize[j] * sizeof(int));
        }
        answer = minimumTime(testCase[i].n, pRelations, testCase[i].relationsSize, testCase[i].relationsColSize,
                             testCase[i].time, testCase[i].timeSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].relationsSize; ++j) {
            if (pRelations[j]) {
                free(pRelations[j]);
                pRelations[j] = NULL;
            }
        }
        free(pRelations);
        pRelations = NULL;
    }

    return EXIT_SUCCESS;
}
