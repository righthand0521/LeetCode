#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* leftmostBuildingQueries(int* heights, int heightsSize, int** queries, int queriesSize, int* queriesColSize,
                             int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    //
    pRetVal = (int*)malloc(queriesSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (queriesSize * sizeof(int)));
    (*returnSize) = queriesSize;

    //
    int querySize[heightsSize];
    memset(querySize, 0, sizeof(querySize));
    for (int i = 0; i < queriesSize; i++) {
        int a = queries[i][0];
        int b = queries[i][1];
        if (a > b) {
            swap(&a, &b);
        }

        if ((a == b) || (heights[a] < heights[b])) {
            pRetVal[i] = b;
            continue;
        }

        querySize[b]++;
    }

    //
    struct Pair {
        int first;
        int second;
    };
    struct Pair* newQueries[heightsSize];
    for (int i = 0; i < heightsSize; i++) {
        newQueries[i] = (struct Pair*)malloc(querySize[i] * sizeof(struct Pair));
    }
    int newQueriesIdx[heightsSize];
    memset(newQueriesIdx, 0, sizeof(newQueriesIdx));
    for (int i = 0; i < queriesSize; i++) {
        int a = queries[i][0];
        int b = queries[i][1];
        if (a > b) {
            swap(&a, &b);
        }

        if (!((a == b) || (heights[a] < heights[b]))) {
            newQueries[b][newQueriesIdx[b]].first = i;
            newQueries[b][newQueriesIdx[b]].second = heights[a];
            newQueriesIdx[b]++;
        }
    }

    //
    int monoStackTop = -1;
    int* monoStack = (int*)malloc(heightsSize * sizeof(int));
    for (int i = heightsSize - 1; i >= 0; i--) {
        for (int j = 0; j < querySize[i]; j++) {
            int q = newQueries[i][j].first;
            int val = newQueries[i][j].second;
            if ((monoStackTop == -1) || (heights[monoStack[0]] <= val)) {
                pRetVal[q] = -1;
                continue;
            }

            int left = 0;
            int right = monoStackTop;
            while (left <= right) {
                int middle = (left + right) / 2;
                if (heights[monoStack[middle]] > val) {
                    left = middle + 1;
                } else {
                    right = middle - 1;
                }
            }
            pRetVal[q] = monoStack[right];
        }

        while ((monoStackTop >= 0) && (heights[monoStack[monoStackTop]] <= heights[i])) {
            monoStackTop--;
        }

        monoStack[++monoStackTop] = i;
    }

    //
    free(monoStack);
    for (int i = 0; i < heightsSize; i++) {
        free(newQueries[i]);
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(5 * 10000)
    struct testCaseType {
        int heights[MAX_SIZE];
        int heightsSize;
        int queries[MAX_SIZE][2];
        int queriesSize;
        int queriesColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{{6, 4, 8, 5, 2, 7}, 6, {{0, 1}, {0, 3}, {2, 4}, {3, 4}, {2, 2}}, 5, {2, 2, 2, 2, 2}, 0},
                    {{5, 3, 8, 2, 6, 1, 4, 6}, 8, {{0, 7}, {3, 5}, {5, 2}, {3, 0}, {1, 6}}, 5, {2, 2, 2, 2, 2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: heights = [6,4,8,5,2,7], queries = [[0,1],[0,3],[2,4],[3,4],[2,2]]
     *  Output: [2,5,-1,5,2]
     *
     *  Input: heights = [5,3,8,2,6,1,4,6], queries = [[0,7],[3,5],[5,2],[3,0],[1,6]]
     *  Output: [7,6,-1,4,6]
     */

    int** pQueries = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: heights = [");
        for (j = 0; j < testCase[i].heightsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].heights[j]);
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

        pQueries = (int**)malloc(testCase[i].queriesSize * sizeof(int*));
        if (pQueries == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            pQueries[j] = (int*)malloc(testCase[i].queriesColSize[j] * sizeof(int));
            if (pQueries[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pQueries[k]) {
                        free(pQueries[k]);
                        pQueries[k] = NULL;
                    }
                }
                free(pQueries);
                pQueries = NULL;
                return EXIT_FAILURE;
            }
            memset(pQueries[j], 0, testCase[i].queriesColSize[j] * sizeof(int));
            memcpy(pQueries[j], testCase[i].queries[j], testCase[i].queriesColSize[j] * sizeof(int));
        }
        pAnswer = leftmostBuildingQueries(testCase[i].heights, testCase[i].heightsSize, pQueries,
                                          testCase[i].queriesSize, testCase[i].queriesColSize, &testCase[i].returnSize);
        printf("Output:[");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            if (pQueries[j]) {
                free(pQueries[j]);
                pQueries[j] = NULL;
            }
        }
        free(pQueries);
        pQueries = NULL;
    }

    return EXIT_SUCCESS;
}
