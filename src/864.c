#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} HashItem;
HashItem *hashFindItem(HashItem **obj, int key) {
    HashItem *pRetVal = NULL;

    HASH_FIND_INT(*obj, &key, pRetVal);

    return pRetVal;
}
bool hashAddItem(HashItem **obj, int key, int val) {
    bool retVal = false;

    if (hashFindItem(obj, key)) {
        return retVal;
    }

    HashItem *pEntry = (HashItem *)malloc(sizeof(HashItem));
    if (pEntry == NULL) {
        perror("malloc");
        return retVal;
    }
    pEntry->key = key;
    pEntry->val = val;
    HASH_ADD_INT(*obj, key, pEntry);
    retVal = true;

    return retVal;
}
int hashGetItem(HashItem **obj, int key, int defaultVal) {
    int retVal = defaultVal;

    HashItem *pEntry = hashFindItem(obj, key);
    if (pEntry == NULL) {
        return retVal;
    }
    retVal = pEntry->val;

    return retVal;
}
void hashFree(HashItem **obj) {
    HashItem *pCurrent = NULL;
    HashItem *pTemp = NULL;
    HASH_ITER(hh, *obj, pCurrent, pTemp) {
        HASH_DEL(*obj, pCurrent);
        free(pCurrent);
    }
}
typedef struct Tuple {
    int x;
    int y;
    int mask;
} Tuple;
Tuple *creatTuple(int x, int y, int mask) {
    Tuple *pRetVal = (Tuple *)malloc(sizeof(Tuple));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    pRetVal->x = x;
    pRetVal->y = y;
    pRetVal->mask = mask;

    return pRetVal;
}
int shortestPathAllKeys(char **grid, int gridSize) {
    int retVal = -1;

    int i, j, idx;
    int gridColSize = strlen(grid[0]);

    //
    int startX = 0;
    int startY = 0;
    HashItem *keyToIdx = NULL;
    for (i = 0; i < gridSize; ++i) {
        for (j = 0; j < gridColSize; ++j) {
            if (grid[i][j] == '@') {
                startX = i;
                startY = j;
            } else if (islower(grid[i][j])) {
                if (hashFindItem(&keyToIdx, grid[i][j]) == NULL) {
                    idx = HASH_COUNT(keyToIdx);
                    hashAddItem(&keyToIdx, grid[i][j], idx);
                }
            }
        }
    }

    //
    const int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int keySize = HASH_COUNT(keyToIdx);
    int visited[gridSize][gridColSize][1 << keySize];
    memset(visited, -1, sizeof(visited));
    visited[startX][startY][0] = 0;

    Tuple *bfsQueue[gridSize * gridColSize * (1 << keySize)];
    int bfsHead = 0;
    int bfsTail = 0;
    bfsQueue[bfsTail] = creatTuple(startX, startY, 0);
    if (bfsQueue[bfsTail] == NULL) {
        hashFree(&keyToIdx);
        return retVal;
    }
    bfsTail++;

    int x, y, mask, nextX, nextY;
    while (bfsHead != bfsTail) {
        x = bfsQueue[bfsHead]->x;
        y = bfsQueue[bfsHead]->y;
        mask = bfsQueue[bfsHead]->mask;
        free(bfsQueue[bfsHead]);
        bfsHead++;

        for (i = 0; i < 4; ++i) {
            nextX = x + directions[i][0];
            nextY = y + directions[i][1];

            if ((nextX < 0) || (nextX >= gridSize)) {
                continue;
            } else if ((nextY < 0) || (nextY >= gridColSize)) {
                continue;
            } else if (grid[nextX][nextY] == '#') {
                continue;
            }

            if ((grid[nextX][nextY] == '.') || (grid[nextX][nextY] == '@')) {
                if (visited[nextX][nextY][mask] == -1) {
                    visited[nextX][nextY][mask] = visited[x][y][mask] + 1;
                    bfsQueue[bfsTail] = creatTuple(nextX, nextY, mask);
                    if (bfsQueue[bfsTail] == NULL) {
                        goto exitLabel;
                    }
                    bfsTail++;
                }
            } else if (islower(grid[nextX][nextY])) {
                idx = hashGetItem(&keyToIdx, grid[nextX][nextY], -1);
                if (visited[nextX][nextY][mask | (1 << idx)] == -1) {
                    visited[nextX][nextY][mask | (1 << idx)] = visited[x][y][mask] + 1;
                    if ((mask | (1 << idx)) == (1 << keySize) - 1) {
                        retVal = visited[nextX][nextY][mask | (1 << idx)];

                        goto exitLabel;
                    }
                    bfsQueue[bfsTail] = creatTuple(nextX, nextY, mask | (1 << idx));
                    if (bfsQueue[bfsTail] == NULL) {
                        goto exitLabel;
                    }
                    bfsTail++;
                }
            } else {
                idx = hashGetItem(&keyToIdx, tolower(grid[nextX][nextY]), -1);
                if ((mask & (1 << idx)) && visited[nextX][nextY][mask] == -1) {
                    visited[nextX][nextY][mask] = visited[x][y][mask] + 1;
                    bfsQueue[bfsTail] = creatTuple(nextX, nextY, mask);
                    if (bfsQueue[bfsTail] == NULL) {
                        goto exitLabel;
                    }
                    bfsTail++;
                }
            }
        }
    }

exitLabel:
    while (bfsHead != bfsTail) {
        free(bfsQueue[bfsHead]);
        bfsHead++;
    }

    //
    hashFree(&keyToIdx);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (30)
    struct testCaseType {
        char *grid[MAX_SIZE];
        int gridSize;
    } testCase[] = {{{"@.a..", "###.#", "b.A.B"}, 3}, {{"@..aA", "..B#.", "....b"}, 3}, {{"@Aa"}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = ["@.a..","###.#","b.A.B"]
     *  Output: 8
     *
     *  Input: grid = ["@..aA","..B#.","....b"]
     *  Output: 6
     *
     *  Input: grid = ["@Aa"]
     *  Output: -1
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: grid = [");
        for (j = 0; j < testCase[i].gridSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].grid[j]);
        }
        printf("]\n");

        answer = shortestPathAllKeys(testCase[i].grid, testCase[i].gridSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
