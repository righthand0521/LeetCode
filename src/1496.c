#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_LENGTH (16)  // 1 <= path.length <= 10^4
struct hashTable {
    char key[MAX_LENGTH];
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* pCurrent;
    struct hashTable* pTmp;
    HASH_ITER(hh, pFree, pCurrent, pTmp) {
        // printf("%s\n", pFree->key);
        HASH_DEL(pFree, pCurrent);
        free(pCurrent);
    }
}
bool isPathCrossing(char* path) {
    bool retVal = false;

    int x = 0;
    int y = 0;
    char pointsHash[MAX_LENGTH];
    memset(pointsHash, 0, sizeof(pointsHash));
    snprintf(pointsHash, sizeof(pointsHash), "%d,%d", x, y);

    struct hashTable* pVisited = NULL;
    struct hashTable* pTmp = NULL;
    pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
    if (pTmp == NULL) {
        perror("malloc");
        return retVal;
    }
    snprintf(pTmp->key, MAX_LENGTH, "%s", pointsHash);
    HASH_ADD_STR(pVisited, key, pTmp);

    int pathSize = strlen(path);
    int i;
    for (i = 0; i < pathSize; ++i) {
        if (path[i] == 'N') {
            y += 1;
        } else if (path[i] == 'S') {
            y -= 1;
        } else if (path[i] == 'E') {
            x += 1;
        } else if (path[i] == 'W') {
            x -= 1;
        }
        memset(pointsHash, 0, sizeof(pointsHash));
        snprintf(pointsHash, sizeof(pointsHash), "%d,%d", x, y);

        pTmp = NULL;
        HASH_FIND_STR(pVisited, pointsHash, pTmp);
        if (pTmp != NULL) {
            retVal = true;
            break;
        }
        pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTmp == NULL) {
            perror("malloc");
            freeAll(pVisited);
            pVisited = NULL;
            return retVal;
        }
        snprintf(pTmp->key, MAX_LENGTH, "%s", pointsHash);
        HASH_ADD_STR(pVisited, key, pTmp);
    }

    freeAll(pVisited);
    pVisited = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char path[MAX_SIZE];
    } testCase[] = {{"NES"}, {"NESWW"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: path = "NES"
     *  Output: false
     *
     *  Input: path = "NESWW"
     *  Output: true
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: path = \"%s\"\n", testCase[i].path);

        answer = isPathCrossing(testCase[i].path);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
