#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int areaOfMaxDiagonal(int** dimensions, int dimensionsSize, int* dimensionsColSize) {
    int retVal = 0;

    int maxDiagonal = 0;
    for (int i = 0; i < dimensionsSize; ++i) {
        int width = dimensions[i][0];
        int height = dimensions[i][1];
        int diagonal = (width * width + height * height);
        int area = width * height;

        if (diagonal > maxDiagonal) {
            maxDiagonal = diagonal;
            retVal = area;
        } else if (diagonal == maxDiagonal) {
            retVal = fmax(retVal, area);
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (100)
#define MAX_COLUMN (2)
    struct testCaseType {
        int dimensions[MAX_ROW][MAX_COLUMN];
        int dimensionsSize;
        int dimensionsColSize[MAX_ROW];
    } testCase[] = {{{{9, 3}, {8, 6}}, 2, {2, 2}}, {{{3, 4}, {4, 3}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: dimensions = [[9,3],[8,6]]
     *  Output: 48
     *
     *  Input: dimensions = [[3,4],[4,3]]
     *  Output: 12
     */

    int** pDimensions = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: dimensions = [");
        for (j = 0; j < testCase[i].dimensionsSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].dimensionsColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].dimensions[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pDimensions = (int**)malloc(testCase[i].dimensionsSize * sizeof(int*));
        if (pDimensions == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].dimensionsSize; ++j) {
            pDimensions[j] = (int*)malloc(testCase[i].dimensionsColSize[j] * sizeof(int));
            if (pDimensions[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pDimensions[k]);
                    pDimensions[k] = NULL;
                }
                free(pDimensions);
                pDimensions = NULL;
                return EXIT_FAILURE;
            }
            memset(pDimensions[j], 0, testCase[i].dimensionsColSize[j] * sizeof(int));
            memcpy(pDimensions[j], testCase[i].dimensions[j], testCase[i].dimensionsColSize[j] * sizeof(int));
        }
        answer = areaOfMaxDiagonal(pDimensions, testCase[i].dimensionsSize, testCase[i].dimensionsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].dimensionsSize; ++j) {
            free(pDimensions[j]);
            pDimensions[j] = NULL;
        }
        free(pDimensions);
        pDimensions = NULL;
    }

    return EXIT_SUCCESS;
}
