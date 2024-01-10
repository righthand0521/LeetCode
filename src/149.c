#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_LENGTH (32)
struct hashStruct {
    char key[MAX_LENGTH];
    int count;
    UT_hash_handle hh;
};
void freeAll(struct hashStruct* pFree) {
    struct hashStruct* current;
    struct hashStruct* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        HASH_DEL(pFree, current);
        free(current);
    }
}
int gcd(int a, int b) {
    int remainder;
    while (b != 0) {
        remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}
int maxPoints(int** points, int pointsSize, int* pointsColSize) {
    int retVal = 0;

    struct hashStruct* map;
    struct hashStruct* temp;
    char key[MAX_LENGTH];
    int maxCount, duplicate, vertical, horizontal;
    int x, y, greatestCommonDivisor;
    int i, j;
    for (i = 0; i < pointsSize; ++i) {
        maxCount = 0;
        duplicate = 0;
        vertical = 0;
        horizontal = 0;
        map = NULL;
        for (j = (i + 1); j < pointsSize; ++j) {
            x = points[j][0] - points[i][0];
            y = points[j][1] - points[i][1];

            if ((x == 0) && (y == 0)) {
                ++duplicate;
            } else if (x == 0) {
                ++vertical;
                maxCount = fmax(maxCount, vertical);
            } else if (y == 0) {
                ++horizontal;
                maxCount = fmax(maxCount, horizontal);
            } else {
                greatestCommonDivisor = gcd(x, y);
                x /= greatestCommonDivisor;
                y /= greatestCommonDivisor;
                memset(key, 0, sizeof(key));
                snprintf(key, sizeof(key), "%d@%d", x, y);
                temp = NULL;
                HASH_FIND_STR(map, key, temp);
                if (temp == NULL) {
                    temp = (struct hashStruct*)malloc(sizeof(struct hashStruct));
                    if (temp == NULL) {
                        perror("malloc");
                        freeAll(map);
                        return retVal;
                    }
                    snprintf(temp->key, MAX_LENGTH, "%s", key);
                    temp->count = 1;
                    HASH_ADD_STR(map, key, temp);
                } else {
                    temp->count += 1;
                }
                maxCount = fmax(maxCount, temp->count);
            }
        }
        freeAll(map);

        retVal = fmax(retVal, maxCount + duplicate + 1);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (300)
#define MAX_COL (2)
    struct testCaseType {
        int points[MAX_ROW][MAX_COL];
        int pointsSize;
        int pointsColSize[MAX_ROW];
    } testCase[] = {{{{1, 1}, {2, 2}, {3, 3}}, 3, {2, 2, 2}},
                    {{{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}}, 6, {2, 2, 2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: points = [[1,1],[2,2],[3,3]]
     *  Output: 3
     *
     *  Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
     *  Output: 4
     */

    int** pPoints = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: points = [");
        for (j = 0; j < testCase[i].pointsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].pointsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].points[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pPoints = (int**)malloc(testCase[i].pointsSize * sizeof(int*));
        if (pPoints == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].pointsSize; ++j) {
            pPoints[j] = (int*)malloc(testCase[i].pointsColSize[j] * sizeof(int));
            if (pPoints[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pPoints[k]);
                    pPoints[k] = NULL;
                }
                free(pPoints);
                pPoints = NULL;
                return EXIT_FAILURE;
            }
            memset(pPoints[j], 0, testCase[i].pointsColSize[j] * sizeof(int));
            memcpy(pPoints[j], testCase[i].points[j], testCase[i].pointsColSize[j] * sizeof(int));
        }
        answer = maxPoints(pPoints, testCase[i].pointsSize, testCase[i].pointsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].pointsSize; ++j) {
            free(pPoints[j]);
        }
        free(pPoints);
        pPoints = NULL;
    }

    return EXIT_SUCCESS;
}
