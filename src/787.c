#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findCheapestPrice(int n, int** flights, int flightsSize, int* flightsColSize, int src, int dst, int k) {
    int retVal = -1;

    int i, j;

    // https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm
    int distance[n];
    for (i = 0; i < n; ++i) {
        distance[i] = INT_MAX;
    }
    distance[src] = 0;

    int from, to, price;
    int temp[n];
    for (i = 0; i <= k; ++i) {
        memset(temp, 0, sizeof(temp));
        memcpy(temp, distance, sizeof(temp));
        for (j = 0; j < flightsSize; ++j) {
            from = flights[j][0];
            to = flights[j][1];
            price = flights[j][2];
            if (distance[from] != INT_MAX) {
                temp[to] = fmin(temp[to], distance[from] + price);
            }
        }
        memcpy(distance, temp, sizeof(distance));
    }

    if (distance[dst] != INT_MAX) {
        retVal = distance[dst];
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE ((int)((100) * (100 - 1) / 2))
    struct testCaseType {
        int n;
        int flights[MAX_SIZE][3];
        int flightsSize;
        int flightsColSize[MAX_SIZE];
        int src;
        int dst;
        int k;
    } testCase[] = {{4, {{0, 1, 100}, {1, 2, 300}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}}, 5, {3, 3, 3, 3, 3}, 0, 3, 1},
                    {3, {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}}, 3, {3, 3, 3}, 0, 2, 1},
                    {3, {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}}, 3, {3, 3, 3}, 0, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
     *  Output: 700
     *
     *  Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 1
     *  Output: 200
     *
     *  Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 0
     *  Output: 500
     */

    int** pFlights = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, flights = [", testCase[i].n);
        for (j = 0; j < testCase[i].flightsSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].flightsColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].flights[j][k]);
            }
            printf("]");
        }
        printf("], src = %d, dst = %d, k = %d\n", testCase[i].src, testCase[i].dst, testCase[i].k);

        pFlights = (int**)malloc(testCase[i].flightsSize * sizeof(int*));
        if (pFlights == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].flightsSize; ++j) {
            pFlights[j] = (int*)malloc(testCase[i].flightsColSize[j] * sizeof(int));
            if (pFlights[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pFlights[k]) {
                        free(pFlights[k]);
                        pFlights[k] = NULL;
                    }
                }
                free(pFlights);
                pFlights = NULL;
                return EXIT_FAILURE;
            }
            memset(pFlights[j], 0, testCase[i].flightsColSize[j] * sizeof(int));
            memcpy(pFlights[j], testCase[i].flights[j], testCase[i].flightsColSize[j] * sizeof(int));
        }
        answer = findCheapestPrice(testCase[i].n, pFlights, testCase[i].flightsSize, testCase[i].flightsColSize,
                                   testCase[i].src, testCase[i].dst, testCase[i].k);

        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].flightsSize; ++j) {
            if (pFlights[j]) {
                free(pFlights[j]);
                pFlights[j] = NULL;
            }
        }
        free(pFlights);
        pFlights = NULL;
    }

    return EXIT_SUCCESS;
}
