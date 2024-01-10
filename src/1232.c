#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool checkStraightLine(int** coordinates, int coordinatesSize, int* coordinatesColSize) {
    bool retVal = true;

    if (coordinatesSize == 2) {
        return retVal;
    }

    // https://en.wikipedia.org/wiki/Cross_product
    int v1x, v1y;
    int v2x, v2y;
    int i;
    for (i = 2; i < coordinatesSize; ++i) {
        v1x = coordinates[i - 1][0] - coordinates[i - 2][0];
        v1y = coordinates[i - 1][1] - coordinates[i - 2][1];
        v2x = coordinates[i][0] - coordinates[i - 1][0];
        v2y = coordinates[i][1] - coordinates[i - 1][1];
        if ((v1x * v2y) != (v1y * v2x)) {
            retVal = false;
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int coordinates[MAX_SIZE][2];
        int coordinatesSize;
        int coordinatesColSize[MAX_SIZE];
    } testCase[] = {{{{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}}, 6, {2, 2, 2, 2, 2, 2}},
                    {{{1, 1}, {2, 2}, {3, 4}, {4, 5}, {5, 6}, {7, 7}}, 6, {2, 2, 2, 2, 2, 2}},
                    {{{1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {6, 7}}, 6, {2, 2, 2, 2, 2, 2}},
                    {{{2, 1}, {4, 2}, {6, 3}}, 3, {2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
     *  Output: true
     *
     *  Input: coordinates = [[1,1],[2,2],[3,4],[4,5],[5,6],[7,7]]
     *  Output: false
     *
     *  Input: coordinates = [[1, 2],[1, 3],[1, 4],[1, 5],[1, 6],[6, 7]]
     *  Output: false
     *
     *  Input: coordinates = [[2, 1],[4, 2],[6, 3]]
     *  Output: true
     */

    int** pCoordinates = NULL;
    bool answer = false;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: coordinates = [");
        for (j = 0; j < testCase[i].coordinatesSize; ++j) {
            printf("[");
            for (k = 0; k < testCase[i].coordinatesColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].coordinates[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pCoordinates = (int**)malloc(testCase[i].coordinatesSize * sizeof(int*));
        if (pCoordinates == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].coordinatesSize; ++j) {
            pCoordinates[j] = (int*)malloc(testCase[i].coordinatesColSize[j] * sizeof(int));
            if (pCoordinates[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pCoordinates[k]);
                    pCoordinates[k] = NULL;
                }
                free(pCoordinates);
                pCoordinates = NULL;
                return EXIT_FAILURE;
            }
            memset(pCoordinates[j], 0, testCase[i].coordinatesColSize[j] * sizeof(int));
            for (k = 0; k < testCase[i].coordinatesColSize[j]; ++k) {
                pCoordinates[j][k] = testCase[i].coordinates[j][k];
            }
        }
        answer = checkStraightLine(pCoordinates, testCase[i].coordinatesSize, testCase[i].coordinatesColSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

        for (j = 0; j < testCase[i].coordinatesSize; ++j) {
            free(pCoordinates[j]);
            pCoordinates[j] = NULL;
        }
        free(pCoordinates);
        pCoordinates = NULL;
    }

    return EXIT_SUCCESS;
}
