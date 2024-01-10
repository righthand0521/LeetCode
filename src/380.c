#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashStruct {
    int val;
    UT_hash_handle hh;
};
typedef struct {
    struct hashStruct* map;
} RandomizedSet;
RandomizedSet* randomizedSetCreate() {
    RandomizedSet* pNew = (RandomizedSet*)malloc(sizeof(RandomizedSet));
    if (pNew == NULL) {
        perror("malloc");
        return pNew;
    }
    pNew->map = NULL;

    return pNew;
}
bool randomizedSetInsert(RandomizedSet* obj, int val) {
    struct hashStruct* temp = NULL;

    HASH_FIND_INT(obj->map, &val, temp);
    if (temp != NULL) {
        return false;
    }
    temp = (struct hashStruct*)malloc(sizeof(struct hashStruct));
    if (temp == NULL) {
        perror("malloc");
        return false;
    }
    temp->val = val;
    HASH_ADD_INT(obj->map, val, temp);

    return true;
}
bool randomizedSetRemove(RandomizedSet* obj, int val) {
    struct hashStruct* temp = NULL;

    HASH_FIND_INT(obj->map, &val, temp);
    if (temp == NULL) {
        return false;
    }
    HASH_DEL(obj->map, temp);
    free(temp);

    return true;
}
int randomizedSetGetRandom(RandomizedSet* obj) {
    int idx = rand() % (HASH_COUNT(obj->map));
    struct hashStruct* temp = obj->map;
    while ((idx > 0) && (temp != NULL)) {
        temp = temp->hh.next;
        --idx;
    }

    return temp->val;
}
void randomizedSetFree(RandomizedSet* obj) {
    struct hashStruct* current;
    struct hashStruct* tmp;
    HASH_ITER(hh, obj->map, current, tmp) {
        // printf("%d\n", obj->map->val);
        HASH_DEL(obj->map, current);
        free(current);
    }
    free(obj);
    obj = NULL;
}
/**
 * Your RandomizedSet struct will be instantiated and called as such:
 * RandomizedSet* obj = randomizedSetCreate();
 * bool param_1 = randomizedSetInsert(obj, val);
 * bool param_2 = randomizedSetRemove(obj, val);
 * int param_3 = randomizedSetGetRandom(obj);
 * randomizedSetFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (32)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE];
        int calls;
    } testCase[] = {{{"RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"},
                     {INT_MIN, 1, 2, 2, INT_MIN, 1, 2, INT_MIN},
                     8}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
     *  [[], [1], [2], [2], [], [1], [2], []]
     *  Output
     *  [null, true, false, true, 2, true, false, 2]
     */

    RandomizedSet* obj = NULL;
    int retInt;
    bool retBool;
    char displayStr[8];
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ", ", testCase[i].methods[j]);
        }
        printf("]\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (testCase[i].val[j] == INT_MIN) {
                printf("%s[]", (j == 0) ? "" : ", ");
                continue;
            }
            printf("%s[%d]", (j == 0) ? "" : ", ", testCase[i].val[j]);
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            memset(displayStr, 0, sizeof(displayStr));
            if (strcmp(testCase[i].methods[j], "RandomizedSet") == 0) {
                obj = randomizedSetCreate();
                snprintf(displayStr, sizeof(displayStr), "%s", "null");
            } else if (strcmp(testCase[i].methods[j], "insert") == 0) {
                retBool = randomizedSetInsert(obj, testCase[i].val[j]);
                snprintf(displayStr, sizeof(displayStr), "%s", (retBool == true) ? "true" : "false");
            } else if (strcmp(testCase[i].methods[j], "remove") == 0) {
                retBool = randomizedSetRemove(obj, testCase[i].val[j]);
                snprintf(displayStr, sizeof(displayStr), "%s", (retBool == true) ? "true" : "false");
            } else if (strcmp(testCase[i].methods[j], "getRandom") == 0) {
                retInt = randomizedSetGetRandom(obj);
                snprintf(displayStr, sizeof(displayStr), "%d", retInt);
            }
            printf("%s%s", (j == 0) ? "" : ", ", displayStr);
        }
        printf("]\n");

        randomizedSetFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
