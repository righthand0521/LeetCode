#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** insert(int** intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize,
             int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = intervalsSize + 1;
    int colSize = 2;

    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));

    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }

    int left = newInterval[0];
    int right = newInterval[1];
    int* pInterval;
    bool placed = false;
    int* tmp;
    (*returnSize) = 0;
    int i;
    for (i = 0; i < intervalsSize; ++i) {
        pInterval = intervals[i];
        if (pInterval[0] > right) {
            if (placed == false) {
                tmp = (int*)malloc(colSize * sizeof(int));
                if (tmp == NULL) {
                    perror("malloc");
                    return pRetVal;
                }
                memset(tmp, 0, (colSize * sizeof(int)));
                tmp[0] = left;
                tmp[1] = right;
                (*returnColumnSizes)[(*returnSize)] = colSize;
                pRetVal[(*returnSize)++] = tmp;

                placed = true;
            }

            tmp = (int*)malloc(colSize * sizeof(int));
            if (tmp == NULL) {
                perror("malloc");
                return pRetVal;
            }
            memset(tmp, 0, (colSize * sizeof(int)));
            memcpy(tmp, pInterval, (colSize * sizeof(int)));
            (*returnColumnSizes)[*returnSize] = colSize;
            pRetVal[(*returnSize)++] = tmp;
        } else if (pInterval[1] < left) {
            tmp = (int*)malloc(colSize * sizeof(int));
            if (tmp == NULL) {
                perror("malloc");
                return pRetVal;
            }
            memset(tmp, 0, (colSize * sizeof(int)));
            memcpy(tmp, pInterval, (colSize * sizeof(int)));
            (*returnColumnSizes)[*returnSize] = colSize;
            pRetVal[(*returnSize)++] = tmp;
        } else {
            left = fmin(left, pInterval[0]);
            right = fmax(right, pInterval[1]);
        }
    }

    if (placed == false) {
        tmp = (int*)malloc(colSize * sizeof(int));
        if (tmp == NULL) {
            perror("malloc");
            return pRetVal;
        }
        memset(tmp, 0, (colSize * sizeof(int)));
        tmp[0] = left;
        tmp[1] = right;
        (*returnColumnSizes)[*returnSize] = colSize;
        pRetVal[(*returnSize)++] = tmp;
    }

#if (DEBUG)
    for (i = (*returnSize); i < (intervalsSize + 1); ++i) {
        pRetVal[i] = (int*)malloc(colSize * sizeof(int));
        memset(pRetVal[i], 0, (colSize * sizeof(int)));
    }
#endif

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (10000)
#define MAX_COLUMN (2)
    struct testCaseType {
        int intervals[MAX_ROW][MAX_COLUMN];
        int intervalsSize;
        int intervalsColSize[MAX_ROW];
        int newInterval[MAX_COLUMN];
        int newIntervalSize;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{{1, 3}, {6, 9}}, 2, {2, 2}, {2, 5}, 2, 0, NULL},
                    {{{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}}, 5, {2, 2, 2, 2, 2}, {4, 8}, 2, 0, NULL},
                    {{}, 0, {}, {5, 7}, 2, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pIntervals = NULL;
    int* pNewInterval = NULL;
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
        printf("], newInterval = [");
        for (j = 0; j < testCase[i].newIntervalSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].newInterval[j]);
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

        pNewInterval = (int*)malloc(testCase[i].newIntervalSize * sizeof(int));
        if (pNewInterval == NULL) {
            perror("malloc");
            for (j = 0; j < testCase[i].intervalsSize; ++j) {
                free(pIntervals[j]);
            }
            free(pIntervals);
            pIntervals = NULL;
            return EXIT_FAILURE;
        }
        memset(pNewInterval, 0, (testCase[i].newIntervalSize * sizeof(int)));
        memcpy(pNewInterval, testCase[i].newInterval, (testCase[i].newIntervalSize * sizeof(int)));

        pAnswer = insert(pIntervals, testCase[i].intervalsSize, testCase[i].intervalsColSize, pNewInterval,
                         testCase[i].newIntervalSize, &testCase[i].returnSize, &(testCase[i].returnColumnSizes));
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

        for (j = 0; j < testCase[i].intervalsSize; ++j) {
            free(pIntervals[j]);
        }
        free(pIntervals);
        pIntervals = NULL;
        free(pNewInterval);
        pNewInterval = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
#if (DEBUG)
        while (j <= testCase[i].intervalsSize) {
            printf("free(pAnswer[%d])\n", j);
            free(pAnswer[j]);
            pAnswer[j] = NULL;
            ++j;
        }
        printf("\n");
#endif
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
