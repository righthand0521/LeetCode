#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_TILES_SIZE (16)  // 1 <= tiles.length <= 7
struct hashTable {
    char key[MAX_TILES_SIZE];
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
void generateSequences(char* tiles, char* current, bool* used, struct hashTable** sequences) {
    // Add current sequence to set
    struct hashTable* pTmp = NULL;
    HASH_FIND_STR((*sequences), current, pTmp);
    if (pTmp == NULL) {
        pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTmp == NULL) {
            perror("malloc");
            return;
        }
        snprintf(pTmp->key, MAX_TILES_SIZE, "%s", current);
        HASH_ADD_STR((*sequences), key, pTmp);
    }

    // Try adding each unused character to current sequence
    char buf[MAX_TILES_SIZE];
    int tilesSize = strlen(tiles);
    for (int pos = 0; pos < tilesSize; ++pos) {
        if (used[pos] == true) {
            continue;
        }
        used[pos] = true;
        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf), "%s%c", current, tiles[pos]);
        generateSequences(tiles, buf, used, sequences);
        used[pos] = false;
    }
}
int numTilePossibilities(char* tiles) {
    int retVal = 0;

    struct hashTable* sequences = NULL;
    int tilesSize = strlen(tiles);
    bool* used = (bool*)malloc(tilesSize * sizeof(bool));
    if (used == NULL) {
        perror("malloc");
        freeAll(sequences);
        sequences = NULL;
        return retVal;
    }
    memset(used, false, (tilesSize * sizeof(bool)));
    generateSequences(tiles, "", used, &sequences);  // Generate all possible sequences including empty string
    retVal = HASH_COUNT(sequences) - 1;              // Subtract 1 to exclude empty string from count

    //
    free(used);
    used = NULL;
    freeAll(sequences);
    sequences = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (8)
    struct testCaseType {
        char tiles[MAX_SIZE];
    } testCase[] = {{"AAB"}, {"AAABBC"}, {"V"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: tiles = "AAB"
     *  Output: 8
     *
     *  Input: tiles = "AAABBC"
     *  Output: 188
     *
     *  Input: tiles = "V"
     *  Output: 1
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: tiles = \"%s\"\n", testCase[i].tiles);

        answer = numTilePossibilities(testCase[i].tiles);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
