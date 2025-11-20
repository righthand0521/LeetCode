#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help(int** intervals, int** temp, int* colSize, int pos, int num) {
    for (int i = pos; i >= 0; i--) {
        if (intervals[i][1] < num) {
            break;
        }
        temp[i][colSize[i]++] = num;
    }
}
int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] < p2[1]);
    }

    return (p1[0] > p2[0]);
}
int intersectionSizeTwo(int** intervals, int intervalsSize, int* intervalsColSize) {
    int retVal = 0;

    qsort(intervals, intervalsSize, sizeof(int*), compareIntArray);

    int** temp = (int**)malloc(sizeof(int*) * intervalsSize);
    if (temp == NULL) {
        perror("malloc");
        return retVal;
    }
    for (int i = 0; i < intervalsSize; i++) {
        temp[i] = (int*)malloc(sizeof(int) * 2);
        if (temp[i] == NULL) {
            perror("malloc");
            goto exit;
        }
    }
    int* colSize = (int*)malloc(sizeof(int) * intervalsSize);
    if (colSize == NULL) {
        perror("malloc");
        goto exit;
    }
    memset(colSize, 0, sizeof(int) * intervalsSize);
    for (int i = intervalsSize - 1; i >= 0; i--) {
        for (int j = intervals[i][0], k = colSize[i]; k < 2; j++, k++) {
            retVal++;
            help(intervals, temp, colSize, i - 1, j);
        }
    }

    //
    free(colSize);
    colSize = NULL;
exit:
    for (int i = 0; i < intervalsSize; i++) {
        if (temp[i] != NULL) {
            free(temp[i]);
            temp[i] = NULL;
        }
    }
    free(temp);
    temp = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3000)
    struct testCaseType {
        int intervals[MAX_SIZE][2];
        int intervalsSize;
        int intervalsColSize[MAX_SIZE];
    } testCase[] = {{{{1, 3}, {3, 7}, {8, 9}}, 3, {2, 2, 2}},
                    {{{1, 3}, {1, 4}, {2, 5}, {3, 5}}, 4, {2, 2, 2, 2}},
                    {{{1, 2}, {2, 3}, {2, 4}, {4, 5}}, 4, {2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: intervals = [[1,3],[3,7],[8,9]]
     *  Output: 5
     *
     *  Input: intervals = [[1,3],[1,4],[2,5],[3,5]]
     *  Output: 3
     *
     *  Input: intervals = [[1,2],[2,3],[2,4],[4,5]]
     *  Output: 5
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
        answer = intersectionSizeTwo(pIntervals, testCase[i].intervalsSize, testCase[i].intervalsColSize);
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
