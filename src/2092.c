#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct {
    int size;
    int capacity;
    int* data;
} IntVector;
typedef struct {
    int key;
    IntVector* val;
    UT_hash_handle hh;
} HashItem;
IntVector* createIntVector() {
    IntVector* pRetVal = NULL;

    pRetVal = (IntVector*)malloc(sizeof(IntVector));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->size = 0;
    pRetVal->capacity = 64;
    pRetVal->data = (int*)malloc(pRetVal->capacity * sizeof(int));
    if (pRetVal->data == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    return pRetVal;
}
void pushBack(IntVector* vec, int value) {
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        vec->data = (int*)realloc(vec->data, vec->capacity * sizeof(int));
    }
    vec->data[vec->size++] = value;
}
void freeIntVector(IntVector* vec) {
    free(vec->data);
    free(vec);
}
HashItem* hashFindItem(HashItem** obj, int key) {
    HashItem* pEntry = NULL;

    HASH_FIND_INT(*obj, &key, pEntry);

    return pEntry;
}
bool hashAddItem(HashItem** obj, int key, int val) {
    bool retVal = true;

    HashItem* pEntry = NULL;
    HASH_FIND_INT(*obj, &key, pEntry);
    if (pEntry != NULL) {
        pushBack(pEntry->val, val);
    } else {
        pEntry = (HashItem*)malloc(sizeof(HashItem));
        pEntry->key = key;
        pEntry->val = createIntVector();
        pushBack(pEntry->val, val);
        HASH_ADD_INT(*obj, key, pEntry);
    }

    return retVal;
}
IntVector* hashGetItem(HashItem** obj, int key) {
    IntVector* pRetVal = NULL;

    HashItem* pEntry = hashFindItem(obj, key);
    if (pEntry != NULL) {
        pRetVal = pEntry->val;
    }

    return pRetVal;
}
void hashFree(HashItem** obj) {
    HashItem* curr = NULL;
    HashItem* tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        freeIntVector(curr->val);
        free(curr);
    }
    *obj = NULL;
}
typedef struct {
    int key;
    UT_hash_handle hh;
} HashSetItem;
HashSetItem* hashSetFindItem(HashSetItem** obj, int key) {
    HashSetItem* pEntry = NULL;

    HASH_FIND_INT(*obj, &key, pEntry);

    return pEntry;
}
bool hashSetAddItem(HashSetItem** obj, int key) {
    bool retVal = false;

    if (hashSetFindItem(obj, key)) {
        return retVal;
    }
    HashSetItem* pEntry = (HashSetItem*)malloc(sizeof(HashSetItem));
    pEntry->key = key;
    HASH_ADD_INT(*obj, key, pEntry);
    retVal = true;

    return retVal;
}
void hashSetFree(HashSetItem** obj) {
    HashSetItem* curr = NULL;
    HashSetItem* tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        free(curr);
    }
    *obj = NULL;
}

#endif  // HASH_TABLE_H
int compareIntArray(const void* a, const void* b) {
    int* meetingA = *(int**)a;
    int* meetingB = *(int**)b;

    return meetingA[2] - meetingB[2];
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAllPeople(int n, int** meetings, int meetingsSize, int* meetingsColSize, int firstPerson, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    qsort(meetings, meetingsSize, sizeof(int*), compareIntArray);

    bool secret[n];
    memset(secret, false, sizeof(secret));
    secret[0] = secret[firstPerson] = true;

    HashSetItem* vertices = NULL;
    HashItem* edges = NULL;

    int bfsQueue[n];

    int x, y, front, rear, value;
    for (int i = 0; i < meetingsSize;) {
        int j = i;
        while ((j + 1 < meetingsSize) && (meetings[j + 1][2] == meetings[i][2])) {
            ++j;
        }

        hashFree(&edges);
        hashSetFree(&vertices);
        edges = NULL;
        for (int k = i; k <= j; ++k) {
            x = meetings[k][0];
            y = meetings[k][1];
            hashSetAddItem(&vertices, x);
            hashSetAddItem(&vertices, y);
            hashAddItem(&edges, x, y);
            hashAddItem(&edges, y, x);
        }

        front = 0;
        rear = 0;
        for (HashSetItem* pEntry = vertices; pEntry != NULL; pEntry = pEntry->hh.next) {
            value = pEntry->key;
            if (secret[value] == true) {
                bfsQueue[rear++] = value;
            }
        }

        while (front < rear) {
            value = bfsQueue[front++];
            IntVector* neighbors = hashGetItem(&edges, value);
            if (neighbors == NULL) {
                continue;
            }

            for (int idx = 0; idx < neighbors->size; ++idx) {
                value = neighbors->data[idx];
                if (secret[value] == false) {
                    secret[value] = true;
                    bfsQueue[rear++] = value;
                }
            }
        }

        i = j + 1;
    }

    pRetVal = (int*)malloc(n * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
    } else {
        for (int i = 0; i < n; i++) {
            if (secret[i] == true) {
                pRetVal[(*returnSize)++] = i;
            }
        }
    }

    //
    hashSetFree(&vertices);
    hashFree(&edges);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (int)(1e5)
#define MAX_COLUMN (3)
    struct testCaseType {
        int n;
        int meetings[MAX_ROW][MAX_COLUMN];
        int meetingsSize;
        int meetingsColSize[MAX_ROW];
        int firstPerson;
        int returnSize;
    } testCase[] = {{6, {{1, 2, 5}, {2, 3, 8}, {1, 5, 10}}, 3, {3, 3, 3}, 1, 0},
                    {4, {{3, 1, 3}, {1, 2, 2}, {0, 3, 3}}, 3, {3, 3, 3}, 3, 0},
                    {5, {{3, 4, 2}, {1, 2, 1}, {2, 3, 1}}, 3, {3, 3, 3}, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1
     *  Output: [0,1,2,3,5]
     *
     *  Input: n = 4, meetings = [[3,1,3],[1,2,2],[0,3,3]], firstPerson = 3
     *  Output: [0,1,3]
     *
     *  Input: n = 5, meetings = [[3,4,2],[1,2,1],[2,3,1]], firstPerson = 1
     *  Output: [0,1,2,3,4]
     */

    int** pMeetings = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, meetings = [", testCase[i].n);
        for (j = 0; j < testCase[i].meetingsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].meetingsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].meetings[j][k]);
            }
            printf("]");
        }
        printf("], firstPerson = %d\n", testCase[i].firstPerson);

        pMeetings = (int**)malloc(testCase[i].meetingsSize * sizeof(int*));
        if (pMeetings == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].meetingsSize; ++j) {
            pMeetings[j] = (int*)malloc(testCase[i].meetingsColSize[j] * sizeof(int));
            if (pMeetings[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pMeetings[k]);
                }
                free(pMeetings);
                return EXIT_FAILURE;
            }
            memset(pMeetings[j], 0, (testCase[i].meetingsColSize[j] * sizeof(int)));
            memcpy(pMeetings[j], testCase[i].meetings[j], (testCase[i].meetingsColSize[j] * sizeof(int)));
        }
        pAnswer = findAllPeople(testCase[i].n, pMeetings, testCase[i].meetingsSize, testCase[i].meetingsColSize,
                                testCase[i].firstPerson, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].meetingsSize; ++j) {
            free(pMeetings[j]);
        }
        free(pMeetings);
        pMeetings = NULL;
    }

    return EXIT_SUCCESS;
}
