#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize) {
    bool retVal = false;

    int i;

    int indegree[numCourses];
    memset(indegree, 0, sizeof(indegree));
    int adjacency[numCourses][numCourses];
    memset(adjacency, -1, sizeof(adjacency));  // 1 <= numCourses <= 2000; 0 <= ai, bi < numCourses;
    int adjacencyColSize[numCourses];
    memset(adjacencyColSize, 0, sizeof(adjacencyColSize));
    int idx;
    for (i = 0; i < prerequisitesSize; ++i) {
        idx = prerequisites[i][0];
        adjacency[idx][adjacencyColSize[idx]++] = prerequisites[i][1];
        indegree[prerequisites[i][1]]++;
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

    // // Topological Sort Using Kahn's Algorithm
    int numOfPrerequisite = 0;
    int prerequisite, neighbor;
    while (topologicalSortQueueHead < topologicalSortQueueTail) {
        prerequisite = topologicalSortQueue[topologicalSortQueueHead++];
        ++numOfPrerequisite;

        for (i = 0; i < adjacencyColSize[prerequisite]; ++i) {
            neighbor = adjacency[prerequisite][i];
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                topologicalSortQueue[topologicalSortQueueTail++] = neighbor;
            }
        }
    }
    retVal = (numOfPrerequisite == numCourses);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(500)
    struct testCaseType {
        int numCourses;
        int prerequisites[MAX_SIZE][MAX_SIZE];
        int prerequisitesSize;
        int prerequisitesColSize[MAX_SIZE];
    } testCase[] = {{2, {{1, 0}}, 1, {2}}, {2, {{1, 0}, {0, 1}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: numCourses = 2, prerequisites = [[1,0]]
     *  Output: true
     *
     *  Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
     *  Output: false
     */

    int** pPrerequisites = NULL;
    bool answer = false;
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
        answer = canFinish(testCase[i].numCourses, pPrerequisites, testCase[i].prerequisitesSize,
                           testCase[i].prerequisitesColSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

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
