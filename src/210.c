#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int* returnSize) {
    int* pRetVal = NULL;

    int i;

    int indegree[numCourses];
    memset(indegree, 0, sizeof(indegree));
    int adjacency[numCourses][numCourses];
    memset(adjacency, -1, sizeof(adjacency));  // 1 <= numCourses <= 2000; 0 <= ai, bi < numCourses;
    int adjacencyColSize[numCourses];
    memset(adjacencyColSize, 0, sizeof(adjacencyColSize));
    int idx;
    for (i = 0; i < prerequisitesSize; ++i) {
        idx = prerequisites[i][1];
        adjacency[idx][adjacencyColSize[idx]++] = prerequisites[i][0];
        indegree[prerequisites[i][0]]++;
    }
#if (0)
    printf("indegree: ");
    for (i = 0; i < numCourses; ++i) {
        printf("%d ", indegree[i]);
    }
    printf("\n");
    int j;
    for (i = 0; i < numCourses; ++i) {
        printf("adjacency[%d]: ", i);
        for (j = 0; j < numCourses; ++j) {
            printf("%2d ", adjacency[i][j]);
        }
        printf(": %d\n", adjacencyColSize[i]);
    }
#endif

#define MAX_QUEUE_SIZE ((numCourses)*2)
    int topologicalSortQueueHead = 0;
    int topologicalSortQueueTail = 0;
    int topologicalSortQueue[MAX_QUEUE_SIZE];
    for (i = 0; i < numCourses; i++) {
        if (indegree[i] == 0) {
            topologicalSortQueue[topologicalSortQueueTail++] = i;
        }
    }
#if (0)
    for (i = 0; i < (topologicalSortQueueTail - topologicalSortQueueHead); ++i) {
        printf("%d ", topologicalSortQueue[i]);
    }
    printf("\n");
#endif

    (*returnSize) = 0;
    pRetVal = (int*)malloc(numCourses * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (numCourses * sizeof(int)));

    // Topological Sort Using Kahn's Algorithm
    int prerequisite, neighbor;
    while (topologicalSortQueueHead < topologicalSortQueueTail) {
        prerequisite = topologicalSortQueue[topologicalSortQueueHead++];
        pRetVal[(*returnSize)++] = prerequisite;

        for (i = 0; i < adjacencyColSize[prerequisite]; ++i) {
            neighbor = adjacency[prerequisite][i];
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                topologicalSortQueue[topologicalSortQueueTail++] = neighbor;
            }
        }
    }

    if ((*returnSize) != numCourses) {
        (*returnSize) = 0;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(500)
    struct testCaseType {
        int numCourses;
        int prerequisites[MAX_SIZE][MAX_SIZE];
        int prerequisitesSize;
        int prerequisitesColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{2, {{1, 0}}, 1, {2}, 0},
                    {4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}}, 4, {2, 2, 2, 2}, 0},
                    {1, {}, 0, {0}, 0},
                    {3, {{1, 0}, {1, 2}, {0, 1}}, 3, {2, 2, 2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: numCourses = 2, prerequisites = [[1,0]]
     *  Output: [0,1]
     *
     *  Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
     *  Output: [0,2,1,3]
     *
     *  Input: numCourses = 1, prerequisites = []
     *  Output: [0]
     *
     *  Input: numCourses = 3, prerequisites = [[1,0],[1,2],[0,1]]
     *  Output: []
     */

    int** pPrerequisites = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: numCourses = %d, prerequisites =  [", testCase[i].numCourses);
        for (j = 0; j < testCase[i].prerequisitesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].prerequisitesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].prerequisites[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pPrerequisites = (int**)malloc(testCase[i].prerequisitesSize * sizeof(int*));
        if (pPrerequisites == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].prerequisitesSize; ++j) {
            pPrerequisites[j] = (int*)malloc(testCase[i].prerequisitesColSize[j] * sizeof(int));
            if (pPrerequisites[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pPrerequisites[k]) {
                        free(pPrerequisites[k]);
                        pPrerequisites[k] = NULL;
                    }
                }
                free(pPrerequisites);
                pPrerequisites = NULL;
                return EXIT_FAILURE;
            }
            memset(pPrerequisites[j], 0, testCase[i].prerequisitesColSize[j] * sizeof(int));
            memcpy(pPrerequisites[j], testCase[i].prerequisites[j], testCase[i].prerequisitesColSize[j] * sizeof(int));
        }
        pAnswer = findOrder(testCase[i].numCourses, pPrerequisites, testCase[i].prerequisitesSize,
                            testCase[i].prerequisitesColSize, &testCase[i].returnSize);
        printf("Output:[");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].prerequisitesSize; ++j) {
            if (pPrerequisites[j]) {
                free(pPrerequisites[j]);
                pPrerequisites[j] = NULL;
            }
        }
        free(pPrerequisites);
        pPrerequisites = NULL;
    }

    return EXIT_SUCCESS;
}
