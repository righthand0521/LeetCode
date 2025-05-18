#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#ifndef LISTNODE_H
#define LISTNODE_H

struct ListNode *createList(int val) {
    struct ListNode *pObj = NULL;

    pObj = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->val = val;
    pObj->next = NULL;

    return pObj;
}
void freeList(struct ListNode *pObj) {
    if (pObj == NULL) {
        return;
    }

    struct ListNode *pFree;
    while (pObj) {
        pFree = pObj;
        pObj = pObj->next;
        free(pFree);
        pFree = NULL;
    }
}

#endif  // LISTNODE_H
#ifndef HASH_H
#define HASH_H

struct hashTable {
    int key;
    struct ListNode *val;
    UT_hash_handle hh;
};
void hashAddItem(struct hashTable **obj, int key, int val) {
    struct ListNode *p = createList(val);

    struct hashTable *pEntry = NULL;
    HASH_FIND_INT(*obj, &key, pEntry);
    if (pEntry == NULL) {
        pEntry = (struct hashTable *)malloc(sizeof(struct hashTable));
        if (pEntry == NULL) {
            perror("malloc");
            return;
        }
        pEntry->key = key;
        pEntry->val = p;
        HASH_ADD_INT(*obj, key, pEntry);
    } else {
        p->next = pEntry->val;
        pEntry->val = p;
    }
}
struct ListNode *hashGetItem(struct hashTable **obj, int key) {
    struct ListNode *pRetVal = NULL;

    struct hashTable *pEntry = NULL;
    HASH_FIND_INT(*obj, &key, pEntry);
    if (pEntry == NULL) {
        return pRetVal;
    }
    pRetVal = pEntry->val;

    return pRetVal;
}
void hashFree(struct hashTable **pObj) {
    struct hashTable *pCurrent = NULL;
    struct hashTable *pTmp = NULL;
    HASH_ITER(hh, *pObj, pCurrent, pTmp) {
        HASH_DEL(*pObj, pCurrent);
        freeList(pCurrent->val);
        pCurrent->val = NULL;
        free(pCurrent);
        pCurrent = NULL;
    }
}

#endif  // HASH_H
#define MODULO (int)(1e9 + 7)
int colorTheGrid(int m, int n) {
    int retVal = 0;

    // Hash mapping stores all valid coloration schemes for a single row that meet the requirements
    // The key represents mask, and the value represents the ternary string of mask (stored as a list)
    struct hashTable *valid = NULL;
    // Enumerate masks that meet the requirements within the range [0, 3^m)
    int mask_end = pow(3, m);
    for (int mask = 0; mask < mask_end; ++mask) {
        int mm = mask;
        int color[m];
        for (int i = 0; i < m; ++i) {
            color[i] = mm % 3;
            mm /= 3;
        }

        bool check = true;
        for (int i = 0; i < m - 1; ++i) {
            if (color[i] == color[i + 1]) {
                check = false;
                break;
            }
        }
        if (check == true) {
            for (int i = 0; i < m; i++) {
                hashAddItem(&valid, mask, color[i]);
            }
        }
    }

    // Preprocess all (mask1, mask2) binary tuples, satisfying mask1 and mask2 When adjacent rows,
    // the colors of the two cells in the same column are different
    struct hashTable *adjacent = NULL;
    for (struct hashTable *pEntry1 = valid; pEntry1; pEntry1 = pEntry1->hh.next) {
        int mask1 = pEntry1->key;
        for (struct hashTable *pEntry2 = valid; pEntry2; pEntry2 = pEntry2->hh.next) {
            int mask2 = pEntry2->key;

            bool check = true;
            for (struct ListNode *p1 = pEntry1->val, *p2 = pEntry2->val; p1 && p2; p1 = p1->next, p2 = p2->next) {
                if (p1->val == p2->val) {
                    check = false;
                    break;
                }
            }
            if (check == true) {
                hashAddItem(&adjacent, mask1, mask2);
            }
        }
    }

    int f[mask_end];
    memset(f, 0, sizeof(f));
    for (struct hashTable *pEntry = valid; pEntry; pEntry = pEntry->hh.next) {
        int mask = pEntry->key;
        f[mask] = 1;
    }
    for (int i = 1; i < n; ++i) {
        int g[mask_end];
        memset(g, 0, sizeof(g));
        for (struct hashTable *pEntry1 = valid; pEntry1; pEntry1 = pEntry1->hh.next) {
            int mask2 = pEntry1->key;
            for (struct ListNode *p = hashGetItem(&adjacent, mask2); p != NULL; p = p->next) {
                int mask1 = p->val;
                g[mask2] += f[mask1];
                if (g[mask2] >= MODULO) {
                    g[mask2] -= MODULO;
                }
            }
        }
        memcpy(f, g, sizeof(f));
    }

    hashFree(&valid);
    hashFree(&adjacent);

    for (int i = 0; i < mask_end; i++) {
        retVal += f[i];
        if (retVal >= MODULO) {
            retVal -= MODULO;
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int m;
        int n;
    } testCase[] = {{1, 1}, {1, 2}, {5, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: m = 1, n = 1
     *  Output: 3
     *
     *  Input: m = 1, n = 2
     *  Output: 6
     *
     *  Input: m = 5, n = 5
     *  Output: 580986
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: m = %d, n = %d\n", testCase[i].m, testCase[i].n);

        answer = colorTheGrid(testCase[i].m, testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
