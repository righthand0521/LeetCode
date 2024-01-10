#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef UNIONFIND_H
#define UNIONFIND_H
void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
int find(int* f, int x) {
    //
    return f[x] == x ? x : (f[x] = find(f, f[x]));
}
int unionSet(int* f, int* rank, int x, int y) {
    int fx = find(f, x), fy = find(f, y);
    if (fx == fy) {
        return false;
    }

    if (rank[fx] < rank[fy]) {
        swap(&fx, &fy);
    }
    rank[fx] += rank[fy];
    f[fy] = fx;
    return true;
}
#endif  // UNIONFIND_H
struct Edge {
    int len;
    int x;
    int y;
};
int compareStruct(const void* a1, const void* a2) {
    struct Edge* p1 = (struct Edge*)a1;
    struct Edge* p2 = (struct Edge*)a2;

    // ascending order
    return (p1->len > p2->len);
}
int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize) {
    int retVal = 0;

    int i, j;

    // Kruskal's algorithm: https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
    struct Edge edges[(pointsSize + 1) * pointsSize / 2];
    int edgesSize = 0;
    for (i = 0; i < pointsSize; i++) {
        for (j = i + 1; j < pointsSize; j++) {
            edges[edgesSize].x = i;
            edges[edgesSize].y = j;
            edges[edgesSize++].len = fabs(points[i][0] - points[j][0]) + fabs(points[i][1] - points[j][1]);
        }
    }
    qsort(edges, edgesSize, sizeof(struct Edge), compareStruct);

    int f[pointsSize];
    int rank[pointsSize];
    for (i = 0; i < pointsSize; i++) {
        f[i] = i;
        rank[i] = 1;
    }

    int num = 1;
    for (i = 0; i < edgesSize; i++) {
        if (unionSet(f, rank, edges[i].x, edges[i].y)) {
            retVal += edges[i].len;
            num++;
            if (num == pointsSize) {
                break;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int points[MAX_SIZE][2];
        int pointsSize;
        int pointsColSize[MAX_SIZE];
    } testCase[] = {{{{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}}, 5, {2, 2, 2, 2, 2}},
                    {{{3, 12}, {-2, 5}, {-4, 1}}, 3, {2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
     *  Output: 20
     *
     *  Input: points = [[3,12],[-2,5],[-4,1]]
     *  Output: 18
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
        answer = minCostConnectPoints(pPoints, testCase[i].pointsSize, testCase[i].pointsColSize);
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
