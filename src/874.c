#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

static const int HASH_MULTIPLIER = 60001;  // Slightly larger than 2 * max coordinate value
struct hashTable {
    int key;
    UT_hash_handle hh;
};
void hashFreeAll(struct hashTable *pFree) {
    struct hashTable *current = NULL;
    struct hashTable *tmp = NULL;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d\n", pFree->key);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int robotSim(int *commands, int commandsSize, int **obstacles, int obstaclesSize, int *obstaclesColSize) {
    int retVal = 0;

    int i, j;

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int key;
    for (i = 0; i < obstaclesSize; i++) {
        key = obstacles[i][0] * HASH_MULTIPLIER + obstacles[i][1];
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                hashFreeAll(pHashTable);
                return retVal;
            }
            pTemp->key = key;
            HASH_ADD_INT(pHashTable, key, pTemp);
        }
    }

    const int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int d = 1;
    int px = 0;
    int py = 0;
    for (i = 0; i < commandsSize; i++) {
        if (commands[i] < 0) {
            d += ((commands[i] == -1) ? (1) : (-1));
            d %= 4;
            if (d < 0) {
                d += 4;
            }
            continue;
        }

        for (j = 0; j < commands[i]; ++j) {
            key = (px + directions[d][0]) * HASH_MULTIPLIER + py + directions[d][1];
            pTemp = NULL;
            HASH_FIND_INT(pHashTable, &key, pTemp);
            if (pTemp != NULL) {
                break;
            }
            px += directions[d][0];
            py += directions[d][1];
            retVal = fmax(retVal, px * px + py * py);
        }
    }

    //
    hashFreeAll(pHashTable);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int commands[MAX_SIZE];
        int commandsSize;
        int obstacles[MAX_SIZE][2];
        int obstaclesSize;
        int obstaclesColSize[MAX_SIZE];
    } testCase[] = {
        {{4, -1, 3}, 3, {{}}, 0, {}}, {{4, -1, 4, -2, 4}, 5, {{2, 4}}, 1, {2}}, {{6, -1, -1, 6}, 4, {{}}, 0, {}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: commands = [4,-1,3], obstacles = []
     *  Output: 25
     *
     *  Input: commands = [4,-1,4,-2,4], obstacles = [[2,4]]
     *  Output: 65
     *
     *  Input: commands = [6,-1,-1,6], obstacles = []
     *  Output: 36
     */

    int **pObstacles = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: commands = [");
        for (j = 0; j < testCase[i].commandsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].commands[j]);
        }
        printf("], obstacles = [");
        for (j = 0; j < testCase[i].obstaclesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].obstaclesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].obstacles[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pObstacles = (int **)malloc(testCase[i].obstaclesSize * sizeof(int *));
        if (pObstacles == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].obstaclesSize; ++j) {
            pObstacles[j] = (int *)malloc(testCase[i].obstaclesColSize[j] * sizeof(int));
            if (pObstacles[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pObstacles[k]) {
                        free(pObstacles[k]);
                    }
                }
                free(pObstacles);
                pObstacles = NULL;
                return EXIT_FAILURE;
            }
            memset(pObstacles[j], 0, testCase[i].obstaclesColSize[j] * sizeof(int));
            memcpy(pObstacles[j], testCase[i].obstacles[j], testCase[i].obstaclesColSize[j] * sizeof(int));
        }
        answer = robotSim(testCase[i].commands, testCase[i].commandsSize, pObstacles, testCase[i].obstaclesSize,
                          testCase[i].obstaclesColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].obstaclesSize; ++j) {
            if (pObstacles[j]) {
                free(pObstacles[j]);
            }
        }
        free(pObstacles);
        pObstacles = NULL;
    }

    return EXIT_SUCCESS;
}
