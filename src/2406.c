#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void *a1, const void *a2) {
    int *p1 = (int *)a1;
    int *p2 = (int *)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }

    return (p1[0] > p2[0]);
}
int minGroups(int **intervals, int intervalsSize, int *intervalsColSize) {
    int retVal = 0;

    // Convert the intervals to two events start as {start, 1} and end as {end, -1}
    int intervalsWithEndSize = 2 * intervalsSize;
    int intervalsWithEnd[intervalsWithEndSize][2];
    memset(intervalsWithEnd, 0, sizeof(intervalsWithEnd));
    int i = 0;
    for (i = 0; i < intervalsSize; ++i) {
        intervalsWithEnd[2 * i][0] = intervals[i][0];
        intervalsWithEnd[2 * i][1] = 1;
        intervalsWithEnd[2 * i + 1][0] = intervals[i][1] + 1;
        intervalsWithEnd[2 * i + 1][1] = -1;
    }
    // Sort the events according to the number and then by the value (1/-1).
    qsort(intervalsWithEnd, intervalsWithEndSize, sizeof(intervalsWithEnd[0]), compareIntArray);

    int concurrentIntervals = 0;
    int maxConcurrentIntervals = 0;
    for (i = 0; i < intervalsWithEndSize; ++i) {
        concurrentIntervals += intervalsWithEnd[i][1];
        maxConcurrentIntervals = fmax(maxConcurrentIntervals, concurrentIntervals);
    }
    retVal = maxConcurrentIntervals;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int intervals[MAX_SIZE][2];
        int intervalsSize;
        int intervalsColSize[MAX_SIZE];
    } testCase[] = {{{{5, 10}, {6, 8}, {1, 5}, {2, 3}, {1, 10}}, 5, {2, 2, 2, 2, 2}},
                    {{{1, 3}, {5, 6}, {8, 10}, {11, 13}}, 4, {2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: intervals = [[5,10],[6,8],[1,5],[2,3],[1,10]]
     *  Output: 3
     *
     *  Input: intervals = [[1,3],[5,6],[8,10],[11,13]]
     *  Output: 1
     */

    int **pIntervals = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: intervals = [");
        for (j = 0; j < testCase[i].intervalsSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", "[");
            for (k = 0; k < testCase[i].intervalsColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].intervals[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pIntervals = (int **)malloc(testCase[i].intervalsSize * sizeof(int *));
        if (pIntervals == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].intervalsSize; ++j) {
            pIntervals[j] = (int *)malloc(testCase[i].intervalsColSize[j] * sizeof(int));
            if (pIntervals[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pIntervals[k]);
                    pIntervals[k] = NULL;
                }
                free(pIntervals);
                pIntervals = NULL;
                return EXIT_FAILURE;
            }
            memset(pIntervals[j], 0, (testCase[i].intervalsColSize[j] * sizeof(int)));
            memcpy(pIntervals[j], testCase[i].intervals[j], (testCase[i].intervalsColSize[j] * sizeof(int)));
        }
        answer = minGroups(pIntervals, testCase[i].intervalsSize, testCase[i].intervalsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].intervalsSize; ++j) {
            free(pIntervals[j]);
            pIntervals[j] = NULL;
        }
        free(pIntervals);
        pIntervals = NULL;
    }

    return EXIT_SUCCESS;
}
