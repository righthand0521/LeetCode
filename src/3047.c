#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long largestSquareArea(int** bottomLeft, int bottomLeftSize, int* bottomLeftColSize, int** topRight,
                            int topRightSize, int* topRightColSize) {
    long long retVal = 0;

    long long maxSide = 0;
    int weight, high, side;
    for (int i = 0; i < bottomLeftSize; i++) {
        for (int j = i + 1; j < bottomLeftSize; j++) {
            weight = fmin(topRight[i][0], topRight[j][0]) - fmax(bottomLeft[i][0], bottomLeft[j][0]);
            high = fmin(topRight[i][1], topRight[j][1]) - fmax(bottomLeft[i][1], bottomLeft[j][1]);
            if ((weight < 0) || (high < 0)) {
                continue;
            }

            side = fmin(weight, high);
            if ((long long)side > maxSide) {
                maxSide = (long long)side;
            }
        }
    }
    retVal = maxSide * maxSide;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e3)
    struct testCaseType {
        int bottomleft[MAX_SIZE][2];
        int bottomLeftSize;
        int bottomLeftColSize[MAX_SIZE];
        int topRight[MAX_SIZE][2];
        int topRightSize;
        int topRightColSize[MAX_SIZE];
    } testCase[] = {{{{1, 1}, {2, 2}, {3, 1}}, 3, {2, 2, 2}, {{3, 3}, {4, 4}, {6, 6}}, 3, {2, 2, 2}},
                    {{{1, 1}, {1, 3}, {1, 5}}, 3, {2, 2, 2}, {{5, 5}, {5, 7}, {5, 9}}, 3, {2, 2, 2}},
                    {{{1, 1}, {2, 2}, {1, 2}}, 3, {2, 2, 2}, {{3, 3}, {4, 4}, {3, 4}}, 3, {2, 2, 2}},
                    {{{1, 1}, {3, 3}, {3, 1}}, 3, {2, 2, 2}, {{2, 2}, {4, 4}, {4, 2}}, 3, {2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: bottomLeft = [[1,1],[2,2],[3,1]], topRight = [[3,3],[4,4],[6,6]]
     *  Output: 1
     *
     *  Input: bottomLeft = [[1,1],[1,3],[1,5]], topRight = [[5,5],[5,7],[5,9]]
     *  Output: 4
     *
     *  Input: bottomLeft = [[1,1],[2,2],[1,2]], topRight = [[3,3],[4,4],[3,4]]
     *  Output: 1
     *
     *  Input: bottomLeft = [[1,1],[3,3],[3,1]], topRight = [[2,2],[4,4],[4,2]]
     *  Output: 0
     */

    int** pBottomleft = NULL;
    int** pTopRight = NULL;
    long long answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: bottomleft = [");
        for (j = 0; j < testCase[i].bottomLeftSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].bottomLeftColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].bottomleft[j][k]);
            }
            printf("]");
        }
        printf("], topRight = [");
        for (j = 0; j < testCase[i].topRightSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].topRightColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].topRight[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pBottomleft = (int**)malloc(testCase[i].bottomLeftSize * sizeof(int*));
        if (pBottomleft == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].bottomLeftSize; ++j) {
            pBottomleft[j] = (int*)malloc(testCase[i].bottomLeftColSize[j] * sizeof(int));
            if (pBottomleft[j] == NULL) {
                perror("malloc");
                goto exit_bottomleft;
            }
            memset(pBottomleft[j], 0, testCase[i].bottomLeftColSize[j] * sizeof(int));
            memcpy(pBottomleft[j], testCase[i].bottomleft[j], testCase[i].bottomLeftColSize[j] * sizeof(int));
        }

        pTopRight = (int**)malloc(testCase[i].topRightSize * sizeof(int*));
        if (pTopRight == NULL) {
            perror("malloc");
            goto exit_bottomleft;
        }
        for (j = 0; j < testCase[i].topRightSize; ++j) {
            pTopRight[j] = (int*)malloc(testCase[i].topRightColSize[j] * sizeof(int));
            if (pTopRight[j] == NULL) {
                perror("malloc");
                goto exit_topRight;
            }
            memset(pTopRight[j], 0, testCase[i].topRightColSize[j] * sizeof(int));
            memcpy(pTopRight[j], testCase[i].topRight[j], testCase[i].topRightColSize[j] * sizeof(int));
        }

        answer = largestSquareArea(pBottomleft, testCase[i].bottomLeftSize, testCase[i].bottomLeftColSize, pTopRight,
                                   testCase[i].topRightSize, testCase[i].topRightColSize);
        printf("Output: %lld\n", answer);

        printf("\n");

    exit_topRight:
        for (j = 0; j < testCase[i].topRightSize; ++j) {
            if (pTopRight[j] != NULL) {
                free(pTopRight[j]);
                pTopRight[j] = NULL;
            }
        }
        free(pTopRight);
        pTopRight = NULL;
    exit_bottomleft:
        for (j = 0; j < testCase[i].bottomLeftSize; ++j) {
            if (pBottomleft[j] != NULL) {
                free(pBottomleft[j]);
                pBottomleft[j] = NULL;
            }
        }
        free(pBottomleft);
        pBottomleft = NULL;
    }

    return EXIT_SUCCESS;
}
