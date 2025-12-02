#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MODULO (int)(1e9 + 7)
struct hashStruct {
    int key;
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashStruct* pFree) {
    struct hashStruct* current;
    struct hashStruct* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int countTrapezoids(int** points, int pointsSize, int* pointsColSize) {
    int retVal = 0;

    struct hashStruct* pointNum = NULL;
    struct hashStruct* pTemp;
    int value;
    for (int i = 0; i < pointsSize; i++) {
        value = points[i][1];

        pTemp = NULL;
        HASH_FIND_INT(pointNum, &value, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashStruct*)malloc(sizeof(struct hashStruct));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pointNum);
                return retVal;
            }
            pTemp->key = points[i][1];
            pTemp->value = 1;
            HASH_ADD_INT(pointNum, key, pTemp);
        } else {
            pTemp->value += 1;
        }
    }

    long long ans = 0;
    long long sum = 0;
    long long pNum, edge;
    for (pTemp = pointNum; pTemp; pTemp = pTemp->hh.next) {
        pNum = pTemp->value;
        edge = pNum * (pNum - 1) / 2;

        ans += (edge * sum);
        ans %= MODULO;
        sum += edge;
        sum %= MODULO;
    }
    retVal = ans % MODULO;

    //
    freeAll(pointNum);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (int)(1e5)
#define MAX_COL (2)
    struct testCaseType {
        int points[MAX_ROW][MAX_COL];
        int pointsSize;
        int pointsColSize[MAX_ROW];
    } testCase[] = {{{{1, 0}, {2, 0}, {3, 0}, {2, 2}, {3, 2}}, 5, {2, 2, 2, 2, 2}},
                    {{{0, 0}, {1, 0}, {0, 1}, {2, 1}}, 4, {2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: points = [[1,0],[2,0],[3,0],[2,2],[3,2]]
     *  Output: 3
     *
     *  Input: points = [[0,0],[1,0],[0,1],[2,1]]
     *  Output: 1
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
        answer = countTrapezoids(pPoints, testCase[i].pointsSize, testCase[i].pointsColSize);
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
