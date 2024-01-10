#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order
    if (p1[1] == p2[1]) {
        return (p1[0] > p2[0]);
    }
    return (p1[1] > p2[1]);
}
int eraseOverlapIntervals(int** intervals, int intervalsSize, int* intervalsColSize) {
    int retVal = 0;

    qsort(intervals, intervalsSize, sizeof(int*), compareIntArray);

    int overlapping = INT_MIN;
    int start, end;
    int i;
    for (i = 0; i < intervalsSize; ++i) {
        start = intervals[i][0];
        end = intervals[i][1];

        if (start < overlapping) {
            ++retVal;
        } else {
            overlapping = end;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int intervals[MAX_SIZE][2];
        int intervalsSize;
        int intervalsColSize[MAX_SIZE];
    } testCase[] = {{{{1, 2}, {2, 3}, {3, 4}, {1, 3}}, 4, {2, 2, 2, 2}},
                    {{{1, 2}, {1, 2}, {1, 2}}, 3, {2, 2, 2}},
                    {{{1, 2}, {2, 3}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
     *  Output: 1
     *
     *  Input: intervals = [[1,2],[1,2],[1,2]]
     *  Output: 2
     *
     *  Input: intervals = [[1,2],[2,3]]
     *  Output: 0
     */

    int** pIntervals = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: intervals = [");
        for (j = 0; j < testCase[i].intervalsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].intervalsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].intervals[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pIntervals = (int**)malloc(testCase[i].intervalsSize * sizeof(int*));
        if (pIntervals == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].intervalsSize; ++j) {
            pIntervals[j] = (int*)malloc(testCase[i].intervalsColSize[j] * sizeof(int));
            if (pIntervals[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pIntervals[k]);
                }
                free(pIntervals);
                return EXIT_FAILURE;
            }
            memset(pIntervals[j], 0, (testCase[i].intervalsColSize[j] * sizeof(int)));
            memcpy(pIntervals[j], testCase[i].intervals[j], (testCase[i].intervalsColSize[j] * sizeof(int)));
        }
        answer = eraseOverlapIntervals(pIntervals, testCase[i].intervalsSize, testCase[i].intervalsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].intervalsSize; ++j) {
            free(pIntervals[j]);
        }
        free(pIntervals);
        pIntervals = NULL;
    }

    return EXIT_SUCCESS;
}
