#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#ifndef HEAP_H
#define HEAP_H

typedef struct {
    int first;
    int second;
} Pair;
int cmpPair(Pair a, Pair b) {
    int retVal = 0;

    if (a.first != b.first) {
        retVal = (a.first < b.first) ? (-1) : (1);
    } else if (a.second != b.second) {
        retVal = (a.second < b.second) ? (-1) : (1);
    }

    return retVal;
}

typedef struct TreapNode {
    Pair key;
    int pri;
    int size;
    struct TreapNode *l, *r;
} TreapNode;
int nodeSize(TreapNode* n) {
    int retVal = 0;

    if (n) {
        retVal = n->size;
    }

    return retVal;
}
void updateSize(TreapNode* n) {
    if (n) {
        n->size = 1 + nodeSize(n->l) + nodeSize(n->r);
    }
}
TreapNode* newNode(Pair key) {
    TreapNode* pObj = NULL;

    pObj = (TreapNode*)malloc(sizeof(TreapNode));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->key = key;
    pObj->pri = rand();
    pObj->size = 1;
    pObj->l = NULL;
    pObj->r = NULL;

    return pObj;
}
TreapNode* rotateRight(TreapNode* y) {
    TreapNode* x = y->l;

    y->l = x->r;
    x->r = y;
    updateSize(y);
    updateSize(x);

    return x;
}
TreapNode* rotateLeft(TreapNode* x) {
    TreapNode* y = x->r;

    x->r = y->l;
    y->l = x;
    updateSize(x);
    updateSize(y);

    return y;
}
TreapNode* treapInsert(TreapNode* root, Pair key) {
    if (root == NULL) {
        return newNode(key);
    }

    int c = cmpPair(key, root->key);
    if (c < 0) {
        root->l = treapInsert(root->l, key);
        if (root->l->pri > root->pri) {
            root = rotateRight(root);
        }
    } else if (c > 0) {
        root->r = treapInsert(root->r, key);
        if (root->r->pri > root->pri) {
            root = rotateLeft(root);
        }
    }
    updateSize(root);

    return root;
}
TreapNode* treapDelete(TreapNode* root, Pair key) {
    if (root == NULL) {
        return NULL;
    }

    int c = cmpPair(key, root->key);
    if (c < 0) {
        root->l = treapDelete(root->l, key);
    } else if (c > 0) {
        root->r = treapDelete(root->r, key);
    } else {
        if (root->l == NULL) {
            TreapNode* r = root->r;
            free(root);

            return r;
        } else if (root->r == NULL) {
            TreapNode* l = root->l;
            free(root);

            return l;
        } else {
            if (root->l->pri > root->r->pri) {
                root = rotateRight(root);
                root->r = treapDelete(root->r, key);
            } else {
                root = rotateLeft(root);
                root->l = treapDelete(root->l, key);
            }
        }
    }
    updateSize(root);

    return root;
}
TreapNode* treapMin(TreapNode* root) {
    while (root && root->l) {
        root = root->l;
    }

    return root;
}
TreapNode* treapMax(TreapNode* root) {
    while (root && root->r) {
        root = root->r;
    }

    return root;
}
void treapFree(TreapNode* root) {
    if (root == NULL) {
        return;
    }
    treapFree(root->l);
    treapFree(root->r);
    free(root);
}

#endif  // HEAP_H
#ifndef HASH_H
#define HASH_H

typedef struct {
    int key;
    int count;
    UT_hash_handle hh;
} OccEntry;
OccEntry* occFind(OccEntry* occ, int num) {
    OccEntry* pObj = NULL;

    HASH_FIND_INT(occ, &num, pObj);

    return pObj;
}
int occGet(OccEntry* occ, int num) {
    int retVal = 0;

    OccEntry* pObj = occFind(occ, num);
    if (pObj != NULL) {
        retVal = pObj->count;
    }

    return retVal;
}
void occInc(OccEntry** occ, int num) {
    OccEntry* pObj = occFind(*occ, num);
    if (pObj == NULL) {
        pObj = (OccEntry*)malloc(sizeof(OccEntry));
        if (pObj == NULL) {
            perror("malloc");
            return;
        }
        pObj->key = num;
        pObj->count = 0;
        HASH_ADD_INT(*occ, key, pObj);
    }
    pObj->count++;
}
void occDec(OccEntry** occ, int num) {
    OccEntry* pObj = occFind(*occ, num);
    if (pObj != NULL) {
        pObj->count--;
        if (pObj->count == 0) {
            HASH_DEL(*occ, pObj);
            free(pObj);
        }
    }
}
void occFreeAll(OccEntry* occ) {
    OccEntry *cur, *tmp;
    HASH_ITER(hh, occ, cur, tmp) {
        HASH_DEL(occ, cur);
        free(cur);
    }
}

