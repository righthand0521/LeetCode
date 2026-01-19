#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getRect(int** P, int x1, int y1, int x2, int y2) {
    int retVal = P[x2][y2] - P[x1 - 1][y2] - P[x2][y1 - 1] + P[x1 - 1][y1 - 1];

    return retVal;
}
int maxSideLength(int** mat, int matSize, int* matColSize, int threshold) {
    int retVal = 0;

    int rowSize = matSize;
    int colSize = matColSize[0];

    int** P = (int**)malloc((rowSize + 1) * sizeof(int*));
    if (P == NULL) {
        perror("malloc");
        return retVal;
    }
    for (int i = 0; i <= rowSize; i++) {
        P[i] = (int*)calloc(colSize + 1, sizeof(int));
        if (P[i] == NULL) {
            perror("calloc");
            goto exit;
        }
    }
    for (int i = 1; i <= rowSize; i++) {
        for (int j = 1; j <= colSize; j++) {
            P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + mat[i - 1][j - 1];
        }
    }

    int r = (rowSize < colSize) ? (rowSize) : (colSize);
    for (int i = 1; i <= rowSize; i++) {
        for (int j = 1; j <= colSize; j++) {
            for (int c = retVal + 1; c <= r; c++) {
                if (i + c - 1 > rowSize) {
                    break;
                } else if (j + c - 1 > colSize) {
                    break;
                } else if (getRect(P, i, j, i + c - 1, j + c - 1) > threshold) {
                    break;
                }
                retVal = c;
            }
        }
    }

exit:
    for (int i = 0; i <= rowSize; i++) {
        if (P[i] != NULL) {
            free(P[i]);
            P[i] = NULL;
        }
    }
    free(P);
    P = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (300)
    struct testCaseType {
        int mat[MAX_SIZE][MAX_SIZE];
        int matSize;
        int matColSize[MAX_SIZE];
        int threshold;
    } testCase[] = {
        {{{1, 1, 3, 2, 4, 3, 2}, {1, 1, 3, 2, 4, 3, 2}, {1, 1, 3, 2, 4, 3, 2}}, 3, {7, 7, 7}, 4},
        {{{2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}}, 5, {5, 5, 5, 5, 5}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
     *  Output: 2
     *
     *  Input: mat = [[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2]], threshold = 1
     *  Output: 0
     */

    int** pMat = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: mat = [");
        for (j = 0; j < testCase[i].matSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].matColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].mat[j][k]);
            }
            printf("]");
        }
        printf("], threshold = %d\n", testCase[i].threshold);

        pMat = (int**)malloc(testCase[i].matSize * sizeof(int*));
        if (pMat == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].matSize; ++j) {
            pMat[j] = (int*)malloc(testCase[i].matColSize[j] * sizeof(int));
            if (pMat[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pMat[k]) {
                        free(pMat[k]);
                        pMat[k] = NULL;
                    }
                }
                free(pMat);
                pMat = NULL;
                return EXIT_FAILURE;
            }
            memset(pMat[j], 0, testCase[i].matColSize[j] * sizeof(int));
            memcpy(pMat[j], testCase[i].mat[j], testCase[i].matColSize[j] * sizeof(int));
        }
        answer = maxSideLength(pMat, testCase[i].matSize, testCase[i].matColSize, testCase[i].threshold);
        printf("Output: %d\n", answer);

        printf("\n");

        for (k = 0; k < testCase[i].matSize; ++k) {
            if (pMat[k]) {
                free(pMat[k]);
                pMat[k] = NULL;
            }
        }
        free(pMat);
        pMat = NULL;
    }

    return EXIT_SUCCESS;
}
