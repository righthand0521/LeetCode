#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }
    return (p1[0] > p2[0]);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int**)malloc(intervalsSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    qsort(intervals, intervalsSize, sizeof(int*), compareIntArray);

    pRetVal[(*returnSize)] = (int*)malloc(intervalsColSize[(*returnSize)] * sizeof(int));
    if (pRetVal[(*returnSize)] == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal[(*returnSize)], 0, (intervalsColSize[(*returnSize)] * sizeof(int)));
    memcpy(pRetVal[(*returnSize)], intervals[(*returnSize)], (intervalsColSize[(*returnSize)] * sizeof(int)));
    (*returnSize)++;

    int i;
    for (i = 1; i < intervalsSize; ++i) {
        if (pRetVal[(*returnSize) - 1][1] >= intervals[i][0]) {
            pRetVal[(*returnSize) - 1][1] = fmax(pRetVal[(*returnSize) - 1][1], intervals[i][1]);
        } else {
            pRetVal[(*returnSize)] = (int*)malloc(intervalsColSize[(*returnSize)] * sizeof(int));
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                return pRetVal;
            }
            memset(pRetVal[(*returnSize)], 0, (intervalsColSize[(*returnSize)] * sizeof(int)));
            memcpy(pRetVal[(*returnSize)], intervals[i], (intervalsColSize[(*returnSize)] * sizeof(int)));
            (*returnSize)++;
        }
    }

    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));
    for (i = 0; i < (*returnSize); ++i) {
        (*returnColumnSizes)[i] = intervalsColSize[0];
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (int)(1e4)
#define MAX_COLUMN (2)
    struct testCaseType {
        int intervals[MAX_ROW][MAX_COLUMN];
        int intervalsSize;
        int intervalsColSize[MAX_ROW];
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{{1, 3}, {2, 6}, {8, 10}, {15, 18}}, 4, {2, 2, 2, 2}, 0, NULL},
                    {{{1, 4}, {4, 5}}, 2, {2, 2}, 0, NULL},
                    {{{1, 4}, {2, 3}}, 2, {2, 2}, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
     *  Output: [[1,6],[8,10],[15,18]]
     *
     *  Input: intervals = [[1,4],[4,5]]
     *  Output: [[1,5]]
     *
     *  Input: intervals = [[1,4],[2,3]]
     *  Output: [[1,4]]
     */

    int** pIntervals = NULL;
    int** pAnswer = NULL;
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

        pAnswer = merge(pIntervals, testCase[i].intervalsSize, testCase[i].intervalsColSize, &testCase[i].returnSize,
                        &(testCase[i].returnColumnSizes));
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
        for (j = 0; j < testCase[i].intervalsSize; ++j) {
            free(pIntervals[j]);
            pIntervals[j] = NULL;
        }
        free(pIntervals);
        pIntervals = NULL;
    }

    return EXIT_SUCCESS;
}
