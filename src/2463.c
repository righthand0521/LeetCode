#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }

    return (p1[0] > p2[0]);
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
long long minimumTotalDistance(int* robot, int robotSize, int** factory, int factorySize, int* factoryColSize) {
    long long retVal = 0;

    // Sort robots and factories by position
    qsort(robot, robotSize, sizeof(int), compareInteger);
    qsort(factory, factorySize, sizeof(factory[0]), compareIntArray);

    // Flatten factory positions according to their capacities
    int factoryPositionsSize = 0;
    for (int i = 0; i < factorySize; ++i) {
        factoryPositionsSize += factory[i][1];
    }
    int factoryPositions[factoryPositionsSize];
    memset(factoryPositions, 0, sizeof(factoryPositions));
    int factoryPositionsIndex = 0;
    for (int i = 0; i < factorySize; ++i) {
        for (int j = 0; j < factory[i][1]; ++j) {
            factoryPositions[factoryPositionsIndex++] = factory[i][0];
        }
    }

    long long dp[robotSize + 1][factoryPositionsSize + 1];
    memset(dp, 0, sizeof(dp));

    // Initialize base cases
    for (int i = 0; i < robotSize; ++i) {
        dp[i][factoryPositionsSize] = 1e12;  // No factories left
    }

    // Fill DP table bottom-up
    long long assign, skip;
    for (int i = robotSize - 1; i >= 0; --i) {
        for (int j = factoryPositionsSize - 1; j >= 0; --j) {
            // Option 1: Assign current robot to current factory
            assign = abs(robot[i] - factoryPositions[j]) + dp[i + 1][j + 1];

            // Option 2: Skip current factory for the current robot
            skip = dp[i][j + 1];

            dp[i][j] = fmin(assign, skip);  // Take the minimum option
        }
    }
    retVal = dp[0][0];  // Minimum distance starting from first robot and factory

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int robot[MAX_SIZE];
        int robotSize;
        int factory[MAX_SIZE][2];
        int factorySize;
        int factoryColSize[MAX_SIZE];
    } testCase[] = {{{0, 4, 6}, 3, {{2, 2}, {6, 2}}, 2, {2, 2}}, {{1, -1}, 2, {{-2, 1}, {2, 1}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: robot = [0,4,6], factory = [[2,2],[6,2]]
     *  Output: 4
     *
     *  Input: robot = [1,-1], factory = [[-2,1],[2,1]]
     *  Output: 2
     */

    int** pFactory = NULL;
    long long answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: robot = [");
        for (j = 0; j < testCase[i].robotSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].robot[j]);
        }
        printf("], factory = [");
        for (j = 0; j < testCase[i].factorySize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].factoryColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].factory[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pFactory = (int**)malloc(testCase[i].factorySize * sizeof(int*));
        if (pFactory == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].factorySize; ++j) {
            pFactory[j] = (int*)malloc(testCase[i].factoryColSize[j] * sizeof(int));
            if (pFactory[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pFactory[k]) {
                        free(pFactory[k]);
                        pFactory[k] = NULL;
                    }
                }
                free(pFactory);
                pFactory = NULL;
                return EXIT_FAILURE;
            }
            memset(pFactory[j], 0, testCase[i].factoryColSize[j] * sizeof(int));
            memcpy(pFactory[j], testCase[i].factory[j], testCase[i].factoryColSize[j] * sizeof(int));
        }

        answer = minimumTotalDistance(testCase[i].robot, testCase[i].robotSize, pFactory, testCase[i].factorySize,
                                      testCase[i].factoryColSize);
        printf("Output: %lld\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].factorySize; ++j) {
            if (pFactory[j]) {
                free(pFactory[j]);
                pFactory[j] = NULL;
            }
        }
        free(pFactory);
        pFactory = NULL;
    }

    return EXIT_SUCCESS;
}
