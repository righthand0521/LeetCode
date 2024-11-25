#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_ROW (2)                           // board.length == 2
#define MAX_COL (3)                           // board[i].length == 3
#define MAX_STR_SIZE (MAX_ROW * MAX_COL + 1)  // 0 <= board[i][j] <= 5.
struct hashTable {
    char key[MAX_STR_SIZE];
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%s\n", pFree->key);
        HASH_DEL(pFree, current);
        free(current);
    }
}
void swap(char* x, char* y) {
    char tmp = *x;
    *x = *y;
    *y = tmp;
}
char** getNextStatus(char* status, int* returnSize) {
    char** pRetVal;

    (*returnSize) = 0;

    int x = 0;
    while (status[x] != '0') {
        x++;
    }

    pRetVal = (char**)malloc(MAX_COL * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    const int neighbors[6][3] = {{1, 3, -1}, {0, 2, 4}, {1, 5, -1}, {0, 4, -1}, {1, 3, 5}, {2, 4, -1}};
    int y;
    int i, j;
    for (i = 0; i < MAX_COL && neighbors[x][i] != -1; ++i) {
        y = neighbors[x][i];
        swap(&status[x], &status[y]);

        pRetVal[(*returnSize)] = (char*)malloc(MAX_STR_SIZE * sizeof(char));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            for (j = 0; j < (*returnSize); ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }

        strcpy(pRetVal[(*returnSize)], status);
        (*returnSize)++;

        swap(&status[x], &status[y]);
    }

    return pRetVal;
}
int slidingPuzzle(int** board, int boardSize, int* boardColSize) {
    int retVal = 0;

    int i, j;

    const char target[] = "123450";

    char startState[MAX_STR_SIZE];
    memset(startState, 0, sizeof(startState));
    for (i = 0; i < MAX_ROW; ++i) {
        for (int j = 0; j < MAX_COL; ++j) {
            startState[i * MAX_COL + j] = (char)(board[i][j] + '0');
        }
    }
    startState[MAX_STR_SIZE - 1] = '\0';
    if (strcmp(startState, target) == 0) {
        return retVal;
    }

#define MAX_QUEUE_SIZE (10001)
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    struct bfsQueueNode {
        char key[MAX_STR_SIZE];
        int value;
    } bfsQueue[MAX_QUEUE_SIZE];
    strcpy(bfsQueue[bfsQueueTail].key, startState);
    bfsQueue[bfsQueueTail].value = 0;
    bfsQueueTail++;

    struct hashTable* visited = NULL;
    struct hashTable* pTemp = NULL;
    pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
    if (pTemp == NULL) {
        perror("malloc");
        return retVal;
    }
    strcpy(pTemp->key, startState);
    HASH_ADD(hh, visited, key, MAX_STR_SIZE * sizeof(char), pTemp);

    int nextStatusSize;
    char** nextStatus;
    char* status;
    int step;
    while (bfsQueueHead < bfsQueueTail) {
        status = bfsQueue[bfsQueueHead].key;
        step = bfsQueue[bfsQueueHead].value;
        bfsQueueHead++;

        nextStatusSize = 0;
        nextStatus = getNextStatus(status, &nextStatusSize);
        if (nextStatus == NULL) {
            perror("malloc");
            break;
        }
        for (i = 0; i < nextStatusSize; i++) {
            pTemp = NULL;
            HASH_FIND(hh, visited, nextStatus[i], 5 * sizeof(char), pTemp);
            if (pTemp != NULL) {
                continue;
            }

            if (strcmp(nextStatus[i], target) == 0) {
                for (j = 0; j < nextStatusSize; j++) {
                    free(nextStatus[j]);
                    nextStatus[j] = NULL;
                }
                free(nextStatus);
                nextStatus = NULL;
                freeAll(visited);
                visited = NULL;

                retVal = step + 1;

                return retVal;
            }

            strcpy(bfsQueue[bfsQueueTail].key, nextStatus[i]);
            bfsQueue[bfsQueueTail].value = step + 1;
            bfsQueueTail++;

            pTemp = NULL;
            pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                for (j = 0; j < nextStatusSize; j++) {
                    free(nextStatus[j]);
                    nextStatus[j] = NULL;
                }
                free(nextStatus);
                nextStatus = NULL;
                freeAll(visited);
                visited = NULL;
                return retVal;
            }
            strcpy(pTemp->key, nextStatus[i]);
            HASH_ADD(hh, visited, key, 5 * sizeof(char), pTemp);
        }

        //
        for (j = 0; j < nextStatusSize; j++) {
            free(nextStatus[j]);
            nextStatus[j] = NULL;
        }
        free(nextStatus);
        nextStatus = NULL;
    }
    retVal = -1;

    //
    freeAll(visited);
    visited = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2)
    struct testCaseType {
        int board[MAX_SIZE][3];
        int boardSize;
        int boardColSize[MAX_SIZE];
    } testCase[] = {
        {{{1, 2, 3}, {4, 0, 5}}, 2, {3, 3}}, {{{1, 2, 3}, {5, 4, 0}}, 2, {3, 3}}, {{{4, 1, 2}, {5, 0, 3}}, 2, {3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: board = [[1,2,3],[4,0,5]]
     *  Output: 1
     *
     *  Input: board = [[1,2,3],[5,4,0]]
     *  Output: -1
     *
     *  Input: board = [[4,1,2],[5,0,3]]
     *  Output: 5
     */

    int** pBoard = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: board = [");
        for (j = 0; j < testCase[i].boardSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].boardColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].board[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pBoard = (int**)malloc(testCase[i].boardSize * sizeof(int*));
        if (pBoard == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].boardSize; ++j) {
            pBoard[j] = (int*)malloc(testCase[i].boardColSize[j] * sizeof(int));
            if (pBoard[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pBoard[k]) {
                        free(pBoard[k]);
                        pBoard[k] = NULL;
                    }
                }
                free(pBoard);
                pBoard = NULL;
                return EXIT_FAILURE;
            }
            memset(pBoard[j], 0, testCase[i].boardColSize[j] * sizeof(int));
            memcpy(pBoard[j], testCase[i].board[j], testCase[i].boardColSize[j] * sizeof(int));
        }
        answer = slidingPuzzle(pBoard, testCase[i].boardSize, testCase[i].boardColSize);

        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].boardSize; ++j) {
            if (pBoard[j]) {
                free(pBoard[j]);
                pBoard[j] = NULL;
            }
        }
        free(pBoard);
        pBoard = NULL;
    }

    return EXIT_SUCCESS;
}
