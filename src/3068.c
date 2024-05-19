#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long maximumValueSum(int* nums, int numsSize, int k, int** edges, int edgesSize, int* edgesColSize) {
    long long retVal = 0;

    long long sum = 0;
    int count = 0;
    int positiveMinimum = (1 << 30);
    int negativeMaximum = -1 * (1 << 30);
    int operatedNodeValue, netChange;
    int i;
    for (i = 0; i < numsSize; ++i) {
        operatedNodeValue = nums[i] ^ k;
        sum += nums[i];
        netChange = operatedNodeValue - nums[i];
        if (netChange > 0) {
            positiveMinimum = fmin(positiveMinimum, netChange);
            sum += netChange;
            count++;
        } else {
            negativeMaximum = fmax(negativeMaximum, netChange);
        }
    }

    // If the number of positive netChange values is even return the sum.
    // Otherwise return the maximum of both discussed cases.
    if (count % 2 == 0) {
        retVal = sum;
    } else {
        retVal = fmax(sum - positiveMinimum, sum + negativeMaximum);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
        int edges[MAX_SIZE][2];
        int edgesSize;
        int edgesColSize[MAX_SIZE];
    } testCase[] = {{{1, 2, 1}, 3, 3, {{0, 1}, {0, 2}}, 2, {2, 2}},
                    {{2, 3}, 2, 7, {{0, 1}}, 1, {2}},
                    {{7, 7, 7, 7, 7, 7}, 6, 3, {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}}, 5, {2, 2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,1], k = 3, edges = [[0,1],[0,2]]
     *  Output: 6
     *
     *  Input: nums = [2,3], k = 7, edges = [[0,1]]
     *  Output: 9
     *
     *  Input: nums = [7,7,7,7,7,7], k = 3, edges = [[0,1],[0,2],[0,3],[0,4],[0,5]]
     *  Output: 42
     */

    int** pEdges = NULL;
    long long answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d, edges = [", testCase[i].k);
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].edgesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].edges[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pEdges = (int**)malloc(testCase[i].edgesSize * sizeof(int*));
        if (pEdges == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            pEdges[j] = (int*)malloc(testCase[i].edgesColSize[j] * sizeof(int));
            if (pEdges[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pEdges[k]) {
                        free(pEdges[k]);
                        pEdges[k] = NULL;
                    }
                }
                free(pEdges);
                pEdges = NULL;
                return EXIT_FAILURE;
            }
            memset(pEdges[j], 0, testCase[i].edgesColSize[j] * sizeof(int));
            memcpy(pEdges[j], testCase[i].edges[j], testCase[i].edgesColSize[j] * sizeof(int));
        }
        answer = maximumValueSum(testCase[i].nums, testCase[i].numsSize, testCase[i].k, pEdges, testCase[i].edgesSize,
                                 testCase[i].edgesColSize);
        printf("Output: %lld\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].edgesSize; ++j) {
            if (pEdges[j]) {
                free(pEdges[j]);
                pEdges[j] = NULL;
            }
        }
        free(pEdges);
        pEdges = NULL;
    }

    return EXIT_SUCCESS;
}
