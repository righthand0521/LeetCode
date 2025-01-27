#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* checkIfPrerequisite(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize,
                          int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    bool* pRetVal = NULL;

    (*returnSize) = 0;

    bool isPrerequisite[numCourses][numCourses];
    memset(isPrerequisite, false, sizeof(isPrerequisite));
    for (int i = 0; i < prerequisitesSize; ++i) {
        isPrerequisite[prerequisites[i][0]][prerequisites[i][1]] = true;
    }

    for (int intermediate = 0; intermediate < numCourses; intermediate++) {
        for (int src = 0; src < numCourses; src++) {
            for (int target = 0; target < numCourses; target++) {
                // If src -> intermediate & intermediate -> target exists then src -> target will also exist.
                isPrerequisite[src][target] = isPrerequisite[src][target] || (isPrerequisite[src][intermediate] &&
                                                                              isPrerequisite[intermediate][target]);
            }
        }
    }

    pRetVal = (bool*)malloc(queriesSize * sizeof(bool));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    for (int i = 0; i < queriesSize; ++i) {
        pRetVal[(*returnSize)++] = isPrerequisite[queries[i][0]][queries[i][1]];
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int numCourses;
        int prerequisites[MAX_SIZE][2];
        int prerequisitesSize;
        int prerequisitesColSize[MAX_SIZE];
        int queries[MAX_SIZE][2];
        int queriesSize;
        int queriesColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{2, {{1, 0}}, 1, {2}, {{0, 1}, {1, 0}}, 2, {2, 2}, 0},
                    {2, {}, 0, {0}, {{1, 0}, {0, 1}}, 2, {2, 2}, 0},
                    {3, {{1, 2}, {1, 0}, {2, 0}}, 3, {2, 2, 2}, {{1, 0}, {1, 2}}, 2, {2, 2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: numCourses = 2, prerequisites = [[1,0]], queries = [[0,1],[1,0]]
     *  Output: [false,true]
     *
     *  Input: numCourses = 2, prerequisites = [], queries = [[1,0],[0,1]]
     *  Output: [false,false]
     *
     *  Input: numCourses = 3, prerequisites = [[1,2],[1,0],[2,0]], queries = [[1,0],[1,2]]
     *  Output: [true,true]
     */

    int retVal = EXIT_SUCCESS;
    int** pPrerequisites = NULL;
    int** pQueries = NULL;
    bool* pAnswer = NULL;
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
        printf("], queries =  [");
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].queriesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].queries[j][k]);
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
                retVal = EXIT_FAILURE;
                goto exit_pPrerequisites;
            }
            memset(pPrerequisites[j], 0, testCase[i].prerequisitesColSize[j] * sizeof(int));
            memcpy(pPrerequisites[j], testCase[i].prerequisites[j], testCase[i].prerequisitesColSize[j] * sizeof(int));
        }
        pQueries = (int**)malloc(testCase[i].queriesSize * sizeof(int*));
        if (pQueries == NULL) {
            perror("malloc");
            retVal = EXIT_FAILURE;
            goto exit_pPrerequisites;
        }
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            pQueries[j] = (int*)malloc(testCase[i].queriesColSize[j] * sizeof(int));
            if (pQueries[j] == NULL) {
                perror("malloc");
                retVal = EXIT_FAILURE;
                goto exit_pQueries;
            }
            memset(pQueries[j], 0, testCase[i].queriesColSize[j] * sizeof(int));
            memcpy(pQueries[j], testCase[i].queries[j], testCase[i].queriesColSize[j] * sizeof(int));
        }
        pAnswer = checkIfPrerequisite(testCase[i].numCourses, pPrerequisites, testCase[i].prerequisitesSize,
                                      testCase[i].prerequisitesColSize, pQueries, testCase[i].queriesSize,
                                      testCase[i].queriesColSize, &testCase[i].returnSize);
        printf("Output:[");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", (pAnswer[j] == true ? "true" : "false"));
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    exit_pQueries:
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            if (pQueries[j]) {
                free(pQueries[j]);
                pQueries[j] = NULL;
            }
        }
        free(pQueries);
        pQueries = NULL;
    exit_pPrerequisites:
        for (j = 0; j < testCase[i].prerequisitesSize; ++j) {
            if (pPrerequisites[j]) {
                free(pPrerequisites[j]);
                pPrerequisites[j] = NULL;
            }
        }
        free(pPrerequisites);
        pPrerequisites = NULL;

        if (retVal == EXIT_FAILURE) {
            break;
        }
    }

    return retVal;
}
