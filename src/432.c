#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

// https://leetcode.cn/problems/all-oone-data-structure/solutions/1341409/by-melwood-28xu/
#define MAX_KEY_SIZE (16)  // 1 <= key.length <= 10
typedef struct {
    char key[MAX_KEY_SIZE];
    int count;
    UT_hash_handle hh;
} word;
int cmp(word* a, word* b) {
    //
    return a->count > b->count;
}
typedef struct {
    word* hash;
    int sorted;
    char maxkey[MAX_KEY_SIZE];
    char minkey[MAX_KEY_SIZE];
} AllOne;
AllOne* allOneCreate() {
    AllOne* obj = NULL;

    obj = (AllOne*)calloc(1, sizeof(AllOne));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }

    return obj;
}
void allOneInc(AllOne* obj, char* key) {
    word* cur;
    HASH_FIND_STR(obj->hash, key, cur);
    if (cur) {
        cur->count++;
    } else {
        cur = (word*)calloc(1, sizeof(word));
        strcpy(cur->key, key);
        cur->count = 1;
        HASH_ADD_STR(obj->hash, key, cur);
    }
    obj->sorted = 0;
}
void allOneDec(AllOne* obj, char* key) {
    word* cur;
    HASH_FIND_STR(obj->hash, key, cur);
    cur->count--;
    if (cur->count == 0) {
        HASH_DEL(obj->hash, cur);
    }
    obj->sorted = 0;
}
char* allOneGetMaxKey(AllOne* obj) {
    char* pRetVal;

    if (!HASH_COUNT(obj->hash)) {
        pRetVal = "";
    } else {
        if (!obj->sorted) {
            obj->sorted = 1;
            HASH_SORT(obj->hash, cmp);
            strcpy(obj->minkey, obj->hash->key);
            int n = HASH_COUNT(obj->hash) - 1;
            word* cur = obj->hash;
            while (n) {
                cur = cur->hh.next;
                n--;
            }
            strcpy(obj->maxkey, cur->key);
        }
        pRetVal = obj->maxkey;
    }

    return pRetVal;
}
char* allOneGetMinKey(AllOne* obj) {
    char* pRetVal;

    if (!HASH_COUNT(obj->hash)) {
        pRetVal = "";
    } else {
        if (!obj->sorted) {
            obj->sorted = 1;
            HASH_SORT(obj->hash, cmp);
            strcpy(obj->minkey, obj->hash->key);
            int n = HASH_COUNT(obj->hash) - 1;
            word* cur = obj->hash;
            while (n) {
                cur = cur->hh.next;
                n--;
            }
            strcpy(obj->maxkey, cur->key);
        }
        pRetVal = obj->minkey;
    }

    return pRetVal;
}
void allOneFree(AllOne* obj) {
    if (obj->hash) {
        word* tmp2;
        for (word* tmp = obj->hash; tmp;) {
            HASH_DEL(obj->hash, tmp);
            tmp2 = tmp;
            tmp = tmp->hh.next;
            free(tmp2);
        }
    }
    free(obj);
}
/**
 * Your AllOne struct will be instantiated and called as such:
 * AllOne* obj = allOneCreate();
 * allOneInc(obj, key);
 * allOneDec(obj, key);
 * char* param_3 = allOneGetMaxKey(obj);
 * char* param_4 = allOneGetMinKey(obj);
 * allOneFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (int)(5 * 10000)
    struct testCaseType {
        char* methods[MAX_SIZE];
        char val[MAX_SIZE][10];
        int valSize[MAX_SIZE];
        int calls;
    } testCase[] = {{{"AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc", "getMaxKey", "getMinKey"},
                     {{}, {"hello"}, {"hello"}, {}, {}, {"leet"}, {}, {}},
                     {0, 1, 1, 0, 0, 1, 0, 0},
                     8}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc", "getMaxKey", "getMinKey"]
     *  [[], ["hello"], ["hello"], [], [], ["leet"], [], []]
     *  Output
     *  [null, null, null, "hello", "hello", null, "hello", "leet"]
     */

    AllOne* obj = NULL;
    char* retVal;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ", ", testCase[i].methods[j]);
        }
        printf("]\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s[", (j == 0) ? "" : ", ");
            for (k = 0; k < testCase[i].valSize[j]; ++k) {
                printf("%s\"%s\"", (k == 0) ? "" : ",", testCase[i].val[j]);
            }
            printf("]");
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s", (j == 0) ? "" : ",");

            if (strcmp(testCase[i].methods[j], "AllOne") == 0) {
                obj = allOneCreate(testCase[i].val[j][0]);
                printf("%snull", (j == 0) ? "" : " ");
            } else if (strcmp(testCase[i].methods[j], "inc") == 0) {
                allOneInc(obj, testCase[i].val[j]);
                printf("%snull", (j == 0) ? "" : " ");
            } else if (strcmp(testCase[i].methods[j], "dec") == 0) {
                allOneDec(obj, testCase[i].val[j]);
                printf("%snull", (j == 0) ? "" : " ");
            } else if (strcmp(testCase[i].methods[j], "getMaxKey") == 0) {
                retVal = allOneGetMaxKey(obj);
                printf("%s\"%s\"", (j == 0) ? "" : " ", retVal);
            } else if (strcmp(testCase[i].methods[j], "getMinKey") == 0) {
                retVal = allOneGetMinKey(obj);
                printf("%s\"%s\"", (j == 0) ? "" : " ", retVal);
            }
        }
        printf("]\n");

        allOneFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
