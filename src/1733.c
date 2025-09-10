#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    UT_hash_handle hh;
};
bool hashAddItem(struct hashTable **obj, int key) {
    bool retVal = false;

    struct hashTable *pEntry = NULL;
    HASH_FIND_INT(*obj, &key, pEntry);
    if (pEntry != NULL) {
        return retVal;
    }
    pEntry = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pEntry == NULL) {
        perror("malloc");
        return retVal;
    }
    pEntry->key = key;
    HASH_ADD_INT(*obj, key, pEntry);
    retVal = true;

    return retVal;
}
void hashFree(struct hashTable **obj) {
    struct hashTable *current = NULL;
    struct hashTable *tmp = NULL;
    HASH_ITER(hh, *obj, current, tmp) {
        // printf("%d\n", pFree->key);
        HASH_DEL(*obj, current);
        free(current);
    }
}
int minimumTeachings(int n, int **languages, int languagesSize, int *languagesColSize, int **friendships,
                     int friendshipsSize, int *friendshipsColSize) {
    int retVal = 0;

    struct hashTable *cncon = NULL;
    struct hashTable *mp = NULL;
    struct hashTable *pEntry = NULL;
    int person1, person2, key;
    bool conm;
    for (int i = 0; i < friendshipsSize; i++) {
        person1 = friendships[i][0] - 1;
        person2 = friendships[i][1] - 1;
        for (int j = 0; j < languagesColSize[person1]; j++) {
            hashAddItem(&mp, languages[person1][j]);
        }

        conm = false;
        for (int j = 0; j < languagesColSize[person2]; j++) {
            pEntry = NULL;
            key = languages[person2][j];
            HASH_FIND_INT(mp, &key, pEntry);
            if (pEntry != NULL) {
                conm = true;
                break;
            }
        }
        if (conm == false) {
            hashAddItem(&cncon, person1);
            hashAddItem(&cncon, person2);
        }

        hashFree(&mp);
        mp = NULL;
    }

    int maxCnt = 0;
    int *cnt = (int *)calloc(n + 1, sizeof(int));
    if (cnt == NULL) {
        perror("calloc");
        hashFree(&cncon);
        return retVal;
    }
    int person, lan;
    for (struct hashTable *pEntry = cncon; pEntry; pEntry = pEntry->hh.next) {
        person = pEntry->key;
        for (int i = 0; i < languagesColSize[person]; i++) {
            lan = languages[person][i];
            cnt[lan]++;
            maxCnt = fmax(maxCnt, cnt[lan]);
        }
    }
    retVal = HASH_COUNT(cncon) - maxCnt;

    //
    free(cnt);
    cnt = NULL;
    hashFree(&cncon);
    cncon = NULL;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_ROW (500)
#define MAX_COLUMN (500)
    struct testCaseType {
        int n;
        int languages[MAX_ROW][MAX_COLUMN];
        int languagesSize;
        int languagesColSize[MAX_ROW];
        int friendships[MAX_ROW][MAX_COLUMN];
        int friendshipsSize;
        int friendshipsColSize[MAX_ROW];
    } testCase[] = {
        {2, {{1}, {2}, {1, 2}}, 3, {1, 1, 2}, {{1, 2}, {1, 3}, {2, 3}}, 3, {2, 2, 2}},
        {3, {{2}, {1, 3}, {1, 2}, {3}}, 4, {1, 2, 2, 1}, {{1, 4}, {1, 2}, {3, 4}, {2, 3}}, 4, {2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 2, languages = [[1],[2],[1,2]], friendships = [[1,2],[1,3],[2,3]]
     *  Output: 1
     *
     *  Input: n = 3, languages = [[2],[1,3],[1,2],[3]], friendships = [[1,4],[1,2],[3,4],[2,3]]
     *  Output: 2
     */

    int **pLanguages = NULL;
    int **pFriendships = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, languages = [", testCase[i].n);
        for (j = 0; j < testCase[i].languagesSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].languagesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].languages[j][k]);
            }
            printf("]");
        }
        printf("], friendships = [");
        for (j = 0; j < testCase[i].friendshipsSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].friendshipsColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].friendships[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pLanguages = (int **)malloc(testCase[i].languagesSize * sizeof(int *));
        if (pLanguages == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].languagesSize; ++j) {
            pLanguages[j] = (int *)malloc(testCase[i].languagesColSize[j] * sizeof(int));
            if (pLanguages[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pLanguages[k]);
                    pLanguages[k] = NULL;
                }
                free(pLanguages);
                pLanguages = NULL;
                return EXIT_FAILURE;
            }
            memset(pLanguages[j], 0, testCase[i].languagesColSize[j] * sizeof(int));
            memcpy(pLanguages[j], testCase[i].languages[j], testCase[i].languagesColSize[j] * sizeof(int));
        }

        pFriendships = (int **)malloc(testCase[i].friendshipsSize * sizeof(int *));
        if (pFriendships == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].friendshipsSize; ++j) {
            pFriendships[j] = (int *)malloc(testCase[i].friendshipsColSize[j] * sizeof(int));
            if (pFriendships[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pFriendships[k]);
                    pFriendships[k] = NULL;
                }
                free(pLanguages);
                pFriendships = NULL;
                return EXIT_FAILURE;
            }
            memset(pFriendships[j], 0, testCase[i].friendshipsColSize[j] * sizeof(int));
            memcpy(pFriendships[j], testCase[i].friendships[j], testCase[i].friendshipsColSize[j] * sizeof(int));
        }

        answer = minimumTeachings(testCase[i].n, pLanguages, testCase[i].languagesSize, testCase[i].languagesColSize,
                                  pFriendships, testCase[i].friendshipsSize, testCase[i].friendshipsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].languagesSize; ++j) {
            free(pLanguages[j]);
            pLanguages[j] = NULL;
        }
        free(pLanguages);
        pLanguages = NULL;
        for (j = 0; j < testCase[i].friendshipsSize; ++j) {
            free(pFriendships[j]);
            pFriendships[j] = NULL;
        }
        free(pFriendships);
        pFriendships = NULL;
    }

    return EXIT_SUCCESS;
}
