#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections/solutions/6575954/sorting-python-c-java-js-c-go-rust-kotlin-swift/
typedef struct {
    int start;
    int end;
} pair;
int compareStruct(const void *a, const void *b) {
    int pa = ((pair *)a)->start;
    int pb = ((pair *)b)->start;

    // ascending order
    return (pa > pb);
}
bool check(pair *intervals, int intervalsSize) {
    bool retVal = false;

    qsort(intervals, intervalsSize, sizeof(pair), compareStruct);

    int sections = 0;
    int maxEnd = intervals[0].end;
    int start, end;
    for (int i = 0; i < intervalsSize; ++i) {
        start = intervals[i].start;
        end = intervals[i].end;
        if (maxEnd <= start) {
            sections++;
        }
        maxEnd = fmax(maxEnd, end);
    }
    retVal = (sections >= 2);

    return retVal;
}
bool checkValidCuts(int n, int **rectangles, int rectanglesSize, int *rectanglesColSize) {
    bool retVal = false;

    pair *pXintervals = malloc(rectanglesSize * sizeof(pair));
    if (pXintervals == NULL) {
        perror("malloc");
        return retVal;
    }
    pair *pYintervals = malloc(rectanglesSize * sizeof(pair));
    if (pYintervals == NULL) {
        perror("malloc");
        free(pXintervals);
        pXintervals = NULL;
        return retVal;
    }
    for (int i = 0; i < rectanglesSize; ++i) {
        pXintervals[i].start = rectangles[i][0];
        pXintervals[i].end = rectangles[i][2];
        pYintervals[i].start = rectangles[i][1];
        pYintervals[i].end = rectangles[i][3];
    }
    retVal = check(pXintervals, rectanglesSize) || check(pYintervals, rectanglesSize);

    //
    free(pXintervals);
    pXintervals = NULL;
    free(pYintervals);
    pYintervals = NULL;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int n;
        int rectangles[MAX_SIZE][4];
        int rectanglesSize;
        int rectanglesColSize[MAX_SIZE];
    } testCase[] = {{5, {{1, 0, 5, 2}, {0, 2, 2, 4}, {3, 2, 5, 3}, {0, 4, 4, 5}}, 4, {4, 4, 4, 4}},
                    {4, {{0, 0, 1, 1}, {2, 0, 3, 4}, {0, 2, 2, 3}, {3, 0, 4, 3}}, 4, {4, 4, 4, 4}},
                    {4, {{0, 2, 2, 4}, {1, 0, 3, 2}, {2, 2, 3, 4}, {3, 0, 4, 2}, {3, 2, 4, 4}}, 5, {4, 4, 4, 4, 4}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 5, rectangles = [[1,0,5,2],[0,2,2,4],[3,2,5,3],[0,4,4,5]]
     *  Output: true
     *
     *  Input: n = 4, rectangles = [[0,0,1,1],[2,0,3,4],[0,2,2,3],[3,0,4,3]]
     *  Output: true
     *
     *  Input: n = 4, rectangles = [[0,2,2,4],[1,0,3,2],[2,2,3,4],[3,0,4,2],[3,2,4,4]]
     *  Output: false
     */

    int **pRectangles = NULL;
    bool answer = false;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, rectangles = [", testCase[i].n);
        for (j = 0; j < testCase[i].rectanglesSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].rectanglesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].rectangles[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pRectangles = (int **)malloc(testCase[i].rectanglesSize * sizeof(int *));
        if (pRectangles == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].rectanglesSize; ++j) {
            pRectangles[j] = (int *)malloc(testCase[i].rectanglesColSize[j] * sizeof(int));
            if (pRectangles[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pRectangles[k]) {
                        free(pRectangles[k]);
                        pRectangles[k] = NULL;
                    }
                }
                free(pRectangles);
                pRectangles = NULL;
                return EXIT_FAILURE;
            }
            memset(pRectangles[j], 0, testCase[i].rectanglesColSize[j] * sizeof(int));
            memcpy(pRectangles[j], testCase[i].rectangles[j], testCase[i].rectanglesColSize[j] * sizeof(int));
        }
        answer = checkValidCuts(testCase[i].n, pRectangles, testCase[i].rectanglesSize, testCase[i].rectanglesColSize);

        printf("Output: %s\n", answer ? "true" : "false");

        printf("\n");

        for (j = 0; j < testCase[i].rectanglesSize; ++j) {
            if (pRectangles[j]) {
                free(pRectangles[j]);
                pRectangles[j] = NULL;
            }
        }
        free(pRectangles);
        pRectangles = NULL;
    }

    return EXIT_SUCCESS;
}
