#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
long long maximumImportance(int n, int** roads, int roadsSize, int* roadsColSize) {
    long long retVal = 0;

    int degree[n];
    memset(degree, 0, sizeof(degree));

    int i;
    for (i = 0; i < roadsSize; ++i) {
        degree[roads[i][0]] += 1;
        degree[roads[i][1]] += 1;
    }
    qsort(degree, n, sizeof(int), compareInteger);

    long long value = 1;
    for (i = 0; i < n; ++i) {
        retVal += (value * degree[i]);
        value += 1;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int n;
        int roads[MAX_SIZE][2];
        int roadsSize;
        int roadsColSize[MAX_SIZE];
    } testCase[] = {{5, {{0, 1}, {1, 2}, {2, 3}, {0, 2}, {1, 3}, {2, 4}}, 6, {2, 2, 2, 2, 2, 2, 2}},
                    {5, {{0, 3}, {2, 4}, {1, 3}}, 3, {2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 5, roads = [[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]
     *  Output: 43
     *
     *  Input: n = 5, roads = [[0,3],[2,4],[1,3]]
     *  Output: 20
     */

    int** pRoads = NULL;
    long long answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, roads = [", testCase[i].n);
        for (j = 0; j < testCase[i].roadsSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].roadsColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].roads[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pRoads = (int**)malloc(testCase[i].roadsSize * sizeof(int*));
        if (pRoads == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].roadsSize; ++j) {
            pRoads[j] = (int*)malloc(testCase[i].roadsColSize[j] * sizeof(int));
            if (pRoads[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pRoads[k]) {
                        free(pRoads[k]);
                        pRoads[k] = NULL;
                    }
                }
                free(pRoads);
                pRoads = NULL;
                return EXIT_FAILURE;
            }
            memset(pRoads[j], 0, testCase[i].roadsColSize[j] * sizeof(int));
            memcpy(pRoads[j], testCase[i].roads[j], testCase[i].roadsColSize[j] * sizeof(int));
        }
        answer = maximumImportance(testCase[i].n, pRoads, testCase[i].roadsSize, testCase[i].roadsColSize);

        printf("Output: %lld\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].roadsSize; ++j) {
            if (pRoads[j]) {
                free(pRoads[j]);
                pRoads[j] = NULL;
            }
        }
        free(pRoads);
        pRoads = NULL;
    }

    return EXIT_SUCCESS;
}
