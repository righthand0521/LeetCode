#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxCandies(int* status, int statusSize, int* candies, int candiesSize, int** keys, int keysSize, int* keysColSize,
               int** containedBoxes, int containedBoxesSize, int* containedBoxesColSize, int* initialBoxes,
               int initialBoxesSize) {
    int retVal = 0;

    bool* canOpen = (bool*)calloc(statusSize, sizeof(bool));
    if (canOpen == NULL) {
        perror("calloc");
        return retVal;
    }
    for (int i = 0; i < statusSize; ++i) {
        canOpen[i] = (status[i] == 1);
    }

    bool* hasBox = (bool*)calloc(statusSize, sizeof(bool));
    if (hasBox == NULL) {
        perror("calloc");
        goto exit_canOpen;
    }
    for (int i = 0; i < statusSize; ++i) {
        hasBox[i] = false;
    }

    bool* used = (bool*)calloc(statusSize, sizeof(bool));
    if (used == NULL) {
        perror("calloc");
        goto exit_hasBox;
    }
    for (int i = 0; i < statusSize; ++i) {
        used[i] = false;
    }

    int* bfsQueue = (int*)malloc(statusSize * sizeof(int));
    if (bfsQueue == NULL) {
        perror("malloc");
        goto exit_used;
    }
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    int initialBox;
    for (int i = 0; i < initialBoxesSize; ++i) {
        initialBox = initialBoxes[i];
        hasBox[initialBox] = true;
        if (canOpen[initialBox]) {
            bfsQueue[bfsQueueTail++] = initialBox;
            used[initialBox] = true;
            retVal += candies[initialBox];
        }
    }

    int bigBox, key, box;
    while (bfsQueueHead < bfsQueueTail) {
        bigBox = bfsQueue[bfsQueueHead++];

        for (int i = 0; i < keysColSize[bigBox]; ++i) {
            key = keys[bigBox][i];
            canOpen[key] = true;
            if ((used[key] == false) && (hasBox[key] == true)) {
                bfsQueue[bfsQueueTail++] = key;
                used[key] = true;
                retVal += candies[key];
            }
        }

        for (int i = 0; i < containedBoxesColSize[bigBox]; ++i) {
            box = containedBoxes[bigBox][i];
            hasBox[box] = true;
            if ((used[box] == false) && (canOpen[box] == true)) {
                bfsQueue[bfsQueueTail++] = box;
                used[box] = true;
                retVal += candies[box];
            }
        }
    }

    // Clean up memory
    free(bfsQueue);
    bfsQueue = NULL;
exit_used:
    free(used);
    used = NULL;
exit_hasBox:
    free(hasBox);
    hasBox = NULL;
exit_canOpen:
    free(canOpen);
    canOpen = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int status[MAX_SIZE];
        int statusSize;
        int candies[MAX_SIZE];
        int candiesSize;
        int keys[MAX_SIZE][MAX_SIZE];
        int keysSize;
        int keysColSize[MAX_SIZE];
        int containedBoxes[MAX_SIZE][MAX_SIZE];
        int containedBoxesSize;
        int containedBoxesColSize[MAX_SIZE];
        int initialBoxes[MAX_SIZE];
        int initialBoxesSize;
    } testCase[] = {{{1, 0, 1, 0},
                     4,
                     {7, 5, 4, 100},
                     4,
                     {{}, {}, {1}, {}},
                     4,
                     {0, 0, 1, 0},
                     {{1, 2}, {3}, {}, {}},
                     4,
                     {2, 1, 0, 0},
                     {0},
                     1},
                    {{1, 0, 0, 0, 0, 0},
                     6,
                     {1, 1, 1, 1, 1, 1},
                     6,
                     {{1, 2, 3, 4, 5}, {}, {}, {}},
                     6,
                     {5, 0, 0, 0, 0, 0},
                     {{1, 2, 3, 4, 5}, {}, {}, {}, {}},
                     6,
                     {5, 0, 0, 0, 0},
                     {0},
                     1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: status = [1,0,1,0], candies = [7,5,4,100], keys = [[],[],[1],[]],
     *  containedBoxes = [[1,2],[3],[],[]], initialBoxes = [0]
     *  Output: 16
     *
     *  Input: status = [1,0,0,0,0,0], candies = [1,1,1,1,1,1], keys = [[1,2,3,4,5],[],[],[],[],[]],
     *  containedBoxes = [[1,2,3,4,5],[],[],[],[],[]], initialBoxes = [0]
     *  Output: 6
     */

    int** pKeys = NULL;
    int** pContainedBoxes = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: status =  [");
        for (j = 0; j < testCase[i].statusSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].status[j]);
        }
        printf("], candies =  [");
        for (j = 0; j < testCase[i].candiesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].candies[j]);
        }
        printf("], keys =  [");
        for (j = 0; j < testCase[i].keysSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].keysColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].keys[j][k]);
            }
            printf("]");
        }
        printf("], containedBoxes =  [");
        for (j = 0; j < testCase[i].containedBoxesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].containedBoxesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].containedBoxes[j][k]);
            }
            printf("]");
        }
        printf("], initialBoxes = [");
        for (j = 0; j < testCase[i].initialBoxesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].initialBoxes[j]);
        }
        printf("]\n");

        pKeys = (int**)malloc(testCase[i].keysSize * sizeof(int*));
        if (pKeys == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].keysSize; ++j) {
            pKeys[j] = (int*)malloc(testCase[i].keysColSize[j] * sizeof(int));
            if (pKeys[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pKeys[k]) {
                        free(pKeys[k]);
                        pKeys[k] = NULL;
                    }
                }
                free(pKeys);
                pKeys = NULL;
                return EXIT_FAILURE;
            }
            memset(pKeys[j], 0, testCase[i].keysColSize[j] * sizeof(int));
            memcpy(pKeys[j], testCase[i].keys[j], testCase[i].keysColSize[j] * sizeof(int));
        }
        pContainedBoxes = (int**)malloc(testCase[i].keysSize * sizeof(int*));
        if (pContainedBoxes == NULL) {
            perror("malloc");
            for (j = 0; j < testCase[i].keysSize; ++j) {
                if (pKeys[j]) {
                    free(pKeys[j]);
                    pKeys[j] = NULL;
                }
            }
            free(pKeys);
            pKeys = NULL;
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].containedBoxesSize; ++j) {
            pContainedBoxes[j] = (int*)malloc(testCase[i].containedBoxesColSize[j] * sizeof(int));
            if (pContainedBoxes[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pContainedBoxes[k]) {
                        free(pContainedBoxes[k]);
                        pContainedBoxes[k] = NULL;
                    }
                }
                free(pContainedBoxes);
                pContainedBoxes = NULL;
                for (j = 0; j < testCase[i].keysSize; ++j) {
                    if (pKeys[j]) {
                        free(pKeys[j]);
                        pKeys[j] = NULL;
                    }
                }
                free(pKeys);
                pKeys = NULL;
                return EXIT_FAILURE;
            }
            memset(pContainedBoxes[j], 0, testCase[i].containedBoxesColSize[j] * sizeof(int));
            memcpy(pContainedBoxes[j], testCase[i].containedBoxes[j],
                   testCase[i].containedBoxesColSize[j] * sizeof(int));
        }

        answer =
            maxCandies(testCase[i].status, testCase[i].statusSize, testCase[i].candies, testCase[i].candiesSize, pKeys,
                       testCase[i].keysSize, testCase[i].keysColSize, pContainedBoxes, testCase[i].containedBoxesSize,
                       testCase[i].containedBoxesColSize, testCase[i].initialBoxes, testCase[i].initialBoxesSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].containedBoxesSize; ++j) {
            if (pContainedBoxes[j]) {
                free(pContainedBoxes[j]);
                pContainedBoxes[j] = NULL;
            }
        }
        free(pContainedBoxes);
        pContainedBoxes = NULL;
        for (j = 0; j < testCase[i].keysSize; ++j) {
            if (pKeys[j]) {
                free(pKeys[j]);
                pKeys[j] = NULL;
            }
        }
        free(pKeys);
        pKeys = NULL;
    }

    return EXIT_SUCCESS;
}