#endif  // HASH_H
typedef struct {
    int x;
    int result;
    TreapNode* large;
    TreapNode* small;
    OccEntry* occ;
} Helper;
void helperInit(Helper* h, int x) {
    h->x = x;
    h->result = 0;
    h->large = NULL;
    h->small = NULL;
    h->occ = NULL;
}
void helperFree(Helper* h) {
    treapFree(h->large);
    treapFree(h->small);
    occFreeAll(h->occ);
}
void internalInsert(Helper* h, Pair p) {
    int largeSize = nodeSize(h->large);
    TreapNode* minLarge = treapMin(h->large);
    if ((largeSize < h->x) || (minLarge && cmpPair(p, minLarge->key) > 0)) {
        h->result += p.first * p.second;
        h->large = treapInsert(h->large, p);
        if (nodeSize(h->large) > h->x) {
            TreapNode* m = treapMin(h->large);
            Pair transfer = m->key;
            h->result -= transfer.first * transfer.second;
            h->large = treapDelete(h->large, transfer);
            h->small = treapInsert(h->small, transfer);
        }
    } else {
        h->small = treapInsert(h->small, p);
    }
}
void internalRemove(Helper* h, Pair p) {
    TreapNode* minLarge = treapMin(h->large);
    if (minLarge && cmpPair(p, minLarge->key) >= 0) {
        h->result -= p.first * p.second;
        h->large = treapDelete(h->large, p);
        if (h->small) {
            TreapNode* maxSmall = treapMax(h->small);
            if (maxSmall) {
                Pair transfer = maxSmall->key;
                h->result += transfer.first * transfer.second;
                h->small = treapDelete(h->small, transfer);
                h->large = treapInsert(h->large, transfer);
            }
        }
    } else {
        h->small = treapDelete(h->small, p);
    }
}
void helperInsert(Helper* h, int num) {
    int c = occGet(h->occ, num);
    if (c) {
        internalRemove(h, (Pair){c, num});
    }

    occInc(&h->occ, num);
    c = occGet(h->occ, num);
    internalInsert(h, (Pair){c, num});
}
void helperRemove(Helper* h, int num) {
    int c = occGet(h->occ, num);
    if (c) {
        internalRemove(h, (Pair){c, num});
        occDec(&h->occ, num);
        c = occGet(h->occ, num);
        if (c) internalInsert(h, (Pair){c, num});
    }
}
int helperGet(Helper* h) {
    int retVal = h->result;

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findXSum(int* nums, int numsSize, int k, int x, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int*)calloc(numsSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    Helper h;
    helperInit(&h, x);
    for (int i = 0; i < numsSize; i++) {
        helperInsert(&h, nums[i]);
        if (i >= k) {
            helperRemove(&h, nums[i - k]);
        }
        if (i >= k - 1) {
            pRetVal[(*returnSize)++] = helperGet(&h);
        }
    }
    helperFree(&h);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
        int x;
        int returnSize;
    } testCase[] = {{{1, 1, 2, 2, 3, 4, 2, 3}, 8, 6, 2, 0}, {{3, 8, 7, 8, 7, 5}, 6, 2, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,1,2,2,3,4,2,3], k = 6, x = 2
     *  Output: [6,10,12]
     *
     *  Input: nums = [3,8,7,8,7,5], k = 2, x = 2
     *  Output: [11,15,15,15,12]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d, x = %d\n", testCase[i].k, testCase[i].x);

        pAnswer =
            findXSum(testCase[i].nums, testCase[i].numsSize, testCase[i].k, testCase[i].x, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", *(pAnswer + j));
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
